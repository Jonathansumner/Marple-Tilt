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
        brushSize = 1;


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

    int getElement(){
        return element;
    }

    void setBrushSize(int i){
        brushSize = i;
    }

    void borderIn(){
        border();
    }

    void setMarpleSize(int mSize){
        marpleSize = mSize;
        for(int i = 0; i<20; i++){
            resetElements();
        }

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
        if(element == 0 or element == 4){
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
            if(element == 4){
                for(int i = 0; i < brushSize; i++){
                    for(int j = 0; j < brushSize; j++){
                        painter.drawPoint(x+i, y-j);
                    }
                }
                if(itemCheck(x,y)){
                    int key = 0;
                    for(int i = 0; i < coordinates->size(); i++){
                        if((coordinates->at(i).x == x) && (coordinates->at(i).y == y)){
                            key = coordinates->at(i).key;
                        }
                    }
                    for(int i = 0; i < coordinates->size(); i++){
                        if(coordinates->at(i).key == key){
                            painter.drawPoint(coordinates->at(i).x, coordinates->at(i).y);
                            coordinates->remove(i);
                        }
                    }
                }


            }

            else{
                bool check = false;

                for(int i = 0; i < brushSize; i++){
                    for(int j = 0; j < brushSize; j++){
                        if(itemCheck(x+i,y-j)){
                            check = true;
                        }
                    }
                }

                if(element == 0){
                    if(!check){
                        for(int i = 0; i < brushSize; i++){
                            for(int j = 0; j < brushSize; j++){
                                painter.drawPoint(x+i, y-j);
                            }
                        }
                    }
                }else{
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

    void border(){
        QPainter painter(pixmap);
        painter.setPen(color);
        for(int i = 0; i < 64; i++){
            for(int j = 0; j < brushSize; j++){
                painter.drawPoint(0+j, 0+j+i);
                painter.drawPoint(0+j+i, 0+j);
                painter.drawPoint(63-j-i, 63-j);
                painter.drawPoint(63-j, 63-j-i);
            }

        }

        repaint();
    }

    void resetElements(){
        QColor colorStore = color;
        color = "#ffffff";
        QPainter painter(pixmap);
        painter.setPen(color);
        int x = 0;
        int y = 0;
        for(int i = 0; i < coordinates->size(); i++){
            x = coordinates->at(i).x;
            y = coordinates->at(i).y;
            painter.drawPoint(x,y);
            coordinates->remove(i);
        }
        if(coordinates->empty()){
            std::cout << "Probably Empty?";
            std::cout << "\n";
        }
        color = colorStore;
        repaint();

    }

    QColor color;
    QPixmap *pixmap;
    bool pressed;
    int marpleSize = 3;
    int itemKey = 1;
    int brushSize;

signals:
public slots:
    void writeFile(){
        QPixmap map = pixmap->scaled(64, 64);
        QImage im = map.toImage();
        coord coordinate;
        char en = 'W';
        std::string size = std::to_string(marpleSize);
        bool isElement = false;
        std::ofstream outFile;
        outFile.open("D:/Marple-Tilt/desktop-app/map.csv");
        for(int i = 0; i < 64; i++){
            for(int j = 0; j <64; j++){
                for(int n = 0; n < coordinates->size(); n++){
                    coordinate = coordinates->at(n);
                    if(coordinate.x == j && coordinate.y == i){
                        if(coordinate.el == 1){
                            en = 'H';
                            isElement = true;

                        }
                        if(coordinate.el == 2){
                            en = 'S';
                            isElement = true;
                        }
                        if(coordinate.el == 3){
                            en = 'E';
                            isElement = true;
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
                if(isElement){
                    outPut = outPut.append(size);
                }

                std::cout << outPut;
                std::cout << "  ";
                outFile << outPut + ",";
                en = 'W';
                isElement = false;
            }

            std::cout << '\n';
            outFile << "\n";
        }
        outFile.close();
    }
};

#endif //UNTITLED1_PAINT_H