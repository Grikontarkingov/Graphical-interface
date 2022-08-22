#ifndef ELLIPSE_H
#define ELLIPSE_H

#include <QObject>
#include <QGraphicsItem>
#include <QBrush>

class Ellipse :  public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_PROPERTY(QBrush brush)

public:
    explicit Ellipse(QObject *parent = nullptr);
    void setBrush(QBrush brush) { this->brush = brush; emit reDraw(); }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void setXY(int xn, int xy);

signals:
    void reDraw();

private:
    QRectF boundingRect() const;

    QBrush brush;
    int x, y, width, height;
};

#endif // ELLIPSE_H
