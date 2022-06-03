#include "helpwindow.h"
#include "ui_helpwindow.h"

#include <QTextStream>

HelpWindow::HelpWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HelpWindow)
{
    ui->setupUi(this);
    OpenFileTxt();
}

HelpWindow::~HelpWindow()
{
    delete ui;
}

void HelpWindow::closeEvent(QCloseEvent* event)
{
    event->accept();
    emit helpClose();
}

void HelpWindow::OpenFileTxt()
{
    QFile file(":/Help/Files/Help.txt");
    if(file.open(QIODevice::ReadOnly | QIODevice::ExistingOnly))
    {
        QTextStream stream(&file);
        ui->helpText->setPlainText(stream.readAll());
        file.close();
    }
}
