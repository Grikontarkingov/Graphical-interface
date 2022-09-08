#ifndef FILECONTROLLER_H
#define FILECONTROLLER_H

#include <QObject>
#include <QString>
#include <QFile>
#include <QVector>
#include <tuple>

class FileController : public QObject
{
    Q_OBJECT
public:
    explicit FileController(QObject *parent = nullptr);
    ~FileController() override;

    Q_INVOKABLE
    void writeFile(QString taskName, QString deadline, QString progress);

    Q_INVOKABLE
    int getTasksSize();

private:
    bool checkTaskName(QString taskName);
    bool checkDate(QString date);
    bool checkDay(int day, int month, int year, QDate currentDate);
    bool checkMonth(int month, int year, QDate currentDate);
    bool checkYear(int year, QDate currentDate);

    QFile *file;
    QVector<std::tuple<QString, QString, QString>> tasks;

signals:
    void changeNumberTasks(int number);
    void uncorrectField(QString warning);
};

#endif // FILECONTROLLER_H
