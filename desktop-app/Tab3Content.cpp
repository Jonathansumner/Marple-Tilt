//
// Created by Ali on 30/03/2022.
//

#include "Tab3Content.h"
#include <QWidget>
#include <QGridLayout>
#include <QPushButton>

Tab3Content::Tab3Content(QWidget *parent) :
        QWidget(parent) {

    QGridLayout *frame = new QGridLayout(this);
    QWidget *left = new QWidget;

    QWidget *right= new QWidget;
    QGridLayout *leftFrame = new QGridLayout(left);
    leftFrame->setSpacing(0);
    leftFrame->setContentsMargins(0, 80, 0, 80);
    frame->addWidget(left, 0, 0);
    frame->addWidget(right, 0,1);
    int i,j;

    for(i=0;i<32;i++){
        for(j=0;j<32;j++){
            buttonArray[i][j] = new QPushButton(this);
            buttonArray[i][j]->setStyleSheet("background-color: #d7d6d5");
            buttonArray[i][j]->setFixedSize(18,18);
            leftFrame->addWidget(buttonArray[i][j], i, j, Qt::AlignCenter);
        }
    }


}