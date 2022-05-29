#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class TaskOne;
class TaskTwo;
class TaskThree;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_taskOneButton_clicked();

    void on_taskTwoButton_clicked();

    void on_taskThreeButton_clicked();

private:
    Ui::MainWindow *ui;
    TaskOne* taskOne;
    TaskTwo* taskTwo;
    TaskThree* taskThree;
};
#endif // MAINWINDOW_H
