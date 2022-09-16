#include "picturedownloader.h"

#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>

PictureDownloader::PictureDownloader(QObject *parent) :
    QObject(parent)
{
    connect(&manager, &QNetworkAccessManager::finished, this, &PictureDownloader::on_load);
}

void PictureDownloader::load(QString imageUrl)
{
    manager.get(QNetworkRequest(QUrl(imageUrl)));
}

void PictureDownloader::on_load(QNetworkReply *reply)
{
    QPixmap pixmap;
    pixmap.loadFromData(reply->readAll());
    pixmap = pixmap.scaled(221, 211, Qt::KeepAspectRatio);
    emit loaded(pixmap);
    reply->deleteLater();
}
