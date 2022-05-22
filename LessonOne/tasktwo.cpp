#include "tasktwo.h"
#include "ui_tasktwo.h"

#include <QtMath>
#include <math.h>

TaskTwo::TaskTwo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TaskTwo)
{
    ui->setupUi(this);
}

TaskTwo::~TaskTwo()
{
    delete ui;
}

void TaskTwo::on_calculate_button_clicked()
{
    qint32 a = ui->num_a_edit->text().toInt();
    qint32 b = ui->num_b_edit->text().toInt();
    double angle = ui->num_angle_edit->text().toInt();

    if(ui->is_degrees->isChecked())
    {
        angle = (angle * 3.1416) / 180;
    }

    CalculateTriangleSide(a, b, angle);
}

void TaskTwo::CalculateTriangleSide(qint32 a, qint32 b, double angle)
{
    double c = qSqrt(qPow(a, 2) + qPow(b, 2) - 2 * a * b * qCos(angle));

    ui->result_num_label->setText(QString::number(c));
}

void TaskTwo::on_mainMenuButton_clicked()
{
    this->close();
    emit mainWindow();
}
