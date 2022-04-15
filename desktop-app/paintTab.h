//
// Created by Ali on 04/04/2022.
//


#ifndef UNTITLED1_PAINTTAB_H
#define UNTITLED1_PAINTTAB_H
#include <QWidget>
#include "Paint.h"
#include "ImageInfo.h"
#include <QVector>
#include "ColourPick.h"

class Paint;
class ColourPick;
class QPushButton;
class paintTab: public QWidget {
Q_OBJECT
public:
    explicit paintTab(QWidget *parent);
    Paint *painter;
    ColourPick *colourPicker;



private:



signals:
public slots:
    void writeFile(){painter->writeFile();}

private slots:
    void wallMode(Paint *painter);
    void holeMode(Paint *painter);
    void startMode(Paint *painter);
    void endMode(Paint *painter);
    void selectColour(Paint *painter, ColourPick *picker);
    void erase(Paint *painter);
    void setBrushSize(Paint *painter, int i);
    void border(Paint *painter);
    void setMarpleSize(Paint *painter, int i);
};

#endif //UNTITLED1_PAINTTAB_H