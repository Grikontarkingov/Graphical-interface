#include "controller.h"

Controller::Controller(QObject *parent) : QObject(parent)
{

}

Controller::~Controller()
{
    if (findThread != nullptr)
    {
        if (findThread->isRunning())
        {
            findThread->findStop();
            findThread->terminate();
        }

        findThread.reset();
    }
}

void Controller::startFind(QString dir, QString file)
{
    if (findThread.get())
    {
        findThread->findStop();
        findThread->terminate();
        findThread.reset();
        return;
    }

    findThread = QSharedPointer<ThreadFinder>::create(dir, file);
    findThread->start(QThread::NormalPriority);
    connect(findThread.get(), &ThreadFinder::stopedThread, this, &Controller::deleteThread);
    connect(findThread.get(), &ThreadFinder::writeFoundPath, this, &Controller::printCurrentPath);
    connect(findThread.get(), &ThreadFinder::findFile, this, &Controller::genStringPathFile);
    connect(findThread.get(), &ThreadFinder::findDir, this, &Controller::genStringPathDir);

    emit newFind();
}

void Controller::deleteThread()
{
    findThread.reset();
}

void Controller::printCurrentPath(QString path)
{
    currentPath = path;
    emit changFindPath(path);
}

void Controller::genStringPathFile(QString file)
{
    QString s = currentPath + file;
    emit genPathOfFile(s);
}

void Controller::genStringPathDir(QString dir)
{
    emit genPathOfDir(dir);
}

void Controller::finishThread()
{
    emit changFindPath(tr("FINISH. Find complete"));
}
