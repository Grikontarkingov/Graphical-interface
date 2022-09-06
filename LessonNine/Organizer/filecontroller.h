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

private:
    QFile *file;
    QVector<std::tuple<QString, QString, QString>> tasks;

signals:
};

#endif // FILECONTROLLER_H
