//Marple-Tilt Map Creator
//Alasdair Russell, 2315645R
//Part of the Marple-Tilt project
//Built for RTEP group 6, 2022

#include "window.h"
#include "Paint.h"
#include "ColourPick.h"

#include <QApplication>
#include <QPushButton>
#include <QTabWidget>
#include <QBoxLayout>
#include <QGridLayout>
#include <QFrame>
#include <QLabel>
#include <iostream>

//Class responsible for building the main window and forming the layout
//of the application.


Window::Window(QWidget *parent) :
        QWidget(parent) {

    //Design of main window itself
    setFixedSize(1200, 800);
    this->setWindowTitle("Marple Tilt Map Creator");
    this->setStyleSheet("background-color: #c0bcde");

    //Frame for the two halfs of the main window.
    QGridLayout *frame = new QGridLayout(this);


    //Widgets to contain left and right window contents.
    QWidget *left = new QWidget;
    left->setFixedSize(640, 640);
    QWidget *right= new QWidget;
    right->setStyleSheet("background-color: #d7d6f0");

    frame->addWidget(left, 0, 0);
    frame->addWidget(right, 0,1);

    //Layout for grid of functional buttons on right side.
    QGridLayout *rightFrame = new QGridLayout(right);
    rightFrame->setSpacing(0);
    rightFrame->setContentsMargins(0, 80, 0, 80);

    //Builds the marple paint screen widget on left of screen.
    Paint *painter = new Paint(left);

    //Hook to Colour picking dialog box for changing brush colour.
    ColourPick *colourPicker = new ColourPick(right);

    //Buttons for choosing which game element is being drawn on the map.
    QPushButton *wall = new QPushButton(right);
    wall->setText("Wall");
    wall->setStyleSheet("background-color: #61d5ff");
    wall->setFixedSize(120,60);
    connect(wall, &QPushButton::released, this, std::bind(&Window::wallMode, this, painter));
    QPushButton *hole = new QPushButton(right);
    hole->setText("Hole");
    hole->setStyleSheet("background-color: #9c9c9c");
    hole->setFixedSize(120,60);
    connect(hole, &QPushButton::released, this, std::bind(&Window::holeMode, this, painter));
    QPushButton *start = new QPushButton(right);
    start->setText("Marple-Start");
    start->setStyleSheet("background-color: #84dd3c");
    start->setFixedSize(120,60);
    connect(start, &QPushButton::released, this, std::bind(&Window::startMode, this, painter));
    QPushButton *end = new QPushButton(right);
    end->setText("End-Goal");
    end->setStyleSheet("background-color: #c15e60");
    end->setFixedSize(120,60);
    connect(end, &QPushButton::released, this, std::bind(&Window::endMode, this, painter));

    //Button that will open dialog box to allow user to change brush colour.
    QPushButton *paintButton = new QPushButton(right);
    connect(paintButton, &QPushButton::released, colourPicker, std::bind(&Window::selectColour, this, painter, colourPicker, wall));
    paintButton->setStyleSheet("background-color: #ffaa7f");
    paintButton->setText("Change Colour");
    paintButton->setFixedSize(120,60);

    //Button that sets brush to eraser.
    QPushButton *eraser = new QPushButton(right);
    connect(eraser, &QPushButton::released, this, std::bind(&Window::erase, this, painter));
    eraser->setStyleSheet("background-color: #fff0ca");
    eraser->setText("Eraser");
    eraser->setFixedSize(120,60);

    //Add the above buttons to the right side grid layout.
    rightFrame->addWidget(wall, 0, 0, Qt::AlignCenter);
    rightFrame->addWidget(hole, 1, 0, Qt::AlignCenter);
    rightFrame->addWidget(start, 2, 0, Qt::AlignCenter);
    rightFrame->addWidget(end, 3, 0, Qt::AlignCenter);
    rightFrame->addWidget(eraser, 4, 0, Qt::AlignCenter);
    rightFrame->addWidget(paintButton,4,1,Qt::AlignCenter);


    //Button to initiate writing the drawn map to a .csv file.
    QPushButton *writeFileButton = new QPushButton(this);
    connect(writeFileButton, &QPushButton::released, painter, &Paint::writeFile);
    writeFileButton->setStyleSheet("background-color: #7fa0de");
    writeFileButton->setText("Save to File");

    //Creates a frame populated with a row of four buttons
    //which are responsible for changing brush size.
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
    connect(oneB, &QPushButton::released, this, std::bind(&Window::setBrushSize, this, painter, 1));
    connect(twoB, &QPushButton::released, this, std::bind(&Window::setBrushSize, this, painter, 2));
    connect(threeB, &QPushButton::released, this, std::bind(&Window::setBrushSize, this, painter, 3));
    connect(fourB, &QPushButton::released, this, std::bind(&Window::setBrushSize, this, painter, 4));

    //Button which will indicate to draw a border around the map with the current brush size.
    QPushButton *borderPush = new QPushButton(right);
    borderPush->setText("Draw Border");
    borderPush->setStyleSheet("background-color: #ffdf6b");
    borderPush->setFixedSize(120,60);
    rightFrame->addWidget(borderPush, 2, 1, Qt::AlignCenter);
    connect(borderPush, &QPushButton::released, this, std::bind(&Window::border, this, painter));

    //Creates a frame populated with a row of four buttons
    //which are responsible for changing marple size.
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
    connect(oneM, &QPushButton::released, this, std::bind(&Window::setMarpleSize, this, painter, 1));
    connect(twoM, &QPushButton::released, this, std::bind(&Window::setMarpleSize, this, painter, 2));
    connect(threeM, &QPushButton::released, this, std::bind(&Window::setMarpleSize, this, painter, 3));
    connect(fourM, &QPushButton::released, this, std::bind(&Window::setMarpleSize, this, painter, 4));

    //Button that a user can use to clear the screen.
    QPushButton *resetButton = new QPushButton(right);
    resetButton->setText("Clear Map");
    resetButton->setStyleSheet("background-color: #c788b3");
    resetButton->setFixedSize(120,60);
    rightFrame->addWidget(resetButton, 3, 1, Qt::AlignCenter);
    connect(resetButton, &QPushButton::released, this, std::bind(&Window::resetAll, this, painter));
}

void::Window::wallMode(Paint *painter){
    //Indicate to painter that we are drawing walls.
    painter->setElement(0);
}

void::Window::holeMode(Paint *painter){
    //Indicate to painter that we are placing holes.
    painter->setElement(1);
    painter->setColour("#000000");
}

void::Window::startMode(Paint *painter){
    //Indicate to painter that we are placing the marple start location.
    painter->setElement(2);
    painter->setColour("#84dd3c");
}

void::Window::endMode(Paint *painter){
    //Indicate to painter that we are placing the end goal.
    painter->setElement(3);
    painter->setColour("#c15e60");
}

void::Window::selectColour(Paint *painter, ColourPick *picker, QPushButton *wall){
    //Open dialog box, take returned colour, give it to painter to change the brush colour.
    //Will not do anything if element is set to eraser.
    //Will also change the colour of the wall button as an indicator of current brush colour.
    int element = painter->getElement();
    if(element != 4){
        QColor colour = picker->onColour();
        painter->setColour(colour);
        painter->setBrushColour(colour);
        wall->setStyleSheet("background-color: "+colour.name());
    }
}

void::Window::erase(Paint *painter){
    //Indicate to painter that we are erasing.
    painter->setColour("#ffffff");
    painter->setElement(4);
}

void::Window::setBrushSize(Paint *painter, int i){
    //Change painter brush size.
    painter->setBrushSize(i);
}

void::Window::border(Paint *painter){
    //Call the painter's border drawing function.
    painter->borderIn();
}

void::Window::setMarpleSize(Paint *painter, int i){
    //Indicate to painter that the marple size is changing.
    //Painter's in-built function will reset non wall elements as they are placed based on marple size.
    painter->setMarpleSize(i);
}

void::Window::resetAll(Paint *painter){
    //Indicate to painter that we are clearing the map.
    painter->resetAll();
}


