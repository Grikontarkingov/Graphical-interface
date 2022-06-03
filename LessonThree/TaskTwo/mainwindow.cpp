#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QFileDialog>
#include <QTextStream>
#include <QTextCodec>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_openFile_clicked()
{
    QString in = QFileDialog::getOpenFileName(this, "Open html file...", QDir::currentPath(), "HTML(*.html)");

    if(in.length() > 0)
    {
        QFile file(in);
        if(file.open(QFile::ReadOnly | QFile::ExistingOnly))
        {
            QTextStream stream(&file);
            QTextCodec* codec = QTextCodec::codecForName("Windows-1251");
            QString html(codec->fromUnicode(stream.readAll()).data());

            Parse(html, "<div class=\"weather", "<div class=\"rates");
            Parse(html, "<div class=\"rates", "<a class=\"horoscope");

            file.close();
        }
    }
}

void MainWindow::Parse(QString& in, const QString start, const QString end)
{
    int startIndex = in.indexOf(start);
    int endIndex = in.indexOf(end);

    QString result;

    result.insert(0, &in.data()[startIndex], endIndex - startIndex);
    ui->htmlText->appendHtml(result);
}
