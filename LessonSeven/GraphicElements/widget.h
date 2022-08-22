#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMouseEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

protected:
    void mouseReleaseEvent(QMouseEvent* event);
    void paintEvent(QPaintEvent *event);

private:
    void drawRect();
    void drawElipse();
    void drawStar();

    void nextCount();

    QVector<QRect> rects;
    QVector<QRectF> ellipses;
    QVector<QPointF* > stars;

    int counter;
    int x, y;
};
#endif // WIDGET_H
