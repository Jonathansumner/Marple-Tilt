//
// Created by Ali on 11/04/2022.
//

#include "ColourPick.h"

ColourPick::ColourPick(QWidget *parent) :
        QWidget(parent) {


}

QColor ColourPick::onColour()
{
    QColor colour = QColorDialog::getColor(Qt::yellow, this );
    if( colour.isValid() )
    {
        return colour;
    }
}