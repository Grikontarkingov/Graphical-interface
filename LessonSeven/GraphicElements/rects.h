#ifndef RECTS_H
#define RECTS_H

#include <QObject>
#include <QGraphicsSceneMouseEvent>
#include <QBrush>
#include <QGraphicsItem>


class Rects :  public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_PROPERTY(QBrush brush)

public:
    Rects(QObject *parent = nullptr, int xn = 0, int yn = 0);
    void setBrush(QBrush brush) { this->rectBrush = brush; emit reDraw(); }
    QRectF boundingRect() const override;

signals:
    void reDraw();

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    QRect rect;
    QBrush rectBrush;
    QPointF rectPoint;
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

#endif // RECTS_H
