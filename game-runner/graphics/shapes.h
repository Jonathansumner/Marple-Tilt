#include <cmath>

#ifndef MARPLETILT_SHAPES_H
#define MARPLETILT_SHAPES_H

#endif //MARPLETILT_SHAPES_H


void fillRect(float start_x, float start_y, int w, int h, Object *obj, Object *(&array)[64][64]) {
    int starting_x = (int)std::round(start_x);
    int starting_y = (int)std::round(start_y);
    for (int w_curr = 0; w_curr < w; w_curr++) {
        for (int h_curr = 0; h_curr < h; h_curr++) {
            if ((starting_x + w_curr <= 64) && (starting_x + w_curr >= 0) and (starting_y + h_curr <= 64) && (starting_y + h_curr >= 0)) {
                array[starting_x + w_curr][starting_y + h_curr] = obj;
            }
        }
    }
}
