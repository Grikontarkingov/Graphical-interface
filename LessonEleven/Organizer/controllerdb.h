#ifndef CONTROLLERDB_H
#define CONTROLLERDB_H

#include <QWidget>
#include <QSqlQuery>
#include <QSqlRelationalTableModel>

namespace Ui {
class ControllerDB;
}

class ControllerDB : public QWidget
{
    Q_OBJECT

public:
    ControllerDB();
    ~ControllerDB();

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

    Ui::ControllerDB *ui;
    QSqlDatabase database;
    QSqlRelationalTableModel* model;

    int numberOfTasks;

signals:
    void changeNumberTasks(int number);
    void uncorrectField(QString warning);
};

#endif // CONTROLLERDB_H
