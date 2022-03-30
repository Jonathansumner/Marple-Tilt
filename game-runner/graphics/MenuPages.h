#pragma once

#include "led-matrix.h"
#include "graphics.h"
#include "images.h"
#include "shapes.h"

#include <string.h>

using namespace rgb_matrix;

int getOffset(char word[], int spaces);

void drawMainMenu(Canvas *c);

void drawSettingsMenu(Canvas *c);

void drawSoundMenu(Canvas *c);

void drawBrightnessMenu(Canvas *c);

void drawGameplayMenu(Canvas *c);

void drawMapMenu(Canvas *c);

void drawCalibrateMenu(Canvas *c);

void drawTutorialMenu(Canvas *c);