//Marple-Tilt Map Creator
//Alasdair Russell, 2315645R
//Part of the Marple-Tilt project
//Built for RTEP group 6, 2022

#include "ColourPick.h"

ColourPick::ColourPick(QWidget *parent) :
        QWidget(parent) {
}

//ColourPick class used as an access to inbuilt QT Colour Dialog box.
//Function onColour() will build the dialog box and return the user selected colour.

QColor ColourPick::onColour()
{
    QColor colour = QColorDialog::getColor(Qt::yellow, this );
    if( colour.isValid() )
    {
        return colour;
    }
    else{
        return Qt::black;
    }
}
