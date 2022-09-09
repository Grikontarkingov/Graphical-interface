#ifndef TASKONE_H
#define TASKONE_H

#include <QWidget>

namespace Ui {
class TaskOne;
}

class TaskOne : public QWidget
{
    Q_OBJECT

public:
    explicit TaskOne(QWidget *parent = nullptr);
    ~TaskOne();

signals:
    void mainWindow();

private slots:
    void on_calculate_button_clicked();

    void on_mainMenuButton_clicked();

private:
    void CalculateQuadraticEquation(qint32 a, qint32 b, qint32 c);
    void CalculateLinearEquation(qint32 b, qint32 c);
    qint32 CalculateDiscriminant(qint32 a, qint32 b, qint32 c);

    Ui::TaskOne *ui;
};

#endif // TASKONE_H
