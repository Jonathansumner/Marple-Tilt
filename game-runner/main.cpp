#include "led-matrix.h"

#include <cmath>
#include <csignal>
#include <cstdio>
#include <unistd.h>

#include "graphics/gfx.h"
#include "graphics/shapes.h"
#include "dynamics/dynamics.h"
#include "MPU6050.h"

#include <exception>
#include <Magick++.h>
#include <magick/image.h>
#include <iostream>
#include <sys/time.h>

using rgb_matrix::Canvas;
using rgb_matrix::FrameCanvas;
using rgb_matrix::RGBMatrix;

MPU6050 gyro(0x68);
std::vector<Object *> Object::instances;
Object *screen[64][64];

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

void
update() { // Update object references within the matrix array                     //TODO get advice about handling polymorphic pointer arrays
    for (Object *obj: Object::instances) {
        if (obj) {
            switch (obj->getType()) {
                case MARPLE: {
//                Object &marp = dynamic_cast<Marple &>(*obj);
                    int d = dynamic_cast<Marple *>(obj)->getDiameter();
                    fillRect(obj->getPos()[0], obj->getPos()[1], d, d, dynamic_cast<Marple *>(obj), screen);
                    break;
                }
                case HOLE: {
                    int d = dynamic_cast<Hole *>(obj)->getDiameter();
                    fillRect(obj->getPos()[0], obj->getPos()[1], d, d, dynamic_cast<Hole *>(obj), screen);
                    break;
                }
                case WALL:
                    int d = dynamic_cast<Wall *>(obj)->diameter;
                    fillRect(obj->getPos()[0], obj->getPos()[1], d, d, dynamic_cast<Wall *>(obj), screen);
                    break;
            }
        }
    }
}

void render(Canvas *canvas) { // render each pixel with respect to the object reference
    for (int i = 0; i < 64; i++) {
        for (int j = 0; j < 64; j++) {
            if (screen[i][j]) {
                canvas->SetPixel(i, j, screen[i][j]->red, screen[i][j]->green, screen[i][j]->blue);
            }
        }
    }
}

void clear(Canvas *canvas) { //TODO: find more efficient method of clearing array
    canvas->Clear();
    for (int x = 0; x < 64; x++) {
        for (int y = 0; y < 64; y++) {
            screen[x][y] = nullptr;
        }
    }
}

void wallTest() {
//    Hole hole(30, 30, 5);
//    hole.setColour({255, 0, 0});
    Wall *walls[64];
//    Wall *snake1[64];
//    Wall *snake2[64];
//    Wall *snake3[64];
    walls[0] = new Wall(0, 0, 4);
    for (int x = 1; x < 16; x++) {
        walls[x] = new Wall(static_cast<float>(x) * 4, 0, 4);
        walls[x]->setColour({rand() % 255, rand() % 255, rand() % 255});
    }
    for (int x = 16; x < 32; x++) {
        walls[x] = new Wall(static_cast<float>(x - 16) * 4, 60, 4);
        walls[x]->setColour({rand() % 255, rand() % 255, rand() % 255});
    }
    for (int x = 32; x < 48; x++) {
        walls[x] = new Wall(0, static_cast<float>(x - 32) * 4, 4);
        walls[x]->setColour({rand() % 255, rand() % 255, rand() % 255});
    }
    for (int x = 48; x < 64; x++) {
        walls[x] = new Wall(60, static_cast<float>(x - 48) * 4, 4);
        walls[x]->setColour({rand() % 255, rand() % 255, rand() % 255});
    }
    for (int x = 0; x < 8; x++) {
        snake1[x] = new Wall(18, static_cast<float>(x * 4), 4);
        snake1[x]->setColour({rand() % 255, rand() % 255, rand() % 255});
    }
    for (int x = 0; x < 8; x++) {
        snake2[x] = new Wall(36, static_cast<float>(x * 4), 4);
        snake2[x]->setColour({rand() % 255, rand() % 255, rand() % 255});
    }
    for (int x = 0; x < 8; x++) {
        snake3[x] = new Wall(48, static_cast<float>(x * 4), 4);
        snake3[x]->setColour({rand() % 255, rand() % 255, rand() % 255});
    }
}

int main(int argc, char *argv[]) {
    RGBMatrix::Options defaults;
    defaults.hardware_mapping = "regular";  // or e.g. "adafruit-hat"
    defaults.rows = 64;
    defaults.cols = 64;
    defaults.disable_hardware_pulsing = true;
    defaults.chain_length = 1;
    defaults.parallel = 1;
//    defaults.show_refresh_rate = true;
    defaults.brightness = 50;
    Canvas *canvas = RGBMatrix::CreateFromFlags(&argc, &argv, &defaults);
    if (canvas == nullptr)
        return 1;

    signal(SIGTERM, InterruptHandler);
    signal(SIGINT, InterruptHandler);
    // Test objects
    int x_start = 10, y_start = 10, diameter = 3;
    Marple marple(x_start, y_start, diameter);

    wallTest(); // Display test function
    std::cout << "before offset\n";
    std::cout << "Offsets set: " << gyro.setOffsets() << "\n";
    while (!interrupt_received) {
        gettimeofday(&t, nullptr);
        timestamp1 = t.tv_sec * 1000L + (t.tv_usec / 1000L);
        //Before game updates

        updateMarple(&marple, &gyro);
        update();
        render(canvas);
        if (tick % 60 == 0) {
            marple.setColour({rand() % 255, rand() % 255, rand() % 255});
        }

        //After game updates
        gettimeofday(&t, nullptr);
        timestamp2 = t.tv_sec * 1000L + (t.tv_usec / 1000L);
        elapsed_time = timestamp2 - timestamp1;
        if (elapsed_time < frame_time) {
            usleep(frame_time - elapsed_time);
        }
        clear(canvas);
        tick++;
    }
    std::cout << "\nProgram terminated\n";
    canvas->Clear();
    delete canvas;
    return 0;
}
