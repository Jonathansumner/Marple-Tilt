//
// Created by Ali on 30/03/2022.
//

#ifndef UNTITLED1_TAB1CONTENT_H
#define UNTITLED1_TAB1CONTENT_H
#include <QWidget>

class QPushButton;
class Tab1Content: public QWidget {
    Q_OBJECT
public:
    explicit Tab1Content(QWidget *parent);
private:
    QPushButton *fresh;
    QPushButton *q_buttonA1;
    QPushButton *q_buttonA2;
    QPushButton *q_buttonB1;
    QPushButton *q_buttonB2;

signals:
public slots:
private slots:
    void refresh();
};


#endif //UNTITLED1_TAB1CONTENT_H
