//Marple-Tilt Map Creator
//Alasdair Russell, 2315645R
//Part of the Marple-Tilt project
//Built for RTEP group 6, 2022

#ifndef COLOURPICK_H
#define COLOURPICK_H

#include <QWidget>
#include <QDebug>
#include <QColorDialog>

class ColourPick : public QWidget
{
Q_OBJECT
public:
    explicit ColourPick(QWidget *parent);


signals:
public slots:
    QColor onColour();

};

#endif //COLOURPICK_H
