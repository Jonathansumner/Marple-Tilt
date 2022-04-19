//
// Created by Ali on 30/03/2022.
//

#include "Tab1Content.h"
#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include "Paint.cpp"

Tab1Content::Tab1Content(Window *parent, Paint *painter) :
        QWidget(parent) {

    QGridLayout *frame = new QGridLayout(this);
    //QWidget *left = new QWidget;

    //QWidget *right= new QWidget;
    //QGridLayout *leftFrame = new QGridLayout(left);
    //leftFrame->setSpacing(0);
    //leftFrame->setContentsMargins(0, 80, 0, 80);
    //frame->addWidget(left, 0, 0);
    //frame->addWidget(right, 0,1);


    q_button1 = new QPushButton(this);
    q_button1->setFixedSize(300,300);
    q_button1->setStyleSheet("background-color: #d7d6d5");
    q_button1->setText("1x1");
    connect(q_button1, &QPushButton::released, this, std::bind(&Tab1Content::setMarpleSize, this, 1, painter));

    q_button2 = new QPushButton(this);
    q_button2->setFixedSize(300,300);
    q_button2->setStyleSheet("background-color: #d7d6d5");
    q_button2->setText("2x2");
    connect(q_button2, &QPushButton::released, this, std::bind(&Tab1Content::setMarpleSize, this, 2, painter));

    q_button3 = new QPushButton(this);
    q_button3->setFixedSize(300,300);
    q_button3->setStyleSheet("background-color: #d7d6d5");
    q_button3->setText("3x3");
    connect(q_button3, &QPushButton::released, this, std::bind(&Tab1Content::setMarpleSize, this, 3, painter));

    q_button4 = new QPushButton(this);
    q_button4->setFixedSize(300,300);
    q_button4->setStyleSheet("background-color: #d7d6d5");
    q_button4->setText("4x4");
    connect(q_button4, &QPushButton::released, this, std::bind(&Tab1Content::setMarpleSize, this, 4, painter));


    frame->addWidget(q_button1, 0, 0, Qt::AlignCenter);
    frame->addWidget(q_button2, 0, 1, Qt::AlignCenter);

    frame->addWidget(q_button3, 1, 0, Qt::AlignCenter);
    frame->addWidget(q_button4, 1, 1, Qt::AlignCenter);


}

void::Tab1Content::setMarpleSize(int size, Paint *painter){
    painter->setMarpleSize(size);

}