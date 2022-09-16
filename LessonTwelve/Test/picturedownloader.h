#ifndef PICTUREDOWNLOADER_H
#define PICTUREDOWNLOADER_H

#include <QNetworkAccessManager>
#include <QObject>
#include <QPixmap>


class PictureDownloader : public QObject
{
    Q_OBJECT
public:
    explicit PictureDownloader(QObject *parent = 0);

public slots:
    void load(QString imageUrl);

private slots:
    void on_load(QNetworkReply* reply);

signals:
    void loaded(QPixmap);

private:
    QNetworkAccessManager manager;
};

#endif // PICTUREDOWNLOADER_H
