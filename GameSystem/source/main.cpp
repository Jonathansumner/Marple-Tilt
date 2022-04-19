#include "led-matrix.h"
#include "graphics.h"

#include <cmath>
#include <csignal>
#include <cstdio>
#include <unistd.h>
#include <cstring>
#include <algorithm>
#include <stdio.h>
#include "pigpio.h"

#include "dynamics.h"
#include "MPU6050.h"
#include "images.h"
#include "menu-pages.h"

#include "marple-tilt-machine.h"
#include "menu-states.h"
#include "game-objects.h"
#include "collision-boxes.h"
#include "render.h"
#include "textbox.h"
#include "button.h"
#include "images.h"

#include <exception>
#include <Magick++.h>
#include <magick/image.h>
#include <iostream>
#include <sys/time.h>

using namespace rgb_matrix;
using namespace std;
using rgb_matrix::Canvas;
using rgb_matrix::FrameCanvas;
using rgb_matrix::RGBMatrix;

std::vector<Object *> Object::instances;
std::vector<CollisionBox *> CollisionBox::Colliders;
std::vector<StateCollisionBox *> StateCollisionBox::stateColliders;

static Canvas *canvas;

Object *Object::frame_prev[64][64];
Object *Object::frame[64][64];

MarpleTiltMachine BaseState::runner;
MPU6050 Gyro(0x68);
volatile float accel_x = 0, accel_y = 0, accel_z = 0;

//Interrupt flags and Timers
int status = gpioInitialise();
volatile bool interrupt_received = false;
long long timestamp1;
long long timestamp2;
long long elapsed_time;
long long tick = 0;
struct timeval t;
long long frame_time = 16666; //time period for 60Hz in useconds

void GyroCallback(int gpio, int level, uint32_t tick)
{
    Gyro.clearInterrupt(); // clear register 0x3A (58) of MPU6050 to clear interrupt
    Gyro.getAccel(&accel_x, &accel_y, &accel_z);
}

static void InterruptHandler(int signo) {
    interrupt_received = true;
}

int main(int argc, char *argv[]) {
    //  Matrix initialisation
    RGBMatrix::Options defaults;
    signal(SIGTERM, InterruptHandler);
    signal(SIGINT, InterruptHandler);

    gpioSetMode(16, PI_INPUT);
    gpioSetAlertFunc(16, &GyroCallback);
    Gyro.clearInterrupt();

    defaults.hardware_mapping = "regular";
    defaults.rows = 64;
    defaults.cols = 64;
    defaults.chain_length = 1;
    defaults.parallel = 1;
    defaults.brightness = 10;
    canvas = RGBMatrix::CreateFromFlags(&argc, &argv, &defaults);
    Magick::InitializeMagick(*argv);
    rgb_matrix::Font font;
    font.LoadFont("img/5x8.bdf");
    if (canvas == nullptr)
        return 1;

//  Test Objects
    Gyro.setOffsets();
    BaseState::runner.setCanvas(canvas);
    BaseState::runner.setGyro(&Gyro);

    drawImage("img/new_logo.ppm", canvas, {0, 0, 64, 64});
    sleep(3);
    canvas->Clear();

    BaseState::runner.Init();

    while (!interrupt_received) { // 60 ticks/updates per second
        gettimeofday(&t, nullptr);
        timestamp1 = t.tv_sec * 1000L + (t.tv_usec / 1000L);
        //Before all updates
        update(canvas); // copy frame to frame_prev and update frame with new positions
        render(canvas); // go through prev_frame and frame, draw/clear new/old pixels as appropriate
        update(canvas, true); // copy frame to frame_prev and clear frame for new

        //After display updates
        if (tick % 1 == 0) { //Update physics engine every tick
            //updateMarple(BaseState::runner.GetCurrentState()->getMarple(), &Gyro);
            BaseState::runner.Update(accel_x, accel_y, accel_z);
        }
        //After game updates
        gettimeofday(&t, nullptr);
        timestamp2 = t.tv_sec * 1000L + (t.tv_usec / 1000L);
        elapsed_time = timestamp2 - timestamp1;
        if (elapsed_time < frame_time) {
            usleep(frame_time - elapsed_time);
        }
        tick++;
    }

    canvas->Clear();
    delete canvas;
    return 0;
}

