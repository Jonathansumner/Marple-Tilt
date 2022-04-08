#pragma once

#include "led-matrix.h"
#include "graphics.h"
#include "images.h"
#include "gfx.h"

#include <string.h>
#include <vector>

int getOffset(char word[], int spaces);

void drawMainMenu(rgb_matrix::Canvas *c);

void drawSettingsMenu(rgb_matrix::Canvas *c);

void drawSoundMenu(rgb_matrix::Canvas *c);

void drawBrightnessMenu(rgb_matrix::Canvas *c);

void drawGameplayMenu(rgb_matrix::Canvas *c);

void drawMapMenu(rgb_matrix::Canvas *c, std::vector<std::string> fileList, int pageNum);

void drawCalibrateMenu(rgb_matrix::Canvas *c);

void drawTutorialMenu(rgb_matrix::Canvas *c);