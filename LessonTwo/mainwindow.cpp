#include "mainwindow.h"
#include "./ui_mainwindow.h"
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
    if(taskOne)
    {
        delete taskOne;
        taskOne = nullptr;
    }
    if(taskTwo)
    {
        delete taskTwo;
        taskTwo = nullptr;
    }
    if(taskThree)
    {
        delete taskThree;
        taskThree = nullptr;
    }
    delete ui;
}


void MainWindow::on_taskOneButton_clicked()
{
    taskOne->show();
    this->close();
}


void MainWindow::on_taskTwoButton_clicked()
{
    taskTwo->show();
    this->close();
}


void MainWindow::on_taskThreeButton_clicked()
{
    taskThree->show();
    this->close();
}

