#ifndef TASKTHREE_H
#define TASKTHREE_H

#include <QWidget>

namespace Ui {
class TaskThree;
}

class TaskThree : public QWidget
{
    Q_OBJECT

public:
    explicit TaskThree(QWidget *parent = nullptr);
    ~TaskThree();

signals:
    void mainWindow();

private slots:
    void on_add_in_second_button_clicked();

    void on_replace_in_second_button_clicked();

    void on_insert_html__in_second_button_clicked();

    void on_mainMenuButton_clicked();

private:
    Ui::TaskThree *ui;
};

#endif // TASKTHREE_H
