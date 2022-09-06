#include "filecontroller.h"

#include <QDataStream>

FileController::FileController(QObject *parent)
    : QObject{parent}
{
    file = new QFile("database.txt", this);
    file->open(QFile::ReadWrite);

    if(file)
    {
        while(!file->atEnd())
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
        }
    }
}

FileController::~FileController()
{
    if(file)
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
    std::tuple<QString, QString, QString> t = std::make_tuple(taskName, deadline, progress);
    tasks.push_back(t);
}
