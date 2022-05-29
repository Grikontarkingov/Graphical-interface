#include "taskone.h"
#include "ui_taskone.h"
#include "parsetext.h"

TaskOne::TaskOne(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TaskOne)
{
    ui->setupUi(this);
    this->setWindowTitle("Task One");

    parseText = new ParseText();
    if(!parseText) close();
}

TaskOne::~TaskOne()
{
    if(parseText)
    {
        delete parseText;
        parseText = nullptr;
    }

    delete ui;
}

void TaskOne::on_backToMainMenuButton_clicked()
{
    this->close();
    emit mainWindow();
}


void TaskOne::on_plainTextWidget_textChanged()
{
    QString str = ui->plainTextWidget->toPlainText();
    if(parseText->change(str))
    {
        ui->plainTextWidget->setPlainText(parseText->getText());
    }
}

