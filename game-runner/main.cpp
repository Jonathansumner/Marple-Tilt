#include <led-matrix.h>

#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <signal.h>
//#include <Magick++.h>
//#include <magick/image.h>
//#include <MPU6050.h>

using rgb_matrix::RGBMatrix;
using rgb_matrix::Canvas;

//MPU6050 gyro(0x68);

volatile bool interrupt_received = false;
static void InterruptHandler(int signo) {
    interrupt_received = true;
}

static void DrawOnCanvas(Canvas *canvas) {
    /*
     * Let's create a simple animation. We use the canvas to draw
     * pixels. We wait between each step to have a slower animation.
     */

    int center_x = canvas->width() / 2;
    int center_y = canvas->height() / 2;
    float radius_max = canvas->width() / 2;
    float angle_step = 1.0 / 360;
    for (float a = 0, r = 0; r < radius_max; a += angle_step, r += angle_step) {
        if (interrupt_received)
            return;
        float dot_x = cos(a * 2 * M_PI) * r;
        float dot_y = sin(a * 2 * M_PI) * r;
        canvas->SetPixel(center_x + dot_x, center_y + dot_y,
                         255, 0, 0);
        usleep(1 * 1000);  // wait a little to slow down things.
    }
}

int main(int argc, char *argv[]) {
    float ax, ay, az, gr, gp, gy;
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
    if (canvas == NULL)
        return 1;

    // It is always good to set up a signal handler to cleanly exit when we
    // receive a CTRL-C for instance. The DrawOnCanvas() routine is looking
    // for that.
    signal(SIGTERM, InterruptHandler);
    signal(SIGINT, InterruptHandler);

    DrawOnCanvas(canvas);    // Using the canvas
//    while (1) {
//        gyro.getAngle(0, &gr);
//        gyro.getAngle(1, &gp);
//        gyro.getAngle(2, &gy);
//        std::cout << "Gyro output: " << gr << gp << gy << "\n";
//        usleep(250000); //0.25sec
//    }

    // Animation finished. Shut down the RGB matrix.
    canvas->Clear();
    delete canvas;

    return 0;
}