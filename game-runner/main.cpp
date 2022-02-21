#include <led-matrix.h>

#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <signal.h>
#include <iostream>

#include "graphics/gfx.h"
//#include <Magick++.h>
//#include <magick/image.h>
//#include <MPU6050.h>

using rgb_matrix::RGBMatrix;
using rgb_matrix::Canvas;

//MPU6050 gyro(0x68);
std::vector<Object *> Object::instances;

volatile bool interrupt_received = false;

static void InterruptHandler(int signo) {
    interrupt_received = true;
}

void render(Canvas *canvas) {
    for (auto *obj: Object::instances) {
//        switch (obj->getType()) {
//            case MARPLE:
        if (obj->getType() == MARPLE) {
            std::cout << "Found marple!\n";
            int d = dynamic_cast<Marple *>(obj)->getDiameter();
            int x_pos = obj->getPos()[0];
            int y_pos = obj->getPos()[1];
            for (int w_curr = 0; w_curr < d; w_curr++) {
                for (int h_curr = 0; h_curr < d; h_curr++) {
                    canvas->SetPixel(x_pos + w_curr, y_pos + h_curr, 255, 255, 255);
                }
            }
        }
    }
}
//                break;
//                }
//            case IMAGE:
//                break;
//            case HOLE:
//                break;
//        }
//    }
//}

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

    Marple marple(10, 10, 2); //make a marple at position 1,1 with diameter 2

    for(int rep = 0; rep < 50; rep++) {
        render(canvas);
        std::cout << "Render\n";
        usleep(100000);
//        canvas->Clear();
        marple.move(1, 1);
    }
    canvas->Clear();
    delete canvas;
    return 0;
}