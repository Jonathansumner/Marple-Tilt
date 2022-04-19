//Marple-Tilt Map Creator
//Alasdair Russell, 2315645R
//Part of the Marple-Tilt project
//Built for RTEP group 6, 2022

#ifndef WINDOW_H
#define WINDOW_H

#include "Paint.h"
#include "ColourPick.h"

#include <QWidget>
#include <QTabWidget>


class QPushButton;
class QMenuBar;
class paintTab;
class Window : public QWidget {
Q_OBJECT
public:
    explicit Window(QWidget *parent = 0);
    paintTab *painterTab;
    Paint *painter;
    ColourPick *colourPicker;

private:
    QMenuBar *menuBar;
    QPushButton *q_button;
    QTabWidget *tabBar;

signals:
public slots:


private slots:
    void wallMode(Paint *painter);
    void holeMode(Paint *painter);
    void startMode(Paint *painter);
    void endMode(Paint *painter);
    void selectColour(Paint *painter, ColourPick *picker, QPushButton *wall);
    void erase(Paint *painter);
    void setBrushSize(Paint *painter, int i);
    void border(Paint *painter);
    void setMarpleSize(Paint *painter, int i);
    void resetAll(Paint *painter);

};

#endif // WINDOW_H
