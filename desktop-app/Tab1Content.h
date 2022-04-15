//
// Created by Ali on 30/03/2022.
//

#ifndef UNTITLED1_TAB1CONTENT_H
#define UNTITLED1_TAB1CONTENT_H
#include <QWidget>
#include "window.h"
#include "Paint.h"

class QPushButton;
class Tab1Content: public QWidget {
    Q_OBJECT
public:
    explicit Tab1Content(Window *parent, Paint *painter);
    int marpleSize = 0;
private:

    QPushButton *q_button1;
    QPushButton *q_button2;
    QPushButton *q_button3;
    QPushButton *q_button4;

signals:
public slots:
    void setMarpleSize(int size, Paint *painter);
private slots:

};


#endif //UNTITLED1_TAB1CONTENT_H
