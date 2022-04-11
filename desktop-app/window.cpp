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

    QMenu *fileMenu = menuBar->addMenu(tr("&File"));
    //QPushButton *button = new QPushButton(this);


    QTabWidget *tabBar = new QTabWidget(this);
    tabBar->setStyleSheet("background-color: #c0bcde");
    //Tab1Content *tab1 = new Tab1Content(this);
    //QWidget *tab2 = new Tab2Content(this);
    //QWidget *tab3 = new Tab3Content(this);
    //QWidget *tab4 = new Paint(this);

    //connect(button, &QPushButton::released, this, &Window::writeFile);
    paintTab *tab4 = new paintTab(this);
    tab4->setStyleSheet("background-color: #c0bcde");

    tabBar->setVisible(true);
    tabBar->setGeometry(0, 20, 1200, 800);
    //tabBar->insertTab(0, tab1, "1");
    //tabBar->insertTab(1, tab2, "2");
    //tabBar->insertTab(2, tab3, "3");
    tabBar->insertTab(3, tab4, "Paint");



}

void::Window::writeFile(){
    tab4->writeFile();

}