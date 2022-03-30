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
    leftFrame->setSpacing(0);
    leftFrame->setContentsMargins(0, 80, 0, 80);
    frame->addWidget(left, 0, 0);
    frame->addWidget(right, 0,1);
    QPushButton ref;
    int i,j;
    element = 0;

    for(i=0;i<16;i++){
        for(j=0;j<16;j++){
            buttonArray[i][j] = new QPushButton(this);
            buttonArray[i][j]->setStyleSheet("background-color: #d7d6d5");
            buttonArray[i][j]->setFixedSize(37,37);
            leftFrame->addWidget(buttonArray[i][j], i, j, Qt::AlignCenter);

            connect(buttonArray[i][j], &QPushButton::released, this, std::bind(&Tab2Content::paint, this, buttonArray[i][j]));
        }
    }

}

void::Tab2Content::paint(QPushButton *button){

    if(element == 0){
        button->setStyleSheet("background-color: black");


    }

}