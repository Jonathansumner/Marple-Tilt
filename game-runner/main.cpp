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
    Marple marple(10, 10, 3);
    fillRect(1, 1, 2, 2, &marple, screen);
}

void render(Canvas *canvas) {
//    for (auto *obj: Object::instances) {
//        if (obj->getType() == MARPLE) { // Object is a Marple
//            int d = dynamic_cast<Marple *>(obj)->getDiameter();
//            int x_pos = obj->getPos()[0];
//            int y_pos = obj->getPos()[1];
//            vector<int> rgb = {255, 255, 255};
//        }
//    }
    for (int i = 0; i < 64; i++) {
        for (int j = 0; j < 64; j++) {
            if (screen[i][j]) {
                std::cout << "set pixel \n";
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

    update();
    render(canvas);
    usleep(60000000);

    canvas->Clear();
    delete canvas;
    return 0;
}