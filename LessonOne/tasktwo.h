#ifndef TASKTWO_H
#define TASKTWO_H

#include <QWidget>

namespace Ui {
class TaskTwo;
}

class TaskTwo : public QWidget
{
    Q_OBJECT

public:
    explicit TaskTwo(QWidget *parent = nullptr);
    ~TaskTwo();

signals:
    void mainWindow();

private slots:
    void on_calculate_button_clicked();

    void on_mainMenuButton_clicked();

private:
    void CalculateTriangleSide(qint32 a, qint32 b, double angle);

    Ui::TaskTwo *ui;
};

#endif // TASKTWO_H
