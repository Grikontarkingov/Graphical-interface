#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QPushButton>
#include <QTranslator>
#include <QShortcut>
#include <QStandardItem>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class HotkeysWindow;
class HelpWindow;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_newFile_clicked();
    void on_open_clicked();
    void on_openReadOnly_clicked();
    void on_changeLangToRu_clicked();
    void on_changeLangToEn_clicked();
    void on_save_clicked();

    void on_changeHotkeys_clicked();
    void deleteChangeHotkeysWindow();
    void changeHotkeys(QList<QStandardItem* > hotkeys);

    void on_help_clicked();
    void deleteHelpWindow();

    void quitApp();

private:
    void OpenFileTxt();
    void SaveTextFile();
    void setLanguage(const QString lang);

    Ui::MainWindow *ui;
    HotkeysWindow* hotkeysWindow;
    HelpWindow* helpWindow;
    QTranslator translator;

    QTextEdit* textEdit;

    QMenu* fileMenu;
    QAction* newFile;
    QAction* open;
    QAction* openReadOnly;
    QAction* save;
    QAction* changeLangToRu;
    QAction* changeLangToEn;

    QMenu* settings;
    QAction* hotkeys;

    QMenu* help;
    QAction* about;

    QString filename;
    QString lang;

    QShortcut* keyOpen;
    QShortcut* keySave;
    QShortcut* keyNew;
    QShortcut* keyQuit;
};
#endif // MAINWINDOW_H
