//Marple-Tilt Map Creator
//Alasdair Russell, 2315645R
//Part of the Marple-Tilt project
//Built for RTEP group 6, 2022

#ifndef PAINT_H
#define PAINT_H
#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <iostream>
#include <QVector>
#include <vector>
#include <QList>
#include <fstream>
#include <QInputDialog>
#include <QDir>
#include <filesystem>


class Paint : public QWidget
{
Q_OBJECT

public:
    Paint(QWidget *parent = 0);
    ~Paint();

    int element = 0;

    struct coord {
        //Store x coord, y coord, the element it is meant to be and a unique key.
            int x;
            int y;
            int el;
            int key = 0;
            //Key is necessary to group individual coord pixels with the element they belong to.
    };


    QVector<coord> *coordinates;

    void setElement(int el);
    void setColour(QColor colour);
    void setBrushColour(QColor colour);
    int getElement();
    void setBrushSize(int i);
    void borderIn();
    void setMarpleSize(int mSize);
    void resetAll();

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *e);

private:
    void draw(QMouseEvent *e);
    void updateMap(int x, int y);
    bool itemCheck(int x, int y);
    void border();
    void resetElements();

    QColor color;
    QColor brushColor;
    QPixmap *pixmap;
    bool pressed;
    int marpleSize = 3;
    int itemKey = 1;
    int brushSize;

signals:
public slots:
    void writeFile();
};

#endif //PAINT_H
