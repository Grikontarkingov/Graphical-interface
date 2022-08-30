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


    moving = false;

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

void Stars::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if(event->button() == Qt::LeftButton)
    {
        moving = true;

        currentPos = event->pos().toPoint();
    }
}

void Stars::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    if(event->button() == Qt::LeftButton)
    {
        moving = false;

        emit reDraw();
    }
}

void Stars::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(moving)
    {
        QPoint vec = event->pos().toPoint() - currentPos;

        x += vec.x();
        y += vec.y();

        for(auto& line : star)
        {
            line.setX(line.x() + vec.x());
            line.setY(line.y() + vec.y());
        }

        currentPos = event->pos().toPoint();

        this->setTransformOriginPoint(star.boundingRect().center());

        emit reDraw();
    }
}
