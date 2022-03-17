#include "MenuPages.h"

void drawMainMenu(Canvas *c)
{
    rgb_matrix::Font font;
    font.LoadFont("img/5x8.bdf");
    Color fontColor(60, 170, 50);
    Color borderColor(100, 28, 156);

    DrawText(c, font, 10, 2 + font.height(), fontColor, NULL, "Main Menu", 0);

    fillBorder(c, borderColor, 2);

    drawImage("img/play.png", c, {14, 18, 16, 16});

    drawImage("img/question.png", c, {36, 18, 16, 16});

    drawImage("img/compass.png", c, {14, 44, 16, 16});

    // drawImage("img/gears.png", c, {36, 44, 16, 16});
}

void drawSettingsMenu(Canvas *c)
{
    Color borderColor(100, 28, 156);
    fillBorder(c, borderColor, 2);

    rgb_matrix::Font font;
    font.LoadFont("img/5x8.bdf");
    Color fontColor(60, 170, 50);

    DrawText(c, font, 12, 2 + font.height(), fontColor, NULL, "Settings", 0);
}

void drawSoundMenu(Canvas *c)
{
    Color borderColor(100, 28, 156);
    fillBorder(c, borderColor, 2);

    rgb_matrix::Font font;
    font.LoadFont("img/5x8.bdf");
    Color fontColor(60, 170, 50);

    DrawText(c, font, 12, 2 + font.height(), fontColor, NULL, "Sound", 0);
}

void drawBrightnessMenu(Canvas *c)
{
    Color borderColor(100, 28, 156);
    fillBorder(c, borderColor, 2);

    rgb_matrix::Font font;
    font.LoadFont("img/5x8.bdf");
    Color fontColor(60, 170, 50);

    DrawText(c, font, 12, 2 + font.height(), fontColor, NULL, "Brightness", 0);
}

void drawGameplayMenu(Canvas *c)
{
    Color borderColor(100, 28, 156);
    fillBorder(c, borderColor, 2);

    rgb_matrix::Font font;
    font.LoadFont("img/5x8.bdf");
    Color fontColor(60, 170, 50);

    DrawText(c, font, 12, 2 + font.height(), fontColor, NULL, "Gameplay", 0);
}

void drawTutorialMenu(Canvas *c)
{
    Color borderColor(100, 28, 156);
    fillBorder(c, borderColor, 2);
}

void drawCalibrateMenu(Canvas *c)
{
    Color borderColor(100, 28, 156);
    fillBorder(c, borderColor, 2);
}

void drawMapMenu(Canvas *c)
{
    Color borderColor(100, 28, 156);
    fillBorder(c, borderColor, 2);
}