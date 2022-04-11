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

    drawImage("img/left.png", c, {4, 56, 10, 10});
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

    drawImage("img/sun.png", c, {25, 30, 16, 16});
    drawImage("img/audio.png", c, {45, 30, 16, 16});
    drawImage("img/left.png", c, {4, 56, 10, 10});
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

    drawImage("img/audioup.png", c, {25, 30, 16, 16});
    drawImage("img/audiodown.png", c, {45, 30, 16, 16});
    drawImage("img/left.png", c, {4, 56, 10, 10});
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


    drawImage("img/sun.png", c, {30, 30, 16, 16});
    drawImage("img/left.png", c, {4, 56, 10, 10});
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
    drawImage("img/left.png", c, {4, 56, 10, 10});
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
    drawImage("img/left.png", c, {4, 56, 10, 10});
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

    drawImage("img/left.png", c, {4, 56, 10, 10});
}

void drawMapMenu(Canvas *c, vector<string> files, int pageNum)
{
    Color borderColor(100, 28, 156);
    fillBorder(c, borderColor, 2);

    Font font;
    font.LoadFont("img/5x8.bdf");
    Color fontColor(60, 170, 50);

    Color titleColor(255, 0, 0);

    char word[] = "Map Menu";
    DrawText(c, font, getOffset(word, 0), 2 + font.height(), titleColor, NULL, word, 0);

    int filesLeft = files.size() - (pageNum * 4);

    for (int i=1; i<=filesLeft && i<5; i++) {
        string option = to_string(i + (pageNum * 4)) + " " + files[(i-1) + (pageNum * 4)];
        const char *array = option.c_str();

        DrawText(c, font, 6, 10 + (i*10), fontColor, NULL, array, 0);
    }

    string page = "page " + to_string(pageNum + 1);
    const char *tmp = page.c_str();

    drawImage("img/left.png", c, {4, 56, 10, 10});
    DrawText(c, font, 20, 60, titleColor, NULL, tmp, 0);
    drawImage("img/right.png", c, {52, 56, 10, 10});
}