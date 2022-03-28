#ifndef MARPLETILT_SEQUENCES_H
#define MARPLETILT_SEQUENCES_H

#endif

#include "led-matrix.h"
#include "graphics.h"
#include "images.h"
#include "shapes.h"

using namespace rgb_matrix;

void drawMainMenu(Canvas *c, char *argv[]) {

    rgb_matrix::Font font;
    font.LoadFont("img/5x8.bdf");
    Color fontColor(60, 170, 50);
    Color borderColor(100, 28, 156);

    DrawText(c, font, 10, 2 + font.height(), fontColor, NULL, "Main Menu", 0);

    fillBorder(c, borderColor, 2);

    int pDims[4] = {14, 18, 16, 16};
    drawImage("img/play.png", 10, argv, c, pDims);

    int qDims[4] = {36, 18, 16, 16};
    drawImage("img/question.png", 10, argv, c, qDims);

    int cDims[4] = {14, 44, 16, 16};
    drawImage("img/compass.png", 10, argv, c, cDims);

    //int sDims[4] = {36, 44, 16, 16};
    //drawImage("img/gears.png", 10, argv, c, sDims);
}

void drawSettings(Canvas *c, char *argv[]) {
    rgb_matrix::Font font;
    font.LoadFont("img/5x8.bdf");
    Color fontColor(60, 170, 50);

    DrawText(c, font, 12, 2 + font.height(), fontColor, NULL, "Settings", 0);
}