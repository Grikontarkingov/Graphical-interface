#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "taskone.h"
#include "tasktwo.h"
#include "taskthree.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    taskOne = new TaskOne();
    connect(taskOne, &TaskOne::mainWindow, this, &MainWindow::show);

    taskTwo = new TaskTwo();
    connect(taskTwo, &TaskTwo::mainWindow, this, &MainWindow::show);

    taskThree = new TaskThree();
    connect(taskThree, &TaskThree::mainWindow, this, &MainWindow::show);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete taskOne;
    delete taskTwo;
    delete taskThree;
}


void MainWindow::on_TaskOne_clicked()
{
    taskOne->show();
    this->close();
}


void MainWindow::on_TaskTwo_clicked()
{
    taskTwo->show();
    this->close();
}


void MainWindow::on_TaskThree_clicked()
{
    taskThree->show();
    this->close();
}
