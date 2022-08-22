#include "stars.h"

#include <QRandomGenerator>
#include <QPainter>

Stars::Stars(QObject *parent) : QObject(parent)
{
    star = new QPointF[10];
    x = 0;
    y = 0;

    brush.setColor(QColor::fromRgb(QRandomGenerator::global()->generate()));
    brush.setStyle(Qt::BrushStyle::SolidPattern);
}


void Stars::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    star[0] = QPointF(x, y - 45);
    star[1] = QPointF(x + 15, y - 15);
    star[2] = QPointF(x + 45, y - 15);
    star[3] = QPointF(x + 15, y);
    star[4] = QPointF(x + 30, y + 30);
    star[5] = QPointF(x, y + 15);
    star[6] = QPointF(x - 30, y + 30);
    star[7] = QPointF(x - 15, y);
    star[8] = QPointF(x - 45, y - 15);
    star[9] = QPointF(x - 15, y - 15);

    painter->setBrush(brush);
    painter->drawPolygon(star, 10);

    Q_UNUSED(option)
    Q_UNUSED(widget)
}


void Stars::setXY(int xn, int xy)
{
    this->x = xn;
    this->y = xy;
}
