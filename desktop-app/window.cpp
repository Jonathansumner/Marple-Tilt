#include "window.h"
#include <QApplication>
#include <QPushButton>
#include <QTabWidget>
#include <QMenuBar>
#include <QBoxLayout>
#include "Tab1Content.h"
#include "Tab2Content.h"
#include "Tab3Content.h"
#include "Paint.h"
#include "paintTab.h"
#include "ImageInfo.h"
#include <iostream>

Window::Window(QWidget *parent) :
        QWidget(parent) {

    setFixedSize(1200, 800);
    this->setWindowTitle("Marple Tilt Map Creator");



    QMenuBar *menuBar = new QMenuBar(this);



    QTabWidget *tabBar = new QTabWidget(this);
    tabBar->setStyleSheet("background-color: #c0bcde");

    tabBar->setVisible(true);
    tabBar->setGeometry(0, 20, 1200, 800);


    paintTab *painterTab = new paintTab(this);
    painterTab->setStyleSheet("background-color: #c0bcde");
    tabBar->insertTab(1, painterTab, "Paint");
    //Tab1Content *tab1 = new Tab1Content(this, painterTab->painter);
    //tabBar->insertTab(0, tab1, "Marple Size");



}

