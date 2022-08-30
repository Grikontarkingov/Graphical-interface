#ifndef ELLIPSE_H
#define ELLIPSE_H

#include <QObject>
#include <QGraphicsItem>
#include <QBrush>
#include <QGraphicsSceneMouseEvent>

class Ellipse :  public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_PROPERTY(QBrush brush)

public:
    Ellipse(QObject *parent = nullptr, int xn = 0, int yn = 0);
    void setBrush(QBrush brush) { this->ellipseBrush = brush; emit reDraw(); }
    QRectF boundingRect() const override;

signals:
    void reDraw();

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    QRect ellipse;
    QBrush ellipseBrush;
    QPointF ellipsePoint;
    QPoint currentPos;

    int x, y;
    const int width = 100, height = 60;
    const int offsetX = 50, offsetY = 30;
    bool moving;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // ELLIPSE_H
