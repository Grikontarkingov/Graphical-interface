#include "dbcontroller.h"

#include <QDate>
#include <QDebug>
#include <QSqlError>
#include <QWidget>

DBController::DBController(QObject *parent)
    : QObject{parent}
{
    model = new QSqlRelationalTableModel(nullptr, QSqlDatabase::addDatabase("QSQLITE"));
    database = model->database();
    database.setDatabaseName("tasks.db");

    if(!database.open())
    {
        qDebug() << "Бд не открыта" << database.lastError();
    }
    else
    {
        QSqlQuery query;

        query.exec("CREATE TABLE IF NOT EXISTS tasks ("
                   "task_name TEXT NOT NULL,"
                   "deadline REAL NOT NULL,"
                   "progress REAL NOT NULL);");

        query.exec(tr("SELECT COUNT(*) FROM tasks"));
        query.next ();
        numberOfTasks = query.value(0).toInt();

        emit changeNumberTasks(getTasksSize());
    }
}

DBController::~DBController()
{
    if(tasksView) delete tasksView;
    database.close();
}

void DBController::writeDB(QString taskName, QString deadline, QString progress)
{
    if(checkTaskName(taskName) && checkDate(deadline))
    {
        emit uncorrectField("");
    }
    else
    {
        return;
    }

    if(!database.open())
    {
        qDebug() << "Бд не открыта" << database.lastError();
    }
    else
    {
        QSqlQuery query;
        query.exec("CREATE TABLE IF NOT EXISTS tasks ("
                   "task_name TEXT NOT NULL,"
                   "deadline REAL NOT NULL,"
                   "progress REAL NOT NULL);");

        query.exec("INSERT INTO tasks VALUES ('" + taskName + "', '" + deadline + "', '" + progress + "')");

        query.exec(tr("SELECT COUNT(*) FROM tasks"));
        query.next ();
        numberOfTasks = query.value(0).toInt();

        if(tasksView)
        {
            tasksView->updateTasks(model);
        }
    }


    emit changeNumberTasks(getTasksSize());
}


int DBController::getTasksSize()
{
    return numberOfTasks;
}

void DBController::showTasks()
{
    tasksView = new TasksView(model);
    connect(tasksView, &TasksView::closeWindow, this, &DBController::closeTasksView);
    tasksView->show();
}

void DBController::closeTasksView()
{
    delete tasksView;
}


bool DBController::checkDate(QString date)
{
    if(date.size() != 10)
    {
        emit uncorrectField("Uncorrect  \"Date\"! Task is not added! Try again.");

        return false;
    }

    int firstDot = date.toStdString().find('.');
    int secondDot = date.toStdString().find('.');
    if(firstDot != 2 && secondDot != 5)
    {
        emit uncorrectField("Uncorrect  \"Separator of date\"! Task is not added! Try again.");

        return false;
    }

    std::string textDay = date.toStdString().substr(0, 2);
    std::string textMonth = date.toStdString().substr(3, 2);
    std::string textYear = date.toStdString().substr(6, 4);

    int day = std::stoi(textDay);
    int month = std::stoi(textMonth);
    int year = std::stoi(textYear);

    QDate currentDate = QDate::currentDate();

    if(!checkYear(year, currentDate))
    {
        return false;
    }
    if(!checkMonth(month, year, currentDate))
    {
        return false;
    }
    if(!checkDay(day, month, year, currentDate))
    {
        return false;
    }

    return true;
}

bool DBController::checkTaskName(QString taskName)
{
    if(taskName.isEmpty() || taskName == "")
    {
        emit uncorrectField("Uncorrect  \"Task name\"! Task is not added! Try again.");

        return false;
    }

    return true;
}

bool DBController::checkDay(int day, int month, int year, QDate currentDate)
{
    int dayInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if(year % 4 == 0)
    {
        if(year % 100 == 0)
        {
            if(year % 400 == 0)
            {
                dayInMonth[1] = 29;
            }
        }
        else
        {
            dayInMonth[1] = 29;
        }
    }

    if(year == currentDate.year() && month == currentDate.month())
    {
        if(day < currentDate.day() || day > dayInMonth[month])
        {
            emit uncorrectField("Uncorrect  \"Day(more or less)\"! Task is not added! Try again.");

            return false;
        }
    }
    else{

        if(day < 1 || day > dayInMonth[month])
        {
            emit uncorrectField("Uncorrect  \"Day(more or less)\"! Task is not added! Try again.");

            return false;
        }
    }

    return true;
}

bool DBController::checkMonth(int month, int year, QDate currentDate)
{
    if(year == currentDate.year())
    {
        if(month < currentDate.month() || month > 12)
        {
            emit uncorrectField("Uncorrect  \"Month(more or less)\"! Task is not added! Try again.");
            return false;
        }
    }
    else
    {
        if(month < 1 || month > 12)
        {
            emit uncorrectField("Uncorrect  \"Month(more or less)\"! Task is not added! Try again.");
            return false;
        }
    }

    return true;
}

bool DBController::checkYear(int year, QDate currentDate)
{
    if(year < currentDate.year())
    {
        emit uncorrectField("Uncorrect  \"Year(less current)\"! Task is not added! Try again.");
        return false;
    }

    return true;
}
