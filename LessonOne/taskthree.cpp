#include "taskthree.h"
#include "ui_taskthree.h"

TaskThree::TaskThree(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TaskThree)
{
    ui->setupUi(this);
}

TaskThree::~TaskThree()
{
    delete ui;
}

void TaskThree::on_add_in_second_button_clicked()
{
    ui->second_text_widgets->appendPlainText(ui->first_text_widgets->toPlainText());
}


void TaskThree::on_replace_in_second_button_clicked()
{
    ui->second_text_widgets->setPlainText(ui->first_text_widgets->toPlainText());
}


void TaskThree::on_insert_html__in_second_button_clicked()
{
    ui->second_text_widgets->appendHtml("<font color='red'>Hello</font>");
}

void TaskThree::on_mainMenuButton_clicked()
{
    this->close();
    emit mainWindow();
}
