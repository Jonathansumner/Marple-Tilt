//Marple-Tilt Map Creator
//Alasdair Russell, 2315645R
//Part of the Marple-Tilt project
//Built for RTEP group 6, 2022

#include <windows.h>
#include "window.h"
#include <QApplication>

//Entry point for executable. Builds the main Window and runs the application.

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Window window;
    window.setObjectName("Marple Map Maker");
    window.show();
    return a.exec();
}
