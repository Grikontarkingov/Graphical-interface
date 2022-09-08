#include "filecontroller.h"

#include <QDataStream>
#include <QDate>

FileController::FileController(QObject *parent)
    : QObject{parent}
{
    file = new QFile("database.txt", this);
    file->open(QFile::ReadOnly);

    if(file)
    {
        while(file->isOpen())
        {
            QDataStream stream(file);

            int len = 0;
            stream.readRawData((char*)&len, sizeof len);

            QByteArray b;
            b.resize(len);
            stream.readRawData(b.data(), len);
            QString taskName = QString::fromUtf8(b);

            stream.readRawData((char*)&len, sizeof len);
            b.resize(len);
            stream.readRawData(b.data(), len);
            QString deadline = QString::fromUtf8(b);

            stream.readRawData((char*)&len, sizeof len);
            b.resize(len);
            stream.readRawData(b.data(), len);
            QString progress = QString::fromUtf8(b);

            tasks.push_back(std::make_tuple(taskName, deadline, progress));

            if(file->atEnd())
            {
                file->close();
            }
        }
    }
}

FileController::~FileController()
{
    if(file->open(QFile::WriteOnly))
    {
        for(auto task : tasks)
        {
            QDataStream stream(file);

            auto  bytes = std::get<0>(task).toUtf8();
            int  len = bytes.length();

            stream.writeRawData((char*)&len, sizeof len);
            stream.writeRawData(bytes.data(), len);

            bytes = std::get<1>(task).toUtf8();
            len = bytes.length();

            stream.writeRawData((char*)&len, sizeof len);
            stream.writeRawData(bytes.data(), len);

            bytes = std::get<2>(task).toUtf8();
            len = bytes.length();

            stream.writeRawData((char*)&len, sizeof len);
            stream.writeRawData(bytes.data(), len);
        }

        file->close();
    }

    tasks.clear();

    delete file;
}

void FileController::writeFile(QString taskName, QString deadline, QString progress)
{
    if(checkTaskName(taskName) && checkDate(deadline))
    {
        emit uncorrectField("");
    }
    else
    {
        return;
    }

    tasks.push_back(std::make_tuple(taskName, deadline, progress));

    emit changeNumberTasks(tasks.size());
}


int FileController::getTasksSize()
{
    return tasks.size();
}

bool FileController::checkDate(QString date)
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


bool FileController::checkTaskName(QString taskName)
{
    if(taskName.isEmpty() || taskName == "")
    {
        emit uncorrectField("Uncorrect  \"Task name\"! Task is not added! Try again.");

        return false;
    }

    return true;
}

bool FileController::checkDay(int day, int month, int year, QDate currentDate)
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

bool FileController::checkMonth(int month, int year, QDate currentDate)
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

bool FileController::checkYear(int year, QDate currentDate)
{
    if(year < currentDate.year())
    {
        emit uncorrectField("Uncorrect  \"Year(less current)\"! Task is not added! Try again.");
        return false;
    }

    return true;
}
