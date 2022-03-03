#include "led-matrix.h"

#include <math.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

#include <exception>
#include <Magick++.h>
#include <magick/image.h>

using rgb_matrix::Canvas;
using rgb_matrix::FrameCanvas;
using rgb_matrix::RGBMatrix;

using ImageVector = std::vector<Magick::Image>;

static ImageVector LoadImageAndScaleImage(const char *filename,
                                          int target_width,
                                          int target_height)
{
    ImageVector result;

    ImageVector frames;
    try
    {
        readImages(&frames, filename);
    }
    catch (std::exception &e)
    {
        if (e.what())
            fprintf(stderr, "%s\n", e.what());
        return result;
    }

    if (frames.empty())
    {
        fprintf(stderr, "No image found.");
        return result;
    }

    // Animated images have partial frames that need to be put together
    if (frames.size() > 1)
    {
        Magick::coalesceImages(&result, frames.begin(), frames.end());
    }
    else
    {
        result.push_back(frames[0]); // just a single still image.
    }

    for (Magick::Image &image : result)
    {
        image.scale(Magick::Geometry(target_width, target_height));
    }

    return result;
}


// Copy an image to a Canvas. Note, the RGBMatrix is implementing the Canvas
// interface as well as the FrameCanvas we use in the double-buffering of the
// animted image.
void CopyImageToCanvas(const Magick::Image &image, Canvas *canvas)
{
    const int offset_x = 0, offset_y = 0; // If you want to move the image.
    // Copy all the pixels to the canvas.
    for (size_t y = 0; y < image.rows(); ++y)
    {
        for (size_t x = 0; x < image.columns(); ++x)
        {
            const Magick::Color &c = image.pixelColor(x, y);
            if (c.alphaQuantum() < 256)
            {
                canvas->SetPixel(x + offset_x, y + offset_y,
                                 ScaleQuantumToChar(c.redQuantum()),
                                 ScaleQuantumToChar(c.greenQuantum()),
                                 ScaleQuantumToChar(c.blueQuantum()));
            }
        }
    }
}

// void ShowAnimatedImage(const ImageVector &images, RGBMatrix *matrix)
// {
//     FrameCanvas *offscreen_canvas = matrix->CreateFrameCanvas();
//     while (!interrupt_received)
//     {
//         for (const auto &image : images)
//         {
//             if (interrupt_received)
//                 break;
//             CopyImageToCanvas(image, offscreen_canvas);
//             offscreen_canvas = matrix->SwapOnVSync(offscreen_canvas);
//             usleep(image.animationDelay() * 10000); // 1/100s converted to usec
//         }
//     }
// }

void drawImage(const char *filename, int duration, char *argv[], Canvas *canvas) {
    Magick::InitializeMagick(*argv);

    ImageVector images = LoadImageAndScaleImage(filename,
                                                canvas->width(),
                                                canvas->height());

    switch (images.size())
    {
    case 0: // failed to load image.
        break;
    case 1: // Simple example: one image to show
        CopyImageToCanvas(images[0], canvas);
        sleep(duration); // Until Ctrl-C is pressed
        break;
    default: // More than one image: this is an animation.
        //ShowAnimatedImage(images, canvas);
        break;
    }

    canvas->Clear();
}
