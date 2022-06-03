#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class HelpWindow;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_openFile_clicked();

    void on_saveFile_clicked();

    void on_helpButton_clicked();

    void deleteHelpWindow();

private:
    void OpenFileTxt();
    void SaveTextFile();

    Ui::MainWindow *ui;
    HelpWindow* helpWindow;

    QString filename;
};
#endif // MAINWINDOW_H
