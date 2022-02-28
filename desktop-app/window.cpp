#include "window.h"
#include <QApplication>
#include <QPushButton>

Window::Window(QWidget *parent) :
        QWidget(parent) {

    setFixedSize(1200, 800);

    mapBox = new Map(this);


    mapBox->setGeometry(50,50,600,600);
}