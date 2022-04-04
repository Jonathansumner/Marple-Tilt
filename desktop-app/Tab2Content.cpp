//
// Created by Ali on 30/03/2022.
//

#include "Tab2Content.h"
#include <QWidget>
#include <QGridLayout>
#include <QPushButton>


Tab2Content::Tab2Content(QWidget *parent) :
        QWidget(parent) {

    QGridLayout *frame = new QGridLayout(this);
    QWidget *left = new QWidget;
    QWidget *right= new QWidget;
    QGridLayout *leftFrame = new QGridLayout(left);
    QGridLayout *rightFrame = new QGridLayout(right);
    leftFrame->setSpacing(0);
    leftFrame->setContentsMargins(0, 80, 0, 80);
    rightFrame->setSpacing(0);
    rightFrame->setContentsMargins(80,80,80,80);
    frame->addWidget(left, 0, 0);
    frame->addWidget(right, 0,1);

    int i,j;
    element = 0;

    hole = new QPushButton(this);
    hole->setStyleSheet("background-color: #565656");
    rightFrame->addWidget(hole,0,0 );
    connect(hole, &QPushButton::released, this, &Tab2Content::holeSet);

    wall = new QPushButton(this);
    wall->setStyleSheet("background-color: blue");
    rightFrame->addWidget(wall,1,0);
    connect(wall, &QPushButton::released, this, &Tab2Content::wallSet);

    start = new QPushButton(this);
    start->setStyleSheet("background-color: green");
    rightFrame->addWidget(start,2,0);
    connect(start, &QPushButton::released, this, &Tab2Content::startSet);

    end = new QPushButton(this);
    end->setStyleSheet("background-color: red");
    rightFrame->addWidget(end,3,0);
    connect(end, &QPushButton::released, this, &Tab2Content::endSet);

    eraser = new QPushButton(this);
    eraser->setStyleSheet("background-color: #d7d6d5");
    rightFrame->addWidget(eraser,4,0);
    connect(eraser, &QPushButton::released, this, &Tab2Content::erase);



    for(i=0;i<16;i++){
        for(j=0;j<16;j++){
            buttonArray[i][j] = new QPushButton(this);
            buttonArray[i][j]->setStyleSheet("background-color: #d7d6d5");
            buttonArray[i][j]->setFixedSize(37,37);
            leftFrame->addWidget(buttonArray[i][j], i, j, Qt::AlignCenter);

            connect(buttonArray[i][j], &QPushButton::released, this, std::bind(&Tab2Content::paint, this, i, j));
        }
    }

}

void::Tab2Content::paint(int i, int j){

    if(element == 1){
        buttonArray[i][j]->setStyleSheet("background-color: #565656");
    }
    if(element == 2){
        buttonArray[i][j]->setStyleSheet("background-color: blue");
    }
    if(element == 3){
        buttonArray[i][j]->setStyleSheet("background-color: green");
    }
    if(element == 4){
        buttonArray[i][j]->setStyleSheet("background-color: red");
    }
    if(element == 0){
        buttonArray[i][j]->setStyleSheet("background-color: #d7d6d5");
    }
}

void::Tab2Content::holeSet(){
    element = 1;
}
void::Tab2Content::wallSet(){
    element = 2;
}
void::Tab2Content::startSet(){
    element = 3;
}
void::Tab2Content::endSet(){
    element = 4;
}

void::Tab2Content::erase(){
    element = 0;
}