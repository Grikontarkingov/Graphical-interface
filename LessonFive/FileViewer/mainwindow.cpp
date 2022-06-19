#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      fileViewer(new FileViewer)
{
}

MainWindow::~MainWindow()
{
    if(fileViewer) delete fileViewer;
}

