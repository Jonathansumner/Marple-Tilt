#include "map.h"
#include <QFrame>
#include <QHBoxLayout>

Map::Map(QWidget *parent) :
        QWidget(parent) {

    QFrame *mapFrame = new QFrame(this);
    mapFrame->setObjectName("Game Map");
    mapFrame->setVisible(true);
    mapFrame->setStyleSheet("border: 1px solid black");
    mapFrame->setFixedSize(600, 600);

}