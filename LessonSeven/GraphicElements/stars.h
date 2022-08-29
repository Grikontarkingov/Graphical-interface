#ifndef STARS_H
#define STARS_H

#include <QObject>
#include <QGraphicsItem>
#include <QBrush>
#include <QGraphicsSceneMouseEvent>


class Stars :  public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_PROPERTY(QBrush brush)

public:
    Stars(QObject *parent = nullptr, int xn = 0, int yn = 0);
    void setBrush(QBrush brush) { this->starBrush = brush; emit reDraw(); }
    QRectF boundingRect() const override;

signals:
    void reDraw();

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void makeStar();

    QPolygon star;
    QBrush starBrush;
    QPointF starPoint;

    int x, y;
};

#endif // STARS_H
