#include "rects.h"

#include <QRandomGenerator>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>

Rects::Rects(QObject *parent) : QObject(parent), QGraphicsItem()
{
    x = 0;
    y = 0;

    brush.setColor(QColor::fromRgb(QRandomGenerator::global()->generate()));
    brush.setStyle(Qt::BrushStyle::SolidPattern);

}


void Rects::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(brush);
    painter->drawRect(x - 2, y - 4, 80, 60);
}

QRectF Rects::boundingRect() const
{
    return QRectF(x - 2, y - 4,  80, 60);
}


void Rects::setXY(int xn, int xy)
{
    this->x = xn;
    this->y = xy;
}

void Rects::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if(event->button() & Qt::RightButton)
    {
        emit deleteThis(this);
    }
}
