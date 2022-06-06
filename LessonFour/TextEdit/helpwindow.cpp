#include "helpwindow.h"
#include "ui_helpwindow.h"

#include <QTextStream>

HelpWindow::HelpWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HelpWindow)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("About"));
    this->setGeometry(QRect(0, 0, 300, 400));

    textEdit = new QTextEdit(this);
    textEdit->setGeometry(QRect(10, 10, 280, 380));
    textEdit->setReadOnly(true);

    OpenFileTxt();
}

HelpWindow::~HelpWindow()
{
    if(textEdit) delete textEdit;
    delete ui;
}

void HelpWindow::closeEvent(QCloseEvent* event)
{
    event->accept();
    emit helpClose();
}

void HelpWindow::OpenFileTxt()
{
    QFile file(":/Files/Help.txt");
    if(file.open(QIODevice::ReadOnly | QIODevice::ExistingOnly))
    {
        QTextStream stream(&file);
        textEdit->setPlainText(stream.readAll());
        file.close();
    }
}
