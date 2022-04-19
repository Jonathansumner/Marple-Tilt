#pragma once

#include "led-matrix.h"
using rgb_matrix::Canvas;

void drawImage(const char *filename, Canvas *canvas, std::vector<int> dimensions);