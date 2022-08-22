#include "widget.h"

#include <QPainter>
#include <QApplication>
#include <QRandomGenerator>
#include <QStyleOptionGraphicsItem>

Widget::Widget(QWidget *parent)
: QWidget(parent)
{
    counter = 0;
}


Widget::~Widget()
{
}

void Widget::mouseReleaseEvent(QMouseEvent* event)
{
    if(event->button() & Qt::LeftButton)
    {
        nextCount();

        x = event->x();
        y = event->y();

        this->update();
    }
}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QStyleOptionGraphicsItem bla;

    switch (counter) {
    case 1:
        drawRect();

        break;

    case 2:
        drawElipse();

        break;

    case 3:
        drawStar();

        break;
    }

    if(!rects.isEmpty())
    {
        for(auto rect : rects)
        {
            rect->paint(&painter);
        }
    }

    if(!ellipses.isEmpty())
    {
        for(auto ellipse : ellipses)
        {
            ellipse->paint(&painter, &bla, this);
        }
    }

    if(!stars.isEmpty())
    {
        for(auto star : stars)
        {
            star->paint(&painter, &bla, this);
        }
    }

    painter.end();
    this->render(this);

    Q_UNUSED(event)
}

void Widget::drawRect()
{
    Rects* rect = new Rects(this);
    rect->setXY(x, y);
    connect(rect, &Rects::deleteThis, this, &Widget::deleteRects);

    rects.push_back(rect);
}

void Widget::drawElipse()
{
    Ellipse* ellipse = new Ellipse;
    ellipse->setXY(x, y);

    ellipses.push_back(ellipse);
}

void Widget::drawStar()
{
    Stars* star = new Stars;
    star->setXY(x, y);

    stars.push_back(star);
}

void Widget::nextCount()
{
    ++counter;

    if(counter > 3)
    {
        counter = 1;
    }
}

void Widget::deleteRects(Rects* rect)
{
    QMutableVectorIterator<Rects* > i(rects);
    while(i.hasNext())
    {
        Rects* temp = i.next();

        if(temp == rect)
        {
            i.remove();
        }
    }
}
