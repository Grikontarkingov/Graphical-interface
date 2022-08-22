#ifndef RECTS_H
#define RECTS_H

#include "qbrush.h"
#include <QObject>
#include <QMouseEvent>
#include <QBrush>


class Rects :  public QObject
{
    Q_OBJECT
    Q_PROPERTY(QBrush brush)

public:
    explicit Rects(QObject *parent = nullptr);
    void setBrush(QBrush brush) { this->brush = brush; emit reDraw(); }

    void paint(QPainter *painter);
    void setXY(int xn, int xy);

signals:
    void reDraw();
    void deleteThis(Rects* rect);

private:
    QRectF boundingRect() const;

    QBrush brush;
    int x, y, width, height;

protected:
    void mousePressEvent(QMouseEvent *event);
};

#endif // RECTS_H
