#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "threadfinder.h"

#include <QObject>
#include <QSharedPointer>

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = nullptr);
    ~Controller();
    void startFind(QString dir, QString file);

private:
    QSharedPointer<ThreadFinder>findThread;

    QString currentPath;

signals:
    void changFindPath(QString);
    void genPathOfFile(QString);
    void genPathOfDir(QString);
    void newFind();

public slots:
    void deleteThread();
    void printCurrentPath(QString);
    void genStringPathFile(QString);
    void genStringPathDir(QString);
    void finishThread();
};

#endif // CONTROLLER_H
