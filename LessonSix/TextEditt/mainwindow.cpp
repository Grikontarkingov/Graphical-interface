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
    this->setWindowTitle(tr("Text editor"));
    ui->openFile->setText(tr("Open"));
    ui->openFileReadOnly->setText(tr("Open\nread-only"));
    ui->saveFile->setText(tr("Save"));
    ui->helpButton->setText(tr("Help"));
    helpWindow = nullptr;
}

MainWindow::~MainWindow()
{
    delete helpWindow;
    delete ui;
}


void MainWindow::on_openFile_clicked()
{
    filename = QFileDialog::getOpenFileName(this, tr("Choose txt file..."), QDir::currentPath(), "Text(*.txt)");

    if(filename.length() > 0)
    {
        ui->textEditor->setReadOnly(false);
        OpenFileTxt();
    }
}

void MainWindow::on_saveFile_clicked()
{
    filename = QFileDialog::getSaveFileName(this, tr("Choose directory..."), QDir::current().path(), "Text(*.txt)");
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

void MainWindow::on_openFileReadOnly_clicked()
{
    filename = QFileDialog::getOpenFileName(this, tr("Choose txt file..."), QDir::currentPath(), "Text(*.txt)");

    if(filename.length() > 0)
    {
        ui->textEditor->setReadOnly(true);
        OpenFileTxt();
    }
}

