//
// Created by Ali on 30/03/2022.
//

#ifndef UNTITLED1_TAB3CONTENT_H
#define UNTITLED1_TAB3CONTENT_H
#include <QWidget>
class QPushButton;
class Tab3Content: public QWidget {
    Q_OBJECT
public:
    explicit Tab3Content(QWidget *parent);

private:
    QPushButton *buttonArray[32][32];
signals:
public slots:
private slots:

};


#endif //UNTITLED1_TAB3CONTENT_H
