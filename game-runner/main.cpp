#include <led-matrix.h>

#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <signal.h>
#include <iostream>

#include "gfx.h"
//#include <Magick++.h>
//#include <magick/image.h>
//#include <MPU6050.h>

using rgb_matrix::RGBMatrix;
using rgb_matrix::Canvas;

//MPU6050 gyro(0x68);
std::vector<Object> Object::instances;

volatile bool interrupt_received = false;
static void InterruptHandler(int signo) {
    interrupt_received = true;
}


int main(int argc, char *argv[]) {
    RGBMatrix::Options defaults;
    defaults.hardware_mapping = "regular";  // or e.g. "adafruit-hat"
    defaults.rows = 64;
    defaults.cols = 64;
    defaults.disable_hardware_pulsing=true;
    defaults.chain_length = 1;
    defaults.parallel = 1;
    defaults.show_refresh_rate = true;
    defaults.brightness = 50;
    Canvas *canvas = RGBMatrix::CreateFromFlags(&argc, &argv, &defaults);
    if (canvas == nullptr)
        return 1;

    signal(SIGTERM, InterruptHandler);
    signal(SIGINT, InterruptHandler);

    Object bing(1,1, IMAGE); //make generic image object at position 1,1
    Marple marple(1, 1, 2, MARPLE); //make a marple at position 1,1 with diameter 2
    std::cout << marple.getPos().capacity();
    canvas->Clear();
    delete canvas;
    return 0;
}