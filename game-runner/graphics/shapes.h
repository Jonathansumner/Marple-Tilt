#ifndef MARPLETILT_SHAPES_H
#define MARPLETILT_SHAPES_H

#endif //MARPLETILT_SHAPES_H

void drawRect(int start_x, int start_y, int w, int h, vector<int>* rgb, rgb_matrix::Canvas *canvas, float brightness=1) {
    for (int w_curr = 0; w_curr < w; w_curr++) {
        for (int h_curr = 0; h_curr < h; h_curr++) {
            canvas->SetPixel(start_x + w_curr, start_y + h_curr, round(rgb->at(0)*brightness), round(rgb->at(1)*brightness), round(rgb->at(2)*brightness));
        }
    }
}
