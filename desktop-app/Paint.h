//
// Created by Ali on 31/03/2022.
//

#ifndef UNTITLED1_PAINT_H
#define UNTITLED1_PAINT_H
#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#endif //UNTITLED1_PAINT_H
class Paint : public QWidget
{
Q_OBJECT

public:
    Paint(QWidget *parent = 0) : QWidget(parent), pressed(0) {
        color = Qt::black;
        pixmap = new QPixmap(64, 64);
        pixmap->fill();
        resize(640, 640);
    }
    ~Paint() { if (pixmap) delete pixmap; }

protected:
    void paintEvent(QPaintEvent *) {
        QPainter painter(this);
        painter.drawPixmap(0, 0, pixmap->scaled(640, 640));
        //painter.drawPixmap(0, 0, *pixmap);
    }

    void mousePressEvent(QMouseEvent *e) {
        if (e->button() == Qt::RightButton)
            color = color == Qt::black ? Qt::blue : Qt::black;
        else {
            pressed = 1;
            draw(e);
        }
    }

    void mouseReleaseEvent(QMouseEvent *) { pressed = 0; }
    void mouseMoveEvent(QMouseEvent *e) { draw(e); }

private:
    void draw(QMouseEvent *e) {
        if (pressed) {
            QPainter painter(pixmap);
            painter.setPen(color);
            int x = e->pos().x()/10;
            int y = e->pos().y()/10;
            painter.drawPoint(x, y);
            repaint();
        }
    }

    QColor color;
    QPixmap *pixmap;
    bool pressed;
};