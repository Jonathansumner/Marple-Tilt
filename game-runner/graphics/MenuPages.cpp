#include "MenuPages.h"
#include <iostream>

int getOffset(char word[], int spaces) {
    int len = strlen(word);

    int offset = 64 - ((len * 4) + (len - 1) + spaces);

    std::cout << offset;
    return offset/2;
}

void drawMainMenu(Canvas *c)
{
    rgb_matrix::Font font;
    font.LoadFont("img/5x8.bdf");
    Color fontColor(60, 170, 50);
    Color borderColor(100, 28, 156);

    char word[] = "Main Menu";
    DrawText(c, font, getOffset(word, 1), 2 + font.height(), fontColor, NULL, word, 0);

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

    char word[] = "Settings";
    DrawText(c, font, getOffset(word, 0), 2 + font.height(), fontColor, NULL, word, 0);
}

void drawSoundMenu(Canvas *c)
{
    Color borderColor(100, 28, 156);
    fillBorder(c, borderColor, 2);

    rgb_matrix::Font font;
    font.LoadFont("img/5x8.bdf");
    Color fontColor(60, 170, 50);

    char word[] = "Sound Menu";
    DrawText(c, font, getOffset(word, 1), 2 + font.height(), fontColor, NULL, word, 0);
}

void drawBrightnessMenu(Canvas *c)
{
    Color borderColor(100, 28, 156);
    fillBorder(c, borderColor, 2);

    rgb_matrix::Font font;
    font.LoadFont("img/5x8.bdf");
    Color fontColor(60, 170, 50);

    char word[] = "Brightness";
    DrawText(c, font, getOffset(word, 0), 2 + font.height(), fontColor, NULL, word, 0);
}

void drawGameplayMenu(Canvas *c)
{
    Color borderColor(100, 28, 156);
    fillBorder(c, borderColor, 2);

    rgb_matrix::Font font;
    font.LoadFont("img/5x8.bdf");
    Color fontColor(60, 170, 50);

    char word[] = "Gameplay";
    DrawText(c, font, getOffset(word, 0), 2 + font.height(), fontColor, NULL, word, 0);
}

void drawTutorialMenu(Canvas *c)
{
    Color borderColor(100, 28, 156);
    fillBorder(c, borderColor, 2);

    rgb_matrix::Font font;
    font.LoadFont("img/5x8.bdf");
    Color fontColor(60, 170, 50);

    char word[] = "Tutorial";
    DrawText(c, font, getOffset(word, 0), 2 + font.height(), fontColor, NULL, word, 0);
}

void drawCalibrateMenu(Canvas *c)
{
    Color borderColor(100, 28, 156);
    fillBorder(c, borderColor, 2);

    rgb_matrix::Font font;
    font.LoadFont("img/5x8.bdf");
    Color fontColor(60, 170, 50);

    char word[] = "Calibrate";
    DrawText(c, font, getOffset(word, 0), 2 + font.height(), fontColor, NULL, word, 0);
}

void drawMapMenu(Canvas *c)
{
    Color borderColor(100, 28, 156);
    fillBorder(c, borderColor, 2);

    rgb_matrix::Font font;
    font.LoadFont("img/5x8.bdf");
    Color fontColor(60, 170, 50);

    char word[] = "Map Menu";
    DrawText(c, font, getOffset(word, 0), 2 + font.height(), fontColor, NULL, word, 0);
}