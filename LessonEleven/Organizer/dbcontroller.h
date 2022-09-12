#ifndef DBCONTROLLER_H
#define DBCONTROLLER_H

#include "tasksview.h"

#include <QObject>
#include <QSqlQuery>
#include <QSqlRelationalTableModel>

class DBController : public QObject
{
    Q_OBJECT
public:
    explicit DBController(QObject *parent = nullptr);
    ~DBController() override;

    Q_INVOKABLE
    void writeDB(QString taskName, QString deadline, QString progress);

    Q_INVOKABLE
    int getTasksSize();

    Q_INVOKABLE
    void showTasks();

private:
    bool checkTaskName(QString taskName);
    bool checkDate(QString date);
    bool checkDay(int day, int month, int year, QDate currentDate);
    bool checkMonth(int month, int year, QDate currentDate);
    bool checkYear(int year, QDate currentDate);
    void closeTasksView();

    QSqlDatabase database;
    TasksView* tasksView;
    QSqlRelationalTableModel* model;


    int numberOfTasks;

signals:
    void changeNumberTasks(int number);
    void uncorrectField(QString warning);
};

#endif // DBCONTROLLER_H
