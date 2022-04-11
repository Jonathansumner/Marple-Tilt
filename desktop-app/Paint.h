//
// Created by Ali on 31/03/2022.
//

#ifndef UNTITLED1_PAINT_H
#define UNTITLED1_PAINT_H
#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <iostream>
#include "ImageInfo.h"
#include <QVector>
#include <vector>
#include <QList>
#include <fstream>


class Paint : public QWidget
{
Q_OBJECT

public:
    Paint(QWidget *parent = 0) : QWidget(parent), pressed(0) {
        color = Qt::black;
        pixmap = new QPixmap(64, 64);
        pixmap->fill();
        resize(640, 640);
        coordinates = new QVector<coord>();


    }
    ~Paint() { if (pixmap) delete pixmap; }

    int element = 0;



    struct coord {
            int x;
            int y;
            int el;
            int key = 0;
    };


    QVector<coord> *coordinates;



    void setElement(int el){
        element = el;
    }

    void setColour(QColor colour){
        color = colour;
    }


protected:
    void paintEvent(QPaintEvent *) {
        QPainter painter(this);
        painter.drawPixmap(0, 0, pixmap->scaled(640, 640));
        //painter.drawPixmap(0, 0, *pixmap);
    }

    void mousePressEvent(QMouseEvent *e) {
        if (e->button() == Qt::RightButton){}

        else {
            pressed = 1;
            draw(e);
        }
    }

    void mouseReleaseEvent(QMouseEvent *) { pressed = 0; }
    void mouseMoveEvent(QMouseEvent *e) {
        if(element == 0){
            draw(e);
        }
    }

private:
    void draw(QMouseEvent *e) {
        if (pressed) {
            QPainter painter(pixmap);
            painter.setPen(color);
            int x = e->pos().x()/10;
            int y = e->pos().y()/10;
            if(element == 0){
                if(!itemCheck(x,y)){
                    painter.drawPoint(x, y);
                }
            }
            else{
                bool check = false;
                //Both of the following nested loops are accounting for the
                //size of the element being placed, a square dictated
                //by the marple size.

                //First nested loop ensures that none of the pixels in the square
                //it will draw for the element are already a piece of another element.

                for(int i = 0; i < marpleSize; i++){
                    for(int j = 0; j < marpleSize; j++){
                        if(itemCheck(x+i,y-j)){
                            check = true;
                        }
                    }
                }

                //Second nested loop will draw the element onto the map and store the
                //coordinates (using updateMap()) assuming the desired square is free.

                if(!check){
                    for(int i = 0; i < marpleSize; i++){
                        for(int j = 0; j < marpleSize; j++){
                            painter.drawPoint(x+i, y-j);
                            updateMap(x+i,y-j);
                        }
                    }
                    itemKey ++;
                }

            }
            repaint();
        }
    }

    void updateMap(int x, int y){
        coord coordinate;
        coordinate.x = x;
        coordinate.y = y;
        coordinate.el = element;
        coordinate.key = itemKey;
        coordinates->append(coordinate);
    }

    bool itemCheck(int x, int y){
        bool check = false;

        for(int i = 0; i < coordinates->size(); i++){
            if((coordinates->at(i).x == x) && (coordinates->at(i).y == y)){
                check = true;
            }
        }
        return check;
    }



    QColor color;
    QPixmap *pixmap;
    bool pressed;

    int marpleSize = 2;
    int itemKey = 1;

signals:
public slots:
    void writeFile(){
        QPixmap map = pixmap->scaled(64, 64);
        QImage im = map.toImage();
        coord coordinate;
        char en = 'W';
        int x = 0;
        int y = 0;
        std::ofstream outFile;
        outFile.open("D:/Marple-Tilt/desktop-app/map.csv");
        for(int i = 0; i < 64; i++){
            for(int j = 0; j <64; j++){
                for(int n = 0; n < coordinates->size(); n++){
                    coordinate = coordinates->at(n);
                    if(coordinate.x == j && coordinate.y == i){
                        if(coordinate.el == 1){
                            en = 'H';
                        }
                        if(coordinate.el == 2){
                            en = 'S';
                        }
                        if(coordinate.el == 3){
                            en = 'E';
                        }
                    }
                }

                QColor p = im.pixelColor(j,i);
                QString name = p.name();
                if(name.toStdString() == "#ffffff"){
                    en = 'N';
                }
                QString outP = name.insert(0,en);
                std::string outPut = outP.toStdString();
                std::cout << outPut;
                std::cout << "  ";
                outFile << outPut + ",";
                en = 'W';
            }

            std::cout << '\n';
            outFile << "\n";
        }
        outFile.close();
    }
};

#endif //UNTITLED1_PAINT_H