#include "stars.h"

#include <QRandomGenerator>
#include <QPainter>

Stars::Stars(QObject *parent, int xn, int yn) : QObject(parent), QGraphicsItem()
{
    this->x = xn;
    this->y = yn;

    makeStar();

    starBrush.setColor(QColor::fromRgb(QRandomGenerator::global()->generate()));
    starBrush.setStyle(Qt::BrushStyle::SolidPattern);

    this->setTransformOriginPoint(star.boundingRect().center());
}


void Stars::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(starBrush);
    painter->drawPolygon(star);

    Q_UNUSED(option)
    Q_UNUSED(widget)
}

QRectF Stars::boundingRect() const
{
    return star.boundingRect();
}

void Stars::makeStar()
{
    star << QPoint(x, y - 45);
    star << QPoint(x + 15, y - 15);
    star << QPoint(x + 45, y - 15);
    star << QPoint(x + 15, y);
    star << QPoint(x + 30, y + 30);
    star << QPoint(x, y + 15);
    star << QPoint(x - 30, y + 30);
    star << QPoint(x - 15, y);
    star << QPoint(x - 45, y - 15);
    star << QPoint(x - 15, y - 15);
}
