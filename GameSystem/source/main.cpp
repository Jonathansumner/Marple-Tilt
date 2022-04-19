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
int interrupt_pin = 13;
int rt_test_pin = 26; // Pin to be used for real time testing
//set rt_test & rt_flag set to true in order to measure realtime performance on pin 13 and 26
bool rt_test = false; // true: toggles pin 26 to measure time taken between interrupt and end of loop
bool rt_flag = false; // this boolean assures that interrupts processed during a loop do not hold the measurement pin high
volatile bool interrupt_received = false;
long long timestamp1;
long long timestamp2;
long long elapsed_time;
long long tick = 0;
struct timeval t;
long long frame_time = 10000; //time period for 60Hz in useconds

void GyroCallback(int gpio, int level, uint32_t tick)
{
    if (rt_test) {
        gpioWrite(rt_test_pin, 1);
        rt_flag = false;
    }
    Gyro.clearInterrupt(); // clear register 0x3A (58) of MPU6050 to clear interrupt
    Gyro.getAccel(&accel_x, &accel_y, &accel_z);
}

static void InterruptHandler(int signo) {
    interrupt_received = true;
}

void loop(Canvas *c, bool uniform = false)
{
    if (!interrupt_received)
    {
        gettimeofday(&t, nullptr);
        timestamp1 = t.tv_sec * 1000L + (t.tv_usec / 1000L);

        BaseState::runner.Update(accel_x, accel_y, accel_z);
        
        update(c);
        render(c);
        update(c, true);
        if (rt_test) {
            gpioWrite(rt_test_pin, 0);
            rt_flag = true;
        }

        gettimeofday(&t, nullptr);
        timestamp2 = t.tv_sec * 1000L + (t.tv_usec / 1000L);
        elapsed_time = timestamp2 - timestamp1;
        if (uniform && (elapsed_time < frame_time))
        {
            usleep(frame_time - elapsed_time);
        }
        loop(c, uniform);
    }
}

int main(int argc, char *argv[]) {
    //  Matrix initialisation
    RGBMatrix::Options defaults;
    defaults.hardware_mapping = "regular";
    defaults.rows = 64;
    defaults.cols = 64;
    defaults.chain_length = 1;
    defaults.parallel = 1;
    defaults.brightness = 20;
    canvas = RGBMatrix::CreateFromFlags(&argc, &argv, &defaults);
    if (canvas == nullptr)
        return 1;

    Magick::InitializeMagick(*argv);
    rgb_matrix::Font font;
    font.LoadFont("img/5x8.bdf");

    BaseState::runner.setCanvas(canvas);
    BaseState::runner.setGyro(&Gyro);

    drawImage("img/new_logo.ppm", canvas, {0, 0, 64, 64});
    sleep(3);
    canvas->Clear();

    BaseState::runner.Init();

    Gyro.setOffsets();
    Gyro.clearInterrupt();
    signal(SIGTERM, InterruptHandler);
    signal(SIGINT, InterruptHandler);
    gpioSetMode(interrupt_pin, PI_INPUT);
    gpioSetAlertFunc(interrupt_pin, &GyroCallback);

    loop(canvas, true);

    gpioTerminate();
    canvas->Clear();
    delete canvas;
    return 0;
}