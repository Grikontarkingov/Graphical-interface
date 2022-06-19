#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "myqtwidget.h"

#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    MyQtWidget* mQW;
};
#endif // MAINWINDOW_H
