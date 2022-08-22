#include "rects.h"

#include <QRandomGenerator>
#include <QPainter>
#include <QMouseEvent>

Rects::Rects(QObject *parent) : QObject(parent)
{
    x = 0;
    y = 0;

    brush.setColor(QColor::fromRgb(QRandomGenerator::global()->generate()));
    brush.setStyle(Qt::BrushStyle::SolidPattern);

}


void Rects::paint(QPainter *painter)
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

void Rects::mousePressEvent(QMouseEvent* event)
{
    if(event->button() & Qt::RightButton)
    {
        emit deleteThis(this);
    }
}
