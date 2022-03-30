//
// Created by Ali on 28/02/2022.
//

#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include "map.h"
#include <QTabWidget>

class QPushButton;
class QMenuBar;
class Window : public QWidget {
Q_OBJECT
public:
    explicit Window(QWidget *parent = 0);
private:
    QMenuBar *menuBar;
    QPushButton *q_button;
    QWidget *tab1Content;
    QWidget *tab2Content;
    QWidget *tab3Content;
    QTabWidget *tabBar;

signals:
public slots:
};

#endif // WINDOW_H