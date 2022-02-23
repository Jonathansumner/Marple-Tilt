#ifndef MARPLETILT_SHAPES_H
#define MARPLETILT_SHAPES_H

#endif //MARPLETILT_SHAPES_H


void fillRect(int start_x, int start_y, int w, int h, Object *obj, Object *(&array)[64][64]) {
    for (int w_curr = 0; w_curr < w; w_curr++) {
        for (int h_curr = 0; h_curr < h; h_curr++) {
            if (start_x + w_curr < 64 and start_y + h_curr < 64) {
                array[start_x + w_curr][start_y + h_curr] = obj;
            }
        }
    }
}
