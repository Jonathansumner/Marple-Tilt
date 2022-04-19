#include "led-matrix.h"
#include "game-objects.h"

void gyroTest(Canvas *canvas, Marple *marple, float weighting_factor = 3)
{
    while (!interrupt_received)
    {
        float x, y, z;
        Gyro.getAccel(&x, &y, &z);
        if (x >= 2 or x <= -2)
            x = 0; // clip outliers
        if (y >= 2 or y <= -2)
            y = 0;
        if (z >= 2 or z <= -2)
            z = 0;
        marple->x_acceleration = x * weighting_factor;
        marple->y_acceleration = y * weighting_factor;
        if (marple->x_acceleration > 0)
        {
            for (int b = 0; b < std::round(marple->x_acceleration); b++)
            {
                canvas->SetPixel(32 + b, 31, 0, 255, 0);
                canvas->SetPixel(32 + b, 32, 0, 255, 0);
                canvas->SetPixel(32 + b, 33, 0, 255, 0);
            }
        }
        if (marple->x_acceleration < 0)
        {
            for (int b = 0; b > std::round(marple->x_acceleration); b--)
            {
                canvas->SetPixel(32 + b, 31, 0, 255, 0);
                canvas->SetPixel(32 + b, 32, 0, 255, 0);
                canvas->SetPixel(32 + b, 33, 0, 255, 0);
            }
        }
        if (marple->y_acceleration < 0)
        {
            for (int b = 0; b > std::round(marple->y_acceleration); b--)
            {
                canvas->SetPixel(31, 32 + b, 0, 0, 255);
                canvas->SetPixel(32, 32 + b, 0, 0, 255);
                canvas->SetPixel(33, 32 + b, 0, 0, 255);
            }
        }
        if (marple->y_acceleration > 0)
        {
            for (int b = 0; b < std::round(marple->y_acceleration); b++)
            {
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

void wallTest(bool border = true, bool wall = true)
{
    Wall *walls[96];
    vector<int> colours = {0, 100, 255};
    if (border)
    {
        for (int x = 0; x < 16; x++)
        {
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
    if (wall)
    {
        for (int x = 0; x < 8; x++)
        {
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