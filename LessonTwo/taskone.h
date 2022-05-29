#ifndef TASKONE_H
#define TASKONE_H

#include <QWidget>

namespace Ui {
class TaskOne;
}

class ParseText;

class TaskOne : public QWidget
{
    Q_OBJECT

public:
    explicit TaskOne(QWidget *parent = nullptr);
    ~TaskOne();

signals:
    void mainWindow();

private slots:
    void on_backToMainMenuButton_clicked();

    void on_plainTextWidget_textChanged();

private:
    Ui::TaskOne *ui;
    ParseText* parseText;
};

#endif // TASKONE_H
