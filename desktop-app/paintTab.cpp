//
// Created by Ali on 04/04/2022.
//

#include "paintTab.h"
#include <QGridLayout>
#include "Paint.h"
#include <QPushButton>
#include "ColourPick.h"

paintTab::paintTab(QWidget *parent) :
        QWidget(parent) {

    QGridLayout *frame = new QGridLayout(this);

    QWidget *left = new QWidget;
    left->setFixedSize(640, 640);

    QWidget *right= new QWidget;
    right->setStyleSheet("background-color: #d7d6f0");

    QGridLayout *rightFrame = new QGridLayout(right);
    rightFrame->setSpacing(0);
    rightFrame->setContentsMargins(0, 80, 0, 80);

    Paint *painter = new Paint(left);
    ColourPick *colourPicker = new ColourPick(right);

    QPushButton *wall = new QPushButton(right);
    wall->setText("Wall");
    wall->setStyleSheet("background-color: #61d5ff");
    wall->setFixedSize(120,60);
    connect(wall, &QPushButton::released, this, std::bind(&paintTab::wallMode, this, painter));
    QPushButton *hole = new QPushButton(right);
    hole->setText("Hole");
    hole->setStyleSheet("background-color: #9c9c9c");
    hole->setFixedSize(120,60);
    connect(hole, &QPushButton::released, this, std::bind(&paintTab::holeMode, this, painter));
    QPushButton *start = new QPushButton(right);
    start->setText("Marple-Start");
    start->setStyleSheet("background-color: #84dd3c");
    start->setFixedSize(120,60);
    connect(start, &QPushButton::released, this, std::bind(&paintTab::startMode, this, painter));
    QPushButton *end = new QPushButton(right);
    end->setText("End-Goal");
    end->setStyleSheet("background-color: #c15e60");
    end->setFixedSize(120,60);
    connect(end, &QPushButton::released, this, std::bind(&paintTab::endMode, this, painter));

    QPushButton *paintButton = new QPushButton(right);
    connect(paintButton, &QPushButton::released, colourPicker, std::bind(&paintTab::selectColour, this, painter, colourPicker));
    paintButton->setStyleSheet("background-color: #ffaa7f");
    paintButton->setText("Change Colour");
    paintButton->setFixedSize(120,60);

    QPushButton *eraser = new QPushButton(right);
    connect(eraser, &QPushButton::released, this, std::bind(&paintTab::erase, this, painter));
    eraser->setStyleSheet("background-color: #fff0ca");
    eraser->setText("Eraser");
    eraser->setFixedSize(120,60);

    rightFrame->addWidget(wall, 0, 0, Qt::AlignCenter);
    rightFrame->addWidget(hole, 1, 0, Qt::AlignCenter);
    rightFrame->addWidget(start, 2, 0, Qt::AlignCenter);
    rightFrame->addWidget(end, 3, 0, Qt::AlignCenter);
    rightFrame->addWidget(eraser, 4, 0, Qt::AlignCenter);
    rightFrame->addWidget(paintButton,4,1,Qt::AlignCenter);

    frame->addWidget(left, 0, 0);
    frame->addWidget(right, 0,1);

    QPushButton *writeFileButton = new QPushButton(this);
    connect(writeFileButton, &QPushButton::released, painter, &Paint::writeFile);
    writeFileButton->setStyleSheet("background-color: #7fa0de");
    writeFileButton->setText("Save to File");
}

void::paintTab::wallMode(Paint *painter){
    painter->setElement(0);
    painter->setColour("#61d5ff");
}

void::paintTab::holeMode(Paint *painter){
    painter->setElement(1);
    painter->setColour("#000000");
}

void::paintTab::startMode(Paint *painter){
    painter->setElement(2);
    painter->setColour("#84dd3c");
}

void::paintTab::endMode(Paint *painter){
    painter->setElement(3);
    painter->setColour("#c15e60");
}

void::paintTab::selectColour(Paint *painter, ColourPick *picker){
    int element = painter->getElement();
    if(element != 4){
        painter->setColour(picker->onColour());
    }
}

void::paintTab::erase(Paint *painter){
    painter->setColour("#ffffff");
    painter->setElement(4);
}