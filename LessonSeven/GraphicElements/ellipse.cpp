#include "ellipse.h"

#include <QRandomGenerator>
#include <QPainter>

Ellipse::Ellipse(QObject *parent, int xn, int yn) : QObject(parent), QGraphicsItem()
{
    this->x = xn;
    this->y = yn;

    ellipseBrush.setColor(QColor::fromRgb(QRandomGenerator::global()->generate()));
    ellipseBrush.setStyle(Qt::BrushStyle::SolidPattern);

    moving = false;

    ellipse.setRect(x - offsetX, y - offsetY, width, height);
}


void Ellipse::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(ellipseBrush);
    painter->drawEllipse(x - offsetX, y - offsetY, width, height);

    Q_UNUSED(option)
    Q_UNUSED(widget)
}

QRectF Ellipse::boundingRect() const
{
    return QRectF(x - offsetX, y - offsetY, width, height);
}

void Ellipse::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if(event->button() == Qt::LeftButton)
    {
        moving = true;

        currentPos = event->pos().toPoint();
    }
}

void Ellipse::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    if(event->button() == Qt::LeftButton)
    {
        moving = false;

        emit reDraw();
    }
}

void Ellipse::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
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
