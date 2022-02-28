//
// Created by Ali on 28/02/2022.
//

#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include "map.h"

class QPushButton;
class Map;
class Window : public QWidget
{
Q_OBJECT
public:
    explicit Window(QWidget *parent = 0);
private:
    QPushButton *q_button;
    Map *mapBox;
signals:
public slots:
};

#endif // WINDOW_H