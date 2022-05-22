#include "taskone.h"
#include "ui_taskone.h"

#include <QtMath>

TaskOne::TaskOne(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TaskOne)
{
    ui->setupUi(this);
}

TaskOne::~TaskOne()
{
    delete ui;
}

void TaskOne::on_calculate_button_clicked()
{
    qint32 a = ui->num_a_edit->text().toInt();
    qint32 b = ui->num_b_edit->text().toInt();
    qint32 c = ui->num_c_edit->text().toInt();

    if(a == 0)
    {
        CalculateLinearEquation(b, c);
    }
    else
    {
        CalculateQuadraticEquation(a, b, c);
    }
}

void TaskOne::CalculateQuadraticEquation(qint32 a, qint32 b, qint32 c)
{
    qint32 discriminant = CalculateDiscriminant(a, b, c);
    qint32 number_result = 0;
    QString text_result;

    if(discriminant < 0)
    {
        ui->result_line->setText("No roots");
    }
    else if(discriminant == 0)
    {
        number_result = -b / (2 * a);
        text_result = "X = " + QString::number(number_result);

        ui->result_line->setText(text_result);
    }
    else
    {
        number_result = (-b + qSqrt(discriminant)) / (2 * a);
        text_result = "X1 = " + QString::number(number_result);
        number_result = (-b - qSqrt(discriminant)) / (2 * a);
        text_result += ", X2 = " + QString::number(number_result);

        ui->result_line->setText(text_result);
    }
}

void TaskOne::CalculateLinearEquation(qint32 b, qint32 c)
{
    qint32 number_result = 0;
    QString text_result;
    number_result = -c / b;
    text_result = "X = " + QString::number(number_result);

    ui->result_line->setText(text_result);
}

qint32 TaskOne::CalculateDiscriminant(qint32 a, qint32 b, qint32 c)
{
    return (qPow(b, 2) - (4 * a * c));
}

void TaskOne::on_mainMenuButton_clicked()
{
    this->close();
    emit mainWindow();
}

