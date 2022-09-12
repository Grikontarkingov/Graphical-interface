#include "tasksview.h"
#include "ui_tasksview.h"

TasksView::TasksView(QSqlRelationalTableModel* model) :
    QWidget(nullptr),
    ui(new Ui::TasksView)
{
    ui->setupUi(this);

    ui->tableView->setModel(model);
    model->setTable("tasks");
    model->select();
}

TasksView::~TasksView()
{
    delete ui;
}

void TasksView::updateTasks(QSqlRelationalTableModel* model)
{
    ui->tableView->setModel(model);
     model->setTable("tasks");
     model->select();
}
