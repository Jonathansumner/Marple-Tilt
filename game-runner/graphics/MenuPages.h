#pragma once

#include "led-matrix.h"

#include <string.h>
#include <vector>

class MapButton;
class StateButton;
class MarpleTiltMachine;
class GameState;
class MapMenu;

int getOffset(char word[], int spaces);

void drawMenu(rgb_matrix::Canvas *c, char word[]);

void drawMainMenu(rgb_matrix::Canvas *c);

void drawSettingsMenu(rgb_matrix::Canvas *c);

void drawSoundMenu(rgb_matrix::Canvas *c);

void drawBrightnessMenu(rgb_matrix::Canvas *c);

void drawGameplayMenu(rgb_matrix::Canvas *c);

void drawMapMenu(rgb_matrix::Canvas *c, std::vector<std::string> fileList, int pageNum, MapMenu *mm);

void drawCalibrateMenu(rgb_matrix::Canvas *c);

void drawTutorialMenu(rgb_matrix::Canvas *c);

