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
    int element;
signals:
public slots:
private slots:
    void paint(QPushButton *button);
};


#endif //UNTITLED1_TAB2CONTENT_H
