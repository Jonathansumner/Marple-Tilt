#include "window.h"
#include <QApplication>
#include <QPushButton>
#include <QTabWidget>
#include <QMenuBar>
#include <QBoxLayout>
#include "Tab1Content.h"
#include "Tab3Content.h"

Window::Window(QWidget *parent) :
        QWidget(parent) {

    setFixedSize(1200, 800);
    this->setWindowTitle("Marple Tilt Map Creator");


    QMenuBar *menuBar = new QMenuBar(this);

    QMenu *fileMenu = menuBar->addMenu(tr("&File"));

    QTabWidget *tabBar = new QTabWidget(this);
    Tab1Content *tab1 = new Tab1Content(this);
    QWidget *tab2Content = new QWidget;
    QWidget *tab3 = new Tab3Content(this);

    tabBar->setVisible(true);
    tabBar->setGeometry(0, 20, 1200, 800);
    tabBar->insertTab(0, tab1, "1");
    tabBar->insertTab(1, tab2Content, "2");
    tabBar->insertTab(2, tab3, "3");



}