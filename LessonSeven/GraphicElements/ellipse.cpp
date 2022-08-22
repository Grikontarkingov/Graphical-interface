#include "ellipse.h"

#include <QRandomGenerator>
#include <QPainter>

Ellipse::Ellipse(QObject *parent) : QObject(parent), QGraphicsItem()
{
    x = 0;
    y = 0;

    brush.setColor(QColor::fromRgb(QRandomGenerator::global()->generate()));
    brush.setStyle(Qt::BrushStyle::SolidPattern);

    setPos(0,0);
}


void Ellipse::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(brush);
    painter->drawEllipse(x - 2, y - 4, 80, 60);

    Q_UNUSED(option)
    Q_UNUSED(widget)
}

QRectF Ellipse::boundingRect() const
{
    return QRectF(x - 2, y - 4, 80, 60);
}


void Ellipse::setXY(int xn, int xy)
{
    this->x = xn;
    this->y = xy;
}
