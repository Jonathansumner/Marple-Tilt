//
// Created by Ali on 30/03/2022.
//

#include "Tab1Content.h"
#include <QWidget>
#include <QGridLayout>
#include <QPushButton>

Tab1Content::Tab1Content(QWidget *parent) :
        QWidget(parent) {

    QGridLayout *frame = new QGridLayout(this);
    QWidget *left = new QWidget;

    QWidget *right= new QWidget;
    QGridLayout *leftFrame = new QGridLayout(left);
    leftFrame->setSpacing(0);
    leftFrame->setContentsMargins(0, 80, 0, 80);
    frame->addWidget(left, 0, 0);
    frame->addWidget(right, 0,1);




    q_buttonA1 = new QPushButton(this);
    q_buttonA1->setFixedSize(300,300);
    q_buttonA1->setStyleSheet("background-color: #d7d6d5");
    q_buttonA2 = new QPushButton(this);
    q_buttonA2->setFixedSize(300,300);
    q_buttonA2->setStyleSheet("background-color: #d7d6d5");

    q_buttonB1 = new QPushButton(this);
    q_buttonB1->setFixedSize(300,300);
    q_buttonB1->setStyleSheet("background-color: #d7d6d5");
    q_buttonB2 = new QPushButton(this);
    q_buttonB2->setFixedSize(300,300);
    q_buttonB2->setStyleSheet("background-color: #d7d6d5");


    leftFrame->addWidget(q_buttonA1, 0, 0, Qt::AlignCenter);
    leftFrame->addWidget(q_buttonA2, 0, 1, Qt::AlignCenter);

    leftFrame->addWidget(q_buttonB1, 1, 0, Qt::AlignCenter);
    leftFrame->addWidget(q_buttonB2, 1, 1, Qt::AlignCenter);

    fresh = new QPushButton(right);
    connect(fresh, &QPushButton::released, this, &Tab1Content::refresh);



}
void Tab1Content::refresh()
{

}

