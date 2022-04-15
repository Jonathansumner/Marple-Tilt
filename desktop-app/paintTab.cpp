//
// Created by Ali on 04/04/2022.
//

#include "paintTab.h"
#include <QGridLayout>
#include "Paint.h"
#include <QPushButton>
#include <QFrame>
#include <QLabel>
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

    QFrame *brushFrame = new QFrame(right);
    brushFrame->setWindowIconText("Brush Size");
    rightFrame->addWidget(brushFrame, 0, 1, Qt::AlignCenter);
    QGridLayout *brushSize = new QGridLayout(brushFrame);
    QLabel *brushLabel = new QLabel(brushFrame);
    brushLabel->setText("Brush Size");
    QPushButton *oneB = new QPushButton(right);
    oneB->setText("1");
    oneB->setStyleSheet("background-color: #d5ccf0");
    QPushButton *twoB = new QPushButton(right);
    twoB->setText("2");
    twoB->setStyleSheet("background-color: #d5ccf0");
    QPushButton *threeB = new QPushButton(right);
    threeB->setText("3");
    threeB->setStyleSheet("background-color: #d5ccf0");
    QPushButton *fourB = new QPushButton(right);
    fourB->setText("4");
    fourB->setStyleSheet("background-color: #d5ccf0");
    brushSize->addWidget(oneB, 0, 0, Qt::AlignCenter);
    brushSize->addWidget(twoB, 0, 1, Qt::AlignCenter);
    brushSize->addWidget(threeB, 0, 2, Qt::AlignCenter);
    brushSize->addWidget(fourB, 0, 3, Qt::AlignCenter);
    brushSize->addWidget(brushLabel, 1, 1, Qt::AlignRight);

    connect(oneB, &QPushButton::released, this, std::bind(&paintTab::setBrushSize, this, painter, 1));
    connect(twoB, &QPushButton::released, this, std::bind(&paintTab::setBrushSize, this, painter, 2));
    connect(threeB, &QPushButton::released, this, std::bind(&paintTab::setBrushSize, this, painter, 3));
    connect(fourB, &QPushButton::released, this, std::bind(&paintTab::setBrushSize, this, painter, 4));

    QPushButton *borderPush = new QPushButton(right);
    borderPush->setText("Draw Border");
    borderPush->setStyleSheet("background-color: #ffdf6b");
    borderPush->setFixedSize(120,60);
    rightFrame->addWidget(borderPush, 2, 1, Qt::AlignCenter);
    connect(borderPush, &QPushButton::released, this, std::bind(&paintTab::border, this, painter));

    QFrame *msFrame = new QFrame(right);
    msFrame->setWindowIconText("Brush Size");
    rightFrame->addWidget(msFrame, 1, 1, Qt::AlignCenter);
    QGridLayout *mSize = new QGridLayout(msFrame);
    QLabel *mLabel = new QLabel(msFrame);
    mLabel->setText("Marple-Size: ");
    QLabel *wLabel = new QLabel(msFrame);
    wLabel->setText("(!Will reset non");
    QLabel *dLabel = new QLabel(msFrame);
    dLabel->setText("-wall elements!)");

    QPushButton *oneM = new QPushButton(right);
    oneM->setText("1");
    oneM->setStyleSheet("background-color: #d5ccf0");
    QPushButton *twoM = new QPushButton(right);
    twoM->setText("2");
    twoM->setStyleSheet("background-color: #d5ccf0");
    QPushButton *threeM = new QPushButton(right);
    threeM->setText("3");
    threeM->setStyleSheet("background-color: #d5ccf0");
    QPushButton *fourM = new QPushButton(right);
    fourM->setText("4");
    fourM->setStyleSheet("background-color: #d5ccf0");
    mSize->addWidget(oneM, 0, 0, Qt::AlignCenter);
    mSize->addWidget(twoM, 0, 1, Qt::AlignCenter);
    mSize->addWidget(threeM, 0, 2, Qt::AlignCenter);
    mSize->addWidget(fourM, 0, 3, Qt::AlignCenter);
    mSize->addWidget(mLabel, 1, 1, Qt::AlignRight);
    mSize->addWidget(wLabel, 1, 2, Qt::AlignLeft);
    mSize->addWidget(dLabel, 1, 3, Qt::AlignLeft);

    connect(oneM, &QPushButton::released, this, std::bind(&paintTab::setMarpleSize, this, painter, 1));
    connect(twoM, &QPushButton::released, this, std::bind(&paintTab::setMarpleSize, this, painter, 2));
    connect(threeM, &QPushButton::released, this, std::bind(&paintTab::setMarpleSize, this, painter, 3));
    connect(fourM, &QPushButton::released, this, std::bind(&paintTab::setMarpleSize, this, painter, 4));


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

void::paintTab::setBrushSize(Paint *painter, int i){
    painter->setBrushSize(i);

}

void::paintTab::border(Paint *painter){
    painter->borderIn();
}

void::paintTab::setMarpleSize(Paint *painter, int i){
    painter->setMarpleSize(i);
}