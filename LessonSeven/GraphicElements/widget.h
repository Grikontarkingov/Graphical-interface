#ifndef WIDGET_H
#define WIDGET_H

#include <QGraphicsScene>
#include <QGraphicsView>


class Widget :  public QGraphicsView
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void reDraw();

private:
    void nextCount();
    void addFigure(int x, int y);

    QGraphicsScene *scene;

    int counter;

protected:
    void mouseReleaseEvent(QMouseEvent *event) override;

};
#endif // WIDGET_H
