//Marple-Tilt Map Creator
//Alasdair Russell, 2315645R
//Part of the Marple-Tilt project
//Built for RTEP group 6, 2022

#include "Paint.h"

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>

Paint::Paint(QWidget *parent) : QWidget(parent), pressed(0)
{
    color, brushColor = Qt::black;
    pixmap = new QPixmap(64, 64);
    pixmap->fill();
    resize(640, 640);
    coordinates = new QVector<coord>();
    brushSize = 1;
}

Paint::~Paint()
{
    if (pixmap)
        delete pixmap;
}

void Paint::mouseReleaseEvent(QMouseEvent *)
{
    pressed = 0; 
}

void::Paint::setElement(int el){
    //Set internal element for the Painter.
    if(el == 0){
        color = brushColor;
    }
    element = el;
}

void::Paint::setColour(QColor colour){
    //Set internal colour for painter
    //this is distinct from the brush colour as
    //the hole/start/end elements have default
    //colours.
    color = colour;
}

void::Paint::setBrushColour(QColor colour){
    //Change the brush colour, saved as the
    //current selected colour for painting walls.
    //Needs to be stored seperate from the default
    //colour due to the hole/start/end elements.
    brushColor = colour;
}

int::Paint::getElement(){
    //Return the currently selected element.
    return element;
}

void::Paint::setBrushSize(int i){
    //Change internal painter brush size.
    brushSize = i;
}

void::Paint::borderIn(){
    //Public accessor to border drawing function.
    border();
}

void::Paint::setMarpleSize(int mSize){
    //Change painter marple size.
    marpleSize = mSize;
    for(int i = 0; i<20; i++){
        //Don't know why, but sometimes removing elements from the
        //element storage "coordinates" list doesn't completely remove.
        //Works fine when looped a few times. Perhaps inefficient,
        //but this entire app is pretty light.
        resetElements();
        //Important to reset elements as otherwise there will
        //be a disjoint between different elements. Need
        //marple size consistency.
    }

}

void::Paint::resetAll(){
    for(int i = 0; i<20; i++){
    //Looped for the same reasons discussed in setMarpleSize() comments.
        resetElements();
    }
    //Elements are gone, fill() rest of pixels with white.
    pixmap->fill();
    repaint();
}

void::Paint::paintEvent(QPaintEvent *) {
    //Paint onto 640x640 canvas.
    //Based on 64x64 pixel pixmap, so scaling needed later.
    QPainter painter(this);
    painter.drawPixmap(0, 0, pixmap->scaled(640, 640));
}

void::Paint::mousePressEvent(QMouseEvent *e) {
    //Mouse tracking for the pixmap.
    if (e->button() == Qt::RightButton){} //Don't draw on right click.
    else{
        pressed = 1; //Confirm mouse is currently pressed.
        draw(e);     //Run draw function on current mouse event, allows coordinate mapping.
    }
}

void::Paint::mouseMoveEvent(QMouseEvent *e) {
    if(element == 0 or element == 4){          //Only allow painting on mouse movement for wall brush and eraser.
        draw(e);                               //Draw on current mouse event.
    }                                          //The if statement forces the placing of hole/start/end elements as a single click, not a brush.
}

void::Paint::draw(QMouseEvent *e) {
    //Function to handle drawing pixels on the pixmap.
    if (pressed) { //Don't draw if left mouse button isn't clicked.
        QPainter painter(pixmap);
        painter.setPen(color);
        int x = e->pos().x()/10; //Required scaling that was mentioned earlier.
        int y = e->pos().y()/10; //Our 64x64 pixel image is now mapped to the 640x640 painter widget.
        //^Means we can draw a 64x64 map at a size that is usable with useful x/y coords for where we are drawing.

        if(element == 4){//Erasing.
            for(int i = 0; i < brushSize; i++){
                for(int j = 0; j < brushSize; j++){
                    painter.drawPoint(x+i, y-j);
                    //Draw white to "erase". Loop ensures drawing at brush size.
                }
            }
            //If non wall element found, to erase properly it must be removed from storage list.
            if(itemCheck(x,y)){
                int key = 0;
                //Loop to find the key at the current coordinate.
                for(int i = 0; i < coordinates->size(); i++){
                    if((coordinates->at(i).x == x) && (coordinates->at(i).y == y)){
                        key = coordinates->at(i).key;
                    }
                }
                //Loop to remove every coordinate with that key - I.E, each pixel coordinate of the element.
                //For example, for a 3x3 hole, there will be 9 coordinates with that key, all must be removed.
                for(int i = 0; i < coordinates->size(); i++){
                    if(coordinates->at(i).key == key){
                        painter.drawPoint(coordinates->at(i).x, coordinates->at(i).y);
                        coordinates->remove(i);
                    }
                }
            }
        }
        else{//Anything but erasing.
            bool check = false;

            if(element == 0){//Wall element.
                //Check to see if any of the pixels that would be potentially drawn at the brush size don't overlap any fixed elements (hole/start/end).
                for(int i = 0; i < brushSize; i++){
                    for(int j = 0; j < brushSize; j++){
                        if(itemCheck(x+i,y-j)){
                            check = true;
                        }
                    }
                }
                if(!check){  //Can't draw walls over fixed elements.
                    for(int i = 0; i < brushSize; i++){
                        for(int j = 0; j < brushSize; j++){
                            painter.drawPoint(x+i, y-j);
                            //Draw the wall, loop to account for brush size.
                        }
                    }
                }
            }else{//Fixed elements.
                //Have to also makesure that fixed elements don't overlap other fixed elements.
                for(int i = 0; i < marpleSize; i++){
                    for(int j = 0; j < marpleSize; j++){
                        if(itemCheck(x+i,y-j)){
                            check = true;
                        }
                    }
                }
                if(!check){
                    for(int i = 0; i < marpleSize; i++){
                        for(int j = 0; j < marpleSize; j++){
                            painter.drawPoint(x+i, y-j);
                            //Draw a fixed element based on marple size. Call updateMap() to store element coords.
                            updateMap(x+i,y-j);
                        }
                    }
                    itemKey ++; //Iterate key once a fixed element is fully stored. Each element has a unique key.
                }
            }
        }
        repaint(); //Screen update.
    }
}

void::Paint::updateMap(int x, int y){
    //Build a coordinate struct and store in the coordinates vector.
    coord coordinate;
    coordinate.x = x;
    coordinate.y = y;
    coordinate.el = element;
    coordinate.key = itemKey;
    coordinates->append(coordinate);
}

bool::Paint::itemCheck(int x, int y){
    //Will return true if the coordinate is a fixed element.
    bool check = false;

    for(int i = 0; i < coordinates->size(); i++){
        if((coordinates->at(i).x == x) && (coordinates->at(i).y == y)){
            check = true;
        }
    }
    return check;
}

void::Paint::border(){
    //Paint a border based on the brush size.
    QPainter painter(pixmap);
    painter.setPen(color);
    for(int i = 0; i < 64; i++){
        for(int j = 0; j < brushSize; j++){
            painter.drawPoint(0+j, 0+j+i);
            painter.drawPoint(0+j+i, 0+j);
            painter.drawPoint(63-j-i, 63-j);
            painter.drawPoint(63-j, 63-j-i);
        }
    }
    repaint();
}

void::Paint::resetElements(){
    //Remove all elements from paint screen and storage vector.
    //Needed to keep marple size consistency.
    //Can't have a 3x3 marple falling into 1x1 holes.
    QColor colorStore = color;
    color = "#ffffff";
    QPainter painter(pixmap);
    painter.setPen(color);
    int x = 0;
    int y = 0;
    for(int i = 0; i < coordinates->size(); i++){
        x = coordinates->at(i).x;
        y = coordinates->at(i).y;
        painter.drawPoint(x,y);
        coordinates->remove(i);
    }
    color = colorStore;
    repaint();
}

void::Paint::writeFile(){
    //Write the pixmap to a comma separated list file.
    QPixmap map = pixmap->scaled(64, 64);
    QImage im = map.toImage();
    coord coordinate;
    char en = 'W';
    std::string size = std::to_string(marpleSize);
    bool isElement = false;
    bool ok;
    QString mapName = "map";
    //Dialog to receive user specified map name.
    QString text = QInputDialog::getText(this, tr("Write"), tr("File-Name:"), QLineEdit::Normal, mapName, &ok);
    if (ok && !text.isEmpty()){
        mapName = text;
    }
    std::ofstream outFile;
    outFile.open("maps/"+mapName.toStdString()+".csv");
    //Code below used to work out what each pixel is meant to be.
    //Colours from the pixmap itself, elements from the coordinates storage.
    for(int i = 0; i < 64; i++){
        for(int j = 0; j <64; j++){
            for(int n = 0; n < coordinates->size(); n++){
                coordinate = coordinates->at(n);
                if(coordinate.x == j && coordinate.y == i){
                    if(coordinate.el == 1){
                        en = 'H';
                        isElement = true;
                    }
                    if(coordinate.el == 2){
                        en = 'S';
                        isElement = true;
                    }
                    if(coordinate.el == 3){
                        en = 'E';
                        isElement = true;
                    }
                }
            }

            QColor p = im.pixelColor(j,i);
            QString name = p.name();
            if(name.toStdString() == "#ffffff"){
                en = 'N';
            }
            QString outP = name.insert(0,en);
            std::string outPut = outP.toStdString();
            if(isElement){
                //Appends element size to aid processing on board.
                outPut = outPut.append(size);
            }
            outFile << outPut + ",";
            en = 'W';
            isElement = false;
        }
        outFile << "\n";
    }
    outFile.close();
    //Result is a .csv file with 64 columns and 64 rows.
    //Each cell is an individual pixel mapped onto the marple board.
    //Each cell comes with element info.
}
