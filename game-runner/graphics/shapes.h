#ifndef MARPLETILT_SHAPES_H
#define MARPLETILT_SHAPES_H

#endif //MARPLETILT_SHAPES_H

//#include <led-matrix.h>

void drawRect(int start_x, int start_y, int end_x, int end_y, vector<int>* rgb, rgb_matrix::Canvas *canvas) {
    for (int w_curr = 0; w_curr < end_x; w_curr++) {
        for (int h_curr = 0; h_curr < end_y; h_curr++) {
            canvas->SetPixel(start_x + w_curr, start_y + h_curr, rgb->at(0), rgb->at(1), rgb->at(2));
        }
    }
}
