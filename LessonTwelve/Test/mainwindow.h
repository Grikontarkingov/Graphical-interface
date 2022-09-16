#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUdpSocket>
#include <QObject>

class PictureDownloader;

class QNetworkAccessManager;
class QNetworkReply;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void replyFinished(QNetworkReply* reply);

private slots:
    void on_receiveButton_clicked();

private:
    void findLinkPicture(QString link);
    void setPicture();

    Ui::MainWindow *ui;

    QNetworkAccessManager* http;
    PictureDownloader* pictureDownloaderOne;
    PictureDownloader* pictureDownloaderTwo;
    PictureDownloader* pictureDownloaderThree;

    const QString searcher {"https://yandex.ru/images/search?text="};
    QString strRequest;
    QString startLink { "src=\"//" };
    QVector<QString> linksToPictures;
};
#endif // MAINWINDOW_H
