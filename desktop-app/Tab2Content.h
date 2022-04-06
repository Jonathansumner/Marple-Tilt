//
// Created by Ali on 30/03/2022.
//

#ifndef UNTITLED1_TAB2CONTENT_H
#define UNTITLED1_TAB2CONTENT_H
#include <QWidget>
class QPushButton;

class Tab2Content: public QWidget {
Q_OBJECT
public:
    explicit Tab2Content(QWidget *parent);

private:
    QPushButton *buttonArray[16][16];
    QPushButton *hole;
    QPushButton *wall;
    QPushButton *start;
    QPushButton *end;
    QPushButton *eraser;
    int element;
signals:
public slots:
private slots:
    void paint(int i, int j);
    void holeSet();
    void wallSet();
    void startSet();
    void endSet();
    void erase();
};


#endif //UNTITLED1_TAB2CONTENT_H
