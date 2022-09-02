#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QTranslator>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class HotkeysWindow;
class HelpWindow;
class QMdiArea;
class ContextMenu;
class QShortcut;
class QStandardItem;
class QToolBar;

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
    void on_saveTo_clicked();
    void on_newTab_clicked();

    void on_sendToPrint_clicked();

    void on_exitApp_clicked();

    void on_changeHotkeys_clicked();
    void deleteChangeHotkeysWindow();
    void changeHotkeys(QList<QStandardItem* > hotkeys);

    void on_classicTheme_clicked();
    void on_darkTheme_clicked();
    void on_colorfulTheme_clicked();

    void on_help_clicked();
    void deleteHelpWindow();

    void on_font_changed(const QString& font);
    void on_pointSize_changed(const QString& size);
    void on_bold_clicked();
    void on_italic_clicked();
    void on_underLined_clicked();

    void on_alignmentLeft_clicked();
    void on_alignmentCenter_clicked();
    void on_alignmentRight_clicked();

    void quitApp();

private:
    void OpenFileTxt();
    void SaveTextFile();
    void setLanguage(const QString lang);
    void setStyleApp(const QString style);

    Ui::MainWindow *ui;
    HotkeysWindow* hotkeysWindow;
    HelpWindow* helpWindow;

    QTranslator translator;

    QMdiArea* textsEditors;

    QMenu* fileMenu;
    QAction* newFile;
    QAction* open;
    QAction* openReadOnly;
    QAction* save;
    QAction* saveTo;
    QAction* newTab;
    QAction* changeLangToRu;
    QAction* changeLangToEn;
    QAction* sendToPrint;
    QAction* exitApp;

    QMenu* settings;
    QAction* hotkeys;
    QMenu* theme;
    QAction* classicTheme;
    QAction* darkTheme;
    QAction* colorfulTheme;


    QMenu* help;
    QAction* about;

    QToolBar* toolBar;
    QPushButton* bold;
    QPushButton* italic;
    QPushButton* underLined;
    QPushButton* alignmentLeft;
    QPushButton* alignmentCenter;
    QPushButton* alignmentRight;

    QString filename;
    QString lang;

    QShortcut* keyOpen;
    QShortcut* keySave;
    QShortcut* keyNew;
    QShortcut* keyQuit;
    QShortcut* keySendToPrint;
    QShortcut* keyNewTab;
};
#endif // MAINWINDOW_H
