#include "widget.h"
#include "rects.h"
#include "ellipse.h"
#include "stars.h"

#include <QMouseEvent>

Widget::Widget(QWidget *parent)
    : QGraphicsView(parent)
{
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, 800, 600);
    this->setScene(scene);

    this->setMinimumSize(800, 600);

    counter = 0;
}

Widget::~Widget()
{
}

void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    QPointF point = this->mapToScene(event->pos());

    if(event->button() == Qt::LeftButton && !(scene->itemAt(point, QGraphicsView::transform())))
    {
        nextCount();

        addFigure(point.toPoint().x(), point.toPoint().y());
    }
    else if(event->button() == Qt::RightButton)
    {
        scene->removeItem(scene->itemAt(point, QGraphicsView::transform()));
    }

    QGraphicsView::mouseReleaseEvent(event);
}

void Widget::nextCount()
{
    ++counter;

    if(counter > 3)
    {
        counter = 1;
    }
}


void Widget::addFigure(int x, int y)
{
    switch(counter)
    {
        case 1:
            {
                Rects* rect = new Rects(this, x, y);
                connect(rect, &Rects::reDraw, this, &Widget::reDraw);

                scene->addItem(rect);

                break;
            }
        case 2:
            {
                Ellipse* ellipse = new Ellipse(this, x, y);
                connect(ellipse, &Ellipse::reDraw, this, &Widget::reDraw);

                scene->addItem(ellipse);

                break;
            }
        case 3:
            {
                Stars* star = new Stars(this, x, y);
                connect(star, &Stars::reDraw, this, &Widget::reDraw);

                scene->addItem(star);

                break;
            }
    }
}

void Widget::reDraw()
{
    scene->update();
    update();
}
