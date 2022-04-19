//
// Created by Ali on 04/04/2022.
//

#ifndef UNTITLED1_IMAGEINFO_H
#define UNTITLED1_IMAGEINFO_H


class ImageInfo {
private:
    int *pixGrid[64][64];

public:
    ImageInfo(){
        for(int i; i<64; i++){
            for(int j; j<64; j++){
                pixGrid[64][64] = 0;
            }
        }
    }
    int* readPixGrid(int x, int y){
        return pixGrid[x][y];
    }
    void writePixGrid(int x, int y, int element){
        pixGrid[x][y] = &element;
    }
};


#endif //UNTITLED1_IMAGEINFO_H
