#include "led-matrix.h"
#include "graphics.h"

#include <cmath>
#include <csignal>
#include <cstdio>
#include <unistd.h>
#include <cstring>
#include <algorithm>

#include "gfx.h"
#include "dynamics.h"
#include "MPU6050.h"
#include "images.h"
#include "MenuPages.h"

#include "MarpleTiltMachine.h"
#include "MenuStates.h"

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

MPU6050 Gyro(0x68);
std::vector<Object *> Object::instances;
std::vector<CollisionBox *> CollisionBox::Colliders;
std::vector<StateCollisionBox *> StateCollisionBox::stateColliders;

static Canvas *canvas;

Object *Object::frame_prev[64][64];
Object *Object::frame[64][64];

MarpleTiltMachine BaseState::runner;

//Interrupt flags and Timers
volatile bool interrupt_received = false;
long long timestamp1;
long long timestamp2;
long long elapsed_time;
long long tick = 0;
struct timeval t;
long long frame_time = 16666; //time period for 60Hz in useconds

static void InterruptHandler(int signo) {
    interrupt_received = true;
}

void update(Canvas *c, bool clear = false) { // Update object references within the render buffer
    sort(Object::instances.begin(), Object::instances.end(),
         [](Object *cmp1, Object *cmp2) { return cmp1->getType() > cmp2->getType(); });
    if (clear) memcpy(Object::frame_prev, Object::frame, sizeof(Object::frame_prev));
    for (Object *obj: Object::instances) {
        if (obj) {
            switch (obj->getType()) {
                case MARPLE: {
                    int d = dynamic_cast<Marple *>(obj)->getDiameter();
                    Marple *ref;
                    if (!clear) {
                        ref = dynamic_cast<Marple *>(obj);
                    } else {
                        ref = nullptr;
                    }
                    fillRect(obj->getPos()[0], obj->getPos()[1], d, d, ref, Object::frame);
                    break;
                }
                case HOLE: {
                    int d = dynamic_cast<Hole *>(obj)->getDiameter();
                    auto *ref = dynamic_cast<Hole *>(obj);
                    fillRect(obj->getPos()[0], obj->getPos()[1], d, d, ref, Object::frame);
                    break;
                }
                case WALL: {
                    int d = dynamic_cast<Wall *>(obj)->diameter;
                    auto *ref = dynamic_cast<Wall *>(obj);
                    fillRect(obj->getPos()[0], obj->getPos()[1], d, d, ref, Object::frame);
                    break;
                }
                case TEXT: {
                    dynamic_cast<Textbox *>(obj)->draw();
                    break;
                }
                case END : {
                    int d = dynamic_cast<End *>(obj)->getDiameter();
                    auto *ref = dynamic_cast<End *>(obj);
                    fillRect(obj->getPos()[0], obj->getPos()[1], d, d, ref, Object::frame);
                    break;
                }
                case HOME : {
                    int d = dynamic_cast<Home *>(obj)->getDiameter();
                    auto *ref = dynamic_cast<Home *>(obj);
                    fillRect(obj->getPos()[0], obj->getPos()[1], d, d, ref, Object::frame);
                }
                case BUTTON: {
                    auto *button = dynamic_cast<Button *>(obj);
                    int d = std::round(button->getBarWidth());
                    int h = button->getHeight();
                    Button *ref;
                    if (!clear) {
                        ref = button;
                    } else {
                        ref = nullptr;
                    }
                    if (ref) { drawImage(button->getPath(), c,
                                         {(int) button->getPos()[0], (int) button->getPos()[1], button->getWidth(),
                                          button->getHeight()});
                    }
                    fillRect(obj->getPos()[0], obj->getPos()[1], d, h, ref, Object::frame);
                    break;
                }
                case BAR:
                    break;
            }
        }
    }
}

void render(Canvas *canvas) { // render each pixel with respect to the object reference
    for (int i = 0; i < 64; i++) {
        for (int j = 0; j < 64; j++) {
            if (Object::frame[i][j] && !Object::frame_prev[i][j]) {
                canvas->SetPixel(i, j, Object::frame[i][j]->red, Object::frame[i][j]->green, Object::frame[i][j]->blue);
            } else if (!Object::frame[i][j] && Object::frame_prev[i][j]) {
                canvas->SetPixel(i, j, 0, 0, 0);
            }
        }
    }
}

void gyroTest(Canvas *canvas, Marple *marple, float weighting_factor = 3) {
    while (!interrupt_received) {
        float x, y, z;
        Gyro.getAccel(&x, &y, &z);
        if (x >= 2 or x <= -2) x = 0; // clip outliers
        if (y >= 2 or y <= -2) y = 0;
        if (z >= 2 or z <= -2) z = 0;
        marple->x_acceleration = x * weighting_factor;
        marple->y_acceleration = y * weighting_factor;
        if (marple->x_acceleration > 0) {
            for (int b = 0; b < std::round(marple->x_acceleration); b++) {
                canvas->SetPixel(32 + b, 31, 0, 255, 0);
                canvas->SetPixel(32 + b, 32, 0, 255, 0);
                canvas->SetPixel(32 + b, 33, 0, 255, 0);
            }
        }
        if (marple->x_acceleration < 0) {
            for (int b = 0; b > std::round(marple->x_acceleration); b--) {
                canvas->SetPixel(32 + b, 31, 0, 255, 0);
                canvas->SetPixel(32 + b, 32, 0, 255, 0);
                canvas->SetPixel(32 + b, 33, 0, 255, 0);
            }
        }
        if (marple->y_acceleration < 0) {
            for (int b = 0; b > std::round(marple->y_acceleration); b--) {
                canvas->SetPixel(31, 32 + b, 0, 0, 255);
                canvas->SetPixel(32, 32 + b, 0, 0, 255);
                canvas->SetPixel(33, 32 + b, 0, 0, 255);
            }
        }
        if (marple->y_acceleration > 0) {
            for (int b = 0; b < std::round(marple->y_acceleration); b++) {
                canvas->SetPixel(31, 32 + b, 0, 0, 255);
                canvas->SetPixel(32, 32 + b, 0, 0, 255);
                canvas->SetPixel(33, 32 + b, 0, 0, 255);
            }
        }
        std::cout << x << ", " << y << "\n";
        usleep(50000);
        canvas->Clear();
    }
}

void wallTest(bool border = true, bool wall = true) {
    Wall *walls[96];
    vector<int> colours = {0, 100, 255};
    if (border) {
        for (int x = 0; x < 16; x++) {
            walls[x] = new Wall(static_cast<float>(x) * 4, 0, 4);
            walls[x]->setColour(colours);
            walls[x + 16] = new Wall(static_cast<float>(x) * 4, 60, 4);
            walls[x + 16]->setColour(colours);
            walls[x + 32] = new Wall(0, static_cast<float>(x) * 4, 4);
            walls[x + 32]->setColour(colours);
            walls[x + 48] = new Wall(60, static_cast<float>(x) * 4, 4);
            walls[x + 48]->setColour(colours);
        }
    }
    if (wall) {
        for (int x = 0; x < 8; x++) {
            walls[x + 64] = new Wall(12, 32 + static_cast<float>(x * 4), 4);
            walls[x + 64]->setColour(colours);
            walls[x + 72] = new Wall(24, static_cast<float>(x * 4), 4);
            walls[x + 72]->setColour(colours);
            walls[x + 80] = new Wall(36, 32 + static_cast<float>(x * 4), 4);
            walls[x + 80]->setColour(colours);
            walls[x + 88] = new Wall(48, static_cast<float>(x * 4), 4);
            walls[x + 88]->setColour(colours);
        }
    }
}

int main(int argc, char *argv[]) {
    //  Matrix initialisation
    RGBMatrix::Options defaults;
    signal(SIGTERM, InterruptHandler);
    signal(SIGINT, InterruptHandler);
    defaults.hardware_mapping = "regular";
    defaults.rows = 64;
    defaults.cols = 64;
    defaults.chain_length = 1;
    defaults.parallel = 1;
    defaults.brightness = 5;
    canvas = RGBMatrix::CreateFromFlags(&argc, &argv, &defaults);
    Magick::InitializeMagick(*argv);
    rgb_matrix::Font font;
    font.LoadFont("img/5x8.bdf");
    if (canvas == nullptr)
        return 1;

//  Test Objects
    Gyro.setOffsets();
    BaseState::runner.setCanvas(canvas);
    BaseState::runner.currState = new MainMenu(canvas);
    BaseState::runner.GetCurrentState()->OnEntry();

    while (!interrupt_received) { // 60 ticks/updates per second
        gettimeofday(&t, nullptr);
        timestamp1 = t.tv_sec * 1000L + (t.tv_usec / 1000L);
        //Before all updates
        update(canvas); // copy frame to frame_prev and update frame with new positions
        render(canvas); // go through prev_frame and frame, draw/clear new/old pixels as appropriate
        update(canvas, true); // copy frame to frame_prev and clear frame for new

        //After display updates
        if (tick % 1 == 0) { //Update physics engine every tick
            updateMarple(BaseState::runner.GetCurrentState()->getMarple(), &Gyro);
            ColliderCheck(BaseState::runner.GetCurrentState()->getMarple());
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
