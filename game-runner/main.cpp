#include "led-matrix.h"
#include "graphics.h"

#include <cmath>
#include <csignal>
#include <cstdio>
#include <unistd.h>
#include <cstring>

#include "graphics/gfx.h"
#include "graphics/shapes.h"
#include "dynamics/dynamics.h"
#include "MPU6050.h"
#include "graphics/images.h"
#include "graphics/MenuPages.h"

#include <exception>
#include <Magick++.h>
#include <magick/image.h>
#include <iostream>
#include <sys/time.h>

using namespace rgb_matrix;
using rgb_matrix::Canvas;
using rgb_matrix::FrameCanvas;
using rgb_matrix::RGBMatrix;

MPU6050 gyro(0x68);
std::vector<Object *> Object::instances;
Object *Object::frame_prev[64][64];
Object *Object::frame[64][64];

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

void update(bool clear = false) { // Update object references within the matrix array | TODO get advice about handling polymorphic pointer arrays
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
                case WALL:
                    int d = dynamic_cast<Wall *>(obj)->diameter;
                    auto *ref = dynamic_cast<Wall *>(obj);
                    fillRect(obj->getPos()[0], obj->getPos()[1], d, d, ref, Object::frame);
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
                std::cout << "Set pixel: (" << i << "," << j << ") to {0,0,0}\n";
            }
        }
    }
}


void wallTest() {
    Wall *walls[96];

    for (int x = 0; x < 16; x++) {
        walls[x] = new Wall(static_cast<float>(x) * 4, 0, 4);
        walls[x]->setColour({rand() % 255, rand() % 255, rand() % 255});
        walls[x + 16] = new Wall(static_cast<float>(x) * 4, 60, 4);
        walls[x + 16]->setColour({rand() % 255, rand() % 255, rand() % 255});
        walls[x + 32] = new Wall(0, static_cast<float>(x) * 4, 4);
        walls[x + 32]->setColour({rand() % 255, rand() % 255, rand() % 255});
        walls[x + 48] = new Wall(60, static_cast<float>(x) * 4, 4);
        walls[x + 48]->setColour({rand() % 255, rand() % 255, rand() % 255});
    }

    for (int x = 0; x < 8; x++) {
        walls[x + 64] = new Wall(12, 32 + static_cast<float>(x * 4), 4);
        walls[x + 64]->setColour({rand() % 255, rand() % 255, rand() % 255});
        walls[x + 72] = new Wall(24, static_cast<float>(x * 4), 4);
        walls[x + 72]->setColour({rand() % 255, rand() % 255, rand() % 255});
        walls[x + 80] = new Wall(36, 32 + static_cast<float>(x * 4), 4);
        walls[x + 80]->setColour({rand() % 255, rand() % 255, rand() % 255});
        walls[x + 88] = new Wall(48, static_cast<float>(x * 4), 4);
        walls[x + 88]->setColour({rand() % 255, rand() % 255, rand() % 255});
    }
}

int main(int argc, char *argv[]) {

    Magick::InitializeMagick(*argv);
    rgb_matrix::Font font;
    font.LoadFont("img/5x8.bdf");

    RGBMatrix::Options defaults;
//    defaults.show_refresh_rate = true;
    defaults.hardware_mapping = "regular";
    defaults.rows = 64;
    defaults.cols = 64;
    defaults.disable_hardware_pulsing = true;
    defaults.chain_length = 1;
    defaults.parallel = 1;
    defaults.brightness = 50;
    Canvas *canvas = RGBMatrix::CreateFromFlags(&argc, &argv, &defaults);
    if (canvas == nullptr)
        return 1;

    signal(SIGTERM, InterruptHandler);
    signal(SIGINT, InterruptHandler);
    // Test objects
    float x_start = 10, y_start = 10;
    int diameter = 3;
    Marple marple(x_start, y_start, diameter);
    gyro.setOffsets(); //Calibrate gyro
//     wallTest(); // Display test function

//     while (!interrupt_received) { // 60 ticks/updates per second
//         gettimeofday(&t, nullptr);
//         timestamp1 = t.tv_sec * 1000L + (t.tv_usec / 1000L);
//         //Before all updates

//         update(); // copy frame to frame_prev and update frame with new positions
//         render(canvas); // go through prev_frame and frame, draw/clear new/old pixels as appropriate
//         update(true); // copy frame to frame_prev and clear frame for new positions
//         //After display updates

//         updateMarple(&marple, &gyro, false);
//         if (tick % 60 == 0) { //Once per 60 ticks, change marple colour randomly
//             marple.setColour({rand() % 255, rand() % 255, rand() % 255});
//         }
//         //After game updates

//         gettimeofday(&t, nullptr);
//         timestamp2 = t.tv_sec * 1000L + (t.tv_usec / 1000L);
//         elapsed_time = timestamp2 - timestamp1;
//         if (elapsed_time < frame_time) {
//             usleep(frame_time - elapsed_time);
// //            std::cout << "FRAME TIME: " << elapsed_time << "\n";
//         }
//         tick++;
//     }
//     canvas->Clear();
    interrupt_received = false;

    drawImage("img/new_logo.ppm", canvas, {0, 0, canvas->width(), canvas->height()});

    sleep(5);
    canvas->Clear();

    drawMainMenu(canvas);

    update();
    render(canvas);

    sleep(10);
    canvas->Clear();

    drawSettingsMenu(canvas);
    update();
    render(canvas);
    sleep(5);
    canvas->Clear();

    drawBrightnessMenu(canvas);
    update();
    render(canvas);
    sleep(5);
    canvas->Clear();

    drawSoundMenu(canvas);
    update();
    render(canvas);
    sleep(5);
    canvas->Clear();

    drawGameplayMenu(canvas);
    update();
    render(canvas);
    sleep(5);

    std::cout << "Program terminated\n";
    canvas->Clear();
    delete canvas;
    return 0;
}
