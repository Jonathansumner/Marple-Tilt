#include <led-matrix.h>

#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <signal.h>
#include <iostream>

#include "graphics/gfx.h"
#include "graphics/shapes.h"
//#include <Magick++.h>
//#include <magick/image.h>
//#include <MPU6050.h>

using rgb_matrix::RGBMatrix;
using rgb_matrix::Canvas;

//MPU6050 gyro(0x68);
std::vector<Object *> Object::instances;
Object *screen[64][64];

volatile bool interrupt_received = false;

static void InterruptHandler(int signo) {
    interrupt_received = true;
}

void update() {
    for (Object *obj: Object::instances) {
        switch (obj->getType()) {
            case MARPLE: {
                Object &marp = dynamic_cast<Marple &>(*obj);
                std::cout << marp.blue;
                int d = dynamic_cast<Marple *>(obj)->getDiameter();
                vector<int> pos = dynamic_cast<Marple *>(obj)->getPos();
                fillRect(pos[0], pos[1], d, d, dynamic_cast<Marple *>(obj), screen);
                break;
            }
            case HOLE: {
                Object &hol = dynamic_cast<Hole &>(*obj);
                int d = dynamic_cast<Hole *>(obj)->getDiameter();
                std::cout << hol.blue << "\n";
                fillRect(hol.getPos()[0], hol.getPos()[1], d, d, dynamic_cast<Hole *>(obj), screen);
                break;
            }
        }
    }
}

void render(Canvas *canvas) {
    for (int i = 0; i < 64; i++) {
        for (int j = 0; j < 64; j++) {
            if (screen[i][j]) {
                canvas->SetPixel(i, j, screen[i][j]->red, screen[i][j]->green, screen[i][j]->blue);
            }
        }
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
    defaults.show_refresh_rate = true;
    defaults.brightness = 50;
    Canvas *canvas = RGBMatrix::CreateFromFlags(&argc, &argv, &defaults);
    if (canvas == nullptr)
        return 1;

    signal(SIGTERM, InterruptHandler);
    signal(SIGINT, InterruptHandler);

    Marple marple(20, 20, 5);
    Hole hole(30, 30, 5);
    hole.setColour({255, 0, 0});
    marple.setColour({0, 0, 255});

    update();
    render(canvas);
    usleep(60000000);

    canvas->Clear();
    delete canvas;
    return 0;
}