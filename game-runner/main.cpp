#include "led-matrix.h"

#include <cmath>
#include <csignal>
#include <cstdio>
#include <unistd.h>

#include "graphics/gfx.h"
#include "graphics/shapes.h"
#include "MPU6050.h"
#include "images.h"

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
struct timeval t;
long long frame_time = 16666; //time period for 60Hz in useconds


static void InterruptHandler(int signo) {
    interrupt_received = true;
}

void update() { // Update object references within the matrix array                     //TODO get advice about handling polymorphic pointer arrays
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

void wallTest(Canvas *canvas) {
    Marple marple(20, 20, 3);
    Hole hole(30, 30, 5);
    hole.setColour({255, 0, 0});
    marple.setColour({0, 0, 255});
    Wall *walls[64];
    for (int x = 0; x < 16; x++) {
        walls[x] = new Wall(x * 4, 0, 4);
        walls[x]->setColour({rand() % 255, rand() % 255, rand() % 255});
    }
    for (int x = 16; x < 32; x++) {
        walls[x] = new Wall((x - 16) * 4, 60, 4);
        walls[x]->setColour({rand() % 255, rand() % 255, rand() % 255});
    }
    for (int x = 32; x < 48; x++) {
        walls[x] = new Wall(0, (x - 32) * 4, 4);
        walls[x]->setColour({rand() % 255, rand() % 255, rand() % 255});
    }
    for (int x = 48; x < 64; x++) {
        walls[x] = new Wall(60, (x - 48) * 4, 4);
        walls[x]->setColour({rand() % 255, rand() % 255, rand() % 255});
    }
    update(); // update matrix array from object list
    render(canvas); // draw from matrix array
    usleep(60000000);
}

int main(int argc, char *argv[]) {
    RGBMatrix::Options defaults;
    defaults.hardware_mapping = "regular";  // or e.g. "adafruit-hat"
    defaults.rows = 64;
    defaults.cols = 64;
    defaults.disable_hardwvoid ShowAnimatedImage(const ImageVector &images, RGBMatrix *matrix)
    {
        FrameCanvas *offscreen_canvas = matrix->CreateFrameCanvas();
        while (!interrupt_received)
        {
            for (const auto &image : images)
            {
                if (interrupt_received)
                    break;
                CopyImageToCanvas(image, offscreen_canvas);
                offscreen_canvas = matrix->SwapOnVSync(offscreen_canvas);
                usleep(image.animationDelay() * 10000); // 1/100s converted to usec
            }
        }
    }
    are_pulsing = true;
    defaults.chain_length = 1;
    defaults.parallel = 1;
    defaults.show_refresh_rate = true;
    defaults.brightness = 50;
    Canvas *canvas = RGBMatrix::CreateFromFlags(&argc, &argv, &defaults);
    if (canvas == nullptr)
        return 1;

    signal(SIGTERM, InterruptHandler);
    signal(SIGINT, InterruptHandler);
    float a, b, c;
//    wallTest(canvas); // Display test function

    while (!interrupt_received) {
        gettimeofday(&t, nullptr);
        timestamp1 = t.tv_sec*1000L + (t.tv_usec/1000L);
        //Before game updates
        gyro.getAngle(0, &a);
        gyro.getAngle(1, &b);
        gyro.getAngle(2, &c);
        std::cout << "Gyroscope angles: X: " << a << ", Y: " << b << ", Z: " << c << "\n";
        update();
        render(canvas);
        @id : ms - vscode.cpptools - extension - pack
                                                     // After game updates
                                                     gettimeofday(&t, nullptr);
        timestamp2 = t.tv_sec*1000L + (t.tv_usec/1000L);
        elapsed_time = timestamp2 - timestamp1;
        if (elapsed_time < frame_time) {
            usleep(frame_time - elapsed_time);
        }
        canvas->Clear();
    }

    drawImage("img/logo.ppm", 5, argv, canvas);

    std::cout << "Program terminated\n";
    canvas->Clear();
    delete canvas;
    return 0;
}
