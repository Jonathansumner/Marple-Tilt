#include "window.h"
#include <QApplication>
#include <QPushButton>
#include <QTabWidget>

Window::Window(QWidget *parent) :
        QWidget(parent) {

    setFixedSize(1200, 800);



    QTabWidget *tabBar = new QTabWidget(this);
    QWidget *tab1Content = new QWidget;
    QWidget *tab2Content = new QWidget;
    QWidget *tab3Content = new QWidget;
    QPushButton *q_button = new QPushButton(tab1Content);
    tabBar->setVisible(true);
    tabBar->setGeometry(0, 0, 1200, 800);
    tabBar->insertTab(0, tab1Content, "1");
    tabBar->insertTab(1, tab2Content, "2");
    tabBar->insertTab(2, tab3Content, "3");



}