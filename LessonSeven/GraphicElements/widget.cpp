#include "widget.h"

#include <QPainter>
#include <QApplication>
#include <QRandomGenerator>

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

    QBrush brush;
    brush.setStyle(Qt::BrushStyle::SolidPattern);

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

    if(!rects.empty())
    {
        brush.setColor(QColor::fromRgb(QRandomGenerator::global()->generate()));
        painter.setBrush(brush);
        painter.drawRects(rects);
    }

    if(!ellipses.empty())
    {
        brush.setColor(QColor::fromRgb(QRandomGenerator::global()->generate()));
        painter.setBrush(brush);

        for(auto ell : ellipses)
        {
            painter.drawEllipse(ell);
        }
    }

    if(!stars.empty())
    {
        brush.setColor(QColor::fromRgb(QRandomGenerator::global()->generate()));
        painter.setBrush(brush);

        for(auto star : stars)
        {
            painter.drawPolygon(star, 10);
        }
    }

    painter.end();
    this->render(this);

    Q_UNUSED(event)
}

void Widget::drawRect()
{
    QRect rect(x - 2, y - 4, 80, 60);

    rects.push_back(rect);
}

void Widget::drawElipse()
{
    QRectF elipse(x - 2, y - 4, 80, 60);

    ellipses.push_back(elipse);
}

void Widget::drawStar()
{
    QPointF* star = new QPointF[10];

    star[0] = QPointF(x, y - 45);
    star[1] = QPointF(x + 15, y - 15);
    star[2] = QPointF(x + 45, y - 15);
    star[3] = QPointF(x + 15, y);
    star[4] = QPointF(x + 30, y + 30);
    star[5] = QPointF(x, y + 15);
    star[6] = QPointF(x - 30, y + 30);
    star[7] = QPointF(x - 15, y);
    star[8] = QPointF(x - 45, y - 15);
    star[9] = QPointF(x - 15, y - 15);

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
