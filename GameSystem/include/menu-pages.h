#pragma once

#include "led-matrix.h"

#include <string.h>
#include <vector>

class MapButton;
class StateButton;
class MarpleTiltMachine;
class BaseState;
class MapMenu;
class GameOver;
class Marple;

int getOffset(char word[], int spaces);

void drawMenu(rgb_matrix::Canvas *c, std::string word);

Marple* drawMainMenu(rgb_matrix::Canvas *c);

Marple* drawSettingsMenu(rgb_matrix::Canvas *c);

Marple* drawSoundMenu(rgb_matrix::Canvas *c);

Marple* drawBrightnessMenu(rgb_matrix::Canvas *c);

Marple* drawGameplayMenu(rgb_matrix::Canvas *c);

Marple* drawMapMenu(rgb_matrix::Canvas *c, std::vector<std::string> fileList, int pageNum, MapMenu *mm);

Marple* drawCalibrateMenu(rgb_matrix::Canvas *c);

Marple* drawTutorialMenu(rgb_matrix::Canvas *c);

Marple* drawGameOver(rgb_matrix::Canvas *c, double t);

Marple* drawTutOver(rgb_matrix::Canvas *c);

void drawZone(int x, int y, int d, rgb_matrix::Canvas *c, clock_t t, int tNum);