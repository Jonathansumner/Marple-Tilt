//
// Created by Ali on 28/02/2022.
//

#ifndef MAP_H
#define MAP_H

#include <QWidget>
#include "window.h"
class Window;
class QFrame;
class Map: public QWidget
{
Q_OBJECT
public:
    explicit Map(QWidget *parent);
private:
    QFrame *mapFrame;

};

#endif // MAP_H
