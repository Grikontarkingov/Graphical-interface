#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    mQW = new MyQtWidget(this);
}

MainWindow::~MainWindow()
{
    if(mQW) delete mQW;
}

