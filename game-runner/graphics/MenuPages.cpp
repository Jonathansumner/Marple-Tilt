#include "MenuPages.h"
#include <iostream>

using namespace rgb_matrix;
using namespace std;

int getOffset(char word[], int spaces) {
    int len = strlen(word);

    int offset = 64 - ((len * 4) + (len - 1) + spaces);

    return offset/2;
}

void drawMainMenu(Canvas *c)
{
    Font font;
    font.LoadFont("img/5x8.bdf");
    Color fontColor(60, 170, 50);
    Color borderColor(100, 28, 156);

    char word[] = "Main Menu";
    DrawText(c, font, getOffset(word, 1), 2 + font.height(), fontColor, NULL, word, 0);

    fillBorder(c, borderColor, 2);

    drawImage("img/play.png", c, {14, 18, 16, 16});

    drawImage("img/question.png", c, {36, 18, 16, 16});

    drawImage("img/compass.png", c, {14, 44, 16, 16});

    drawImage("img/gears.png", c, {36, 44, 16, 16});
}

void drawSettingsMenu(Canvas *c)
{
    Color borderColor(100, 28, 156);
    fillBorder(c, borderColor, 2);

    Font font;
    font.LoadFont("img/5x8.bdf");
    Color fontColor(60, 170, 50);

    char word[] = "Settings";
    DrawText(c, font, getOffset(word, 0), 2 + font.height(), fontColor, NULL, word, 0);
}

void drawSoundMenu(Canvas *c)
{
    Color borderColor(100, 28, 156);
    fillBorder(c, borderColor, 2);

    Font font;
    font.LoadFont("img/5x8.bdf");
    Color fontColor(60, 170, 50);

    char word[] = "Sound Menu";
    DrawText(c, font, getOffset(word, 1), 2 + font.height(), fontColor, NULL, word, 0);
}

void drawBrightnessMenu(Canvas *c)
{
    Color borderColor(100, 28, 156);
    fillBorder(c, borderColor, 2);

    Font font;
    font.LoadFont("img/5x8.bdf");
    Color fontColor(60, 170, 50);

    char word[] = "Brightness";
    DrawText(c, font, getOffset(word, 0), 2 + font.height(), fontColor, NULL, word, 0);
}

void drawGameplayMenu(Canvas *c)
{
    Color borderColor(100, 28, 156);
    fillBorder(c, borderColor, 2);

    Font font;
    font.LoadFont("img/5x8.bdf");
    Color fontColor(60, 170, 50);

    char word[] = "Gameplay";
    DrawText(c, font, getOffset(word, 0), 2 + font.height(), fontColor, NULL, word, 0);
}

void drawTutorialMenu(Canvas *c)
{
    Color borderColor(100, 28, 156);
    fillBorder(c, borderColor, 2);

    Font font;
    font.LoadFont("img/5x8.bdf");
    Color fontColor(60, 170, 50);

    char word[] = "Tutorial";
    DrawText(c, font, getOffset(word, 0), 2 + font.height(), fontColor, NULL, word, 0);
}

void drawCalibrateMenu(Canvas *c)
{
    Color borderColor(100, 28, 156);
    fillBorder(c, borderColor, 2);

    Font font;
    font.LoadFont("img/5x8.bdf");
    Color fontColor(60, 170, 50);

    char word[] = "Calibrate";
    DrawText(c, font, getOffset(word, 0), 2 + font.height(), fontColor, NULL, word, 0);
}

void drawMapMenu(Canvas *c, vector<string> files, int pageNum)
{
    Color borderColor(100, 28, 156);
    fillBorder(c, borderColor, 2);

    Font font;
    font.LoadFont("img/5x8.bdf");
    Color fontColor(60, 170, 50);

    char word[] = "Map Menu";
    DrawText(c, font, getOffset(word, 0), 2 + font.height(), fontColor, NULL, word, 0);

    for (int i=1; i<5; i++) {
        string option = to_string(i) + " " + files[i-1];
        const char *array = option.c_str();

        DrawText(c, font, 6, 12 + (i*10), fontColor, NULL, array, 0);
    }
}