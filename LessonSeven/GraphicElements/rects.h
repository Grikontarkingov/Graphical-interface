#ifndef RECTS_H
#define RECTS_H

#include "qbrush.h"
#include <QObject>
#include <QGraphicsSceneMouseEvent>
#include <QBrush>
#include <QGraphicsItem>


class Rects :  public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_PROPERTY(QBrush brush)

public:
    explicit Rects(QObject *parent = nullptr);
    void setBrush(QBrush brush) { this->brush = brush; emit reDraw(); }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void setXY(int xn, int xy);

signals:
    void reDraw();
    void deleteThis(Rects* rect);

private:
    QRectF boundingRect() const override;

    QBrush brush;
    int x, y, width, height;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // RECTS_H
