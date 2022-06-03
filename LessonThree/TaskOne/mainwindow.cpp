#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "helpwindow.h"

#include <QFileDialog>
#include <QTextStream>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Text editor");
    helpWindow = nullptr;
}

MainWindow::~MainWindow()
{
    delete helpWindow;
    delete ui;
}


void MainWindow::on_openFile_clicked()
{
    filename = QFileDialog::getOpenFileName(this, "Choose txt file...", QDir::currentPath(), "Text(*.txt)");

    if(filename.length() > 0)
    {
        OpenFileTxt();
    }
}

void MainWindow::on_saveFile_clicked()
{
    filename = QFileDialog::getSaveFileName(this, "Choose directory...", QDir::current().path(), "Text(*.txt)");
    if(filename.length() > 0)
    {
        SaveTextFile();
    }

}

void MainWindow::on_helpButton_clicked()
{
    helpWindow = new HelpWindow;
    connect(helpWindow, &HelpWindow::helpClose, this, &MainWindow::deleteHelpWindow);
    helpWindow->show();
}

void MainWindow::OpenFileTxt()
{
    int index = filename.indexOf(".txt");

    if(index != -1 && filename.length() - 4 == index)
    {
        QFile file(filename);
        if(file.open(QIODevice::ReadOnly | QIODevice::ExistingOnly))
        {
            QTextStream stream(&file);
            ui->textEditor->setPlainText(stream.readAll());
            file.close();
        }
    }
}

void MainWindow::SaveTextFile()
{
    QString ext = QString(&(filename.data()[filename.length() - 4]));
    if(ext == ".txt")
    {
        QFile file(filename);
        if(file.open(QFile::WriteOnly | QFile::NewOnly))
        {
            QTextStream stream(&file);
            stream << ui->textEditor->toPlainText();
            file.close();
        }
    }
}

void MainWindow::deleteHelpWindow()
{
    delete helpWindow;
    helpWindow = nullptr;
}
