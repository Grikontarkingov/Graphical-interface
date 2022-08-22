#ifndef STARS_H
#define STARS_H

#include <QObject>
#include <QGraphicsItem>
#include <QBrush>


class Stars :  public QObject
{
    Q_OBJECT
    Q_PROPERTY(QBrush brush)

public:
    explicit Stars(QObject *parent = nullptr);
    void setBrush(QBrush brush) { this->brush = brush; emit reDraw(); }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void setXY(int xn, int xy);

signals:
    void reDraw();

private:
    QBrush brush;
    QPointF* star;
    int x, y, width, height;
};

#endif // STARS_H
