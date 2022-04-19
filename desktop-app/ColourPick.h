//
// Created by Ali on 08/04/2022.
//

#ifndef UNTITLED1_COLOURPICK_H
#define UNTITLED1_COLOURPICK_H

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

#endif //UNTITLED1_COLOURPICK_H
