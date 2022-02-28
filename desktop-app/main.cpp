#include <QApplication>

#include "window.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Window window;
    window.setObjectName("Marple Map Maker");
    window.show();
    return a.exec();
}
