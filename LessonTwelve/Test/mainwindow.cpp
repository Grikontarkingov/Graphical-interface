#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "picturedownloader.h"

#include <QNetworkDatagram>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QTimer>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    http = new QNetworkAccessManager(this);

    connect(http, &QNetworkAccessManager::finished, this, &MainWindow::replyFinished);

    linksToPictures.resize(3);
}

MainWindow::~MainWindow()
{
    if(http) delete http;
    if(pictureDownloaderOne) delete pictureDownloaderOne;
    if(pictureDownloaderTwo) delete pictureDownloaderTwo;
    if(pictureDownloaderThree) delete pictureDownloaderThree;
    delete ui;
}

void MainWindow::replyFinished(QNetworkReply* reply)
{
    QByteArray data = reply->readAll();

    findLinkPicture(data);

    setPicture();
}

void MainWindow::on_receiveButton_clicked()
{
    strRequest = ui->userReceive->text();

    http->get(QNetworkRequest(QUrl(searcher + strRequest)));
}

void MainWindow::findLinkPicture(QString link)
{
    int start = 0;
    int end = 0;

    start = link.indexOf(startLink);

    for(int i = 0; i < linksToPictures.size(); ++i)
    {
        start += startLink.length();

        end = link.indexOf("thumbs", start);
        end += 6;

        linksToPictures[i] = "https://" + link.mid(start, (end - start));

        start = link.indexOf(startLink, end);
    }
}

void MainWindow::setPicture()
{
    pictureDownloaderOne = new PictureDownloader;
    pictureDownloaderOne->load(linksToPictures.at(0));
    connect(pictureDownloaderOne, &PictureDownloader::loaded, ui->pictureOne, &QLabel::setPixmap);
    ui->pictureOne->show();

    pictureDownloaderTwo = new PictureDownloader;
    pictureDownloaderTwo->load(linksToPictures.at(1));
    connect(pictureDownloaderTwo, &PictureDownloader::loaded, ui->pictureTwo, &QLabel::setPixmap);

    pictureDownloaderThree = new PictureDownloader;
    pictureDownloaderThree->load(linksToPictures.at(2));
    connect(pictureDownloaderThree, &PictureDownloader::loaded, ui->pictureThree, &QLabel::setPixmap);
}
