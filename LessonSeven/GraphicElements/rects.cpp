#include "rects.h"

#include <QRandomGenerator>
#include <QPainter>

Rects::Rects(QObject *parent, int xn, int yn) : QObject(parent), QGraphicsItem()
{
    this->x = xn;
    this->y = yn;

    rectBrush.setColor(QColor::fromRgb(QRandomGenerator::global()->generate()));
    rectBrush.setStyle(Qt::BrushStyle::SolidPattern);

    moving = false;

    rect.setRect(x - offsetX, y - offsetY, width, height);
}


void Rects::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(rectBrush);
    painter->drawRect(x - offsetX, y - offsetY, width, height);

    Q_UNUSED(option)
    Q_UNUSED(widget)
}

QRectF Rects::boundingRect() const
{
    return QRectF(x - offsetX, y - offsetY, width, height);
}

void Rects::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if(event->button() == Qt::LeftButton)
    {
        moving = true;

        currentPos = event->pos().toPoint();
    }
}

void Rects::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    if(event->button() == Qt::LeftButton)
    {
        moving = false;

        emit reDraw();
    }
}

void Rects::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(moving)
    {
        QPoint vec = event->pos().toPoint() - currentPos;

        x += vec.x();
        y += vec.y();

        currentPos = event->pos().toPoint();

        emit reDraw();
    }
}
