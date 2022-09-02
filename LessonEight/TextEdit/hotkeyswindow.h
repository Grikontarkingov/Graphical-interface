#ifndef HOTKEYSWINDOW_H
#define HOTKEYSWINDOW_H

#include <QWidget>
#include <QStandardItemModel>
#include <QTableView>
#include <QPushButton>
#include <QTranslator>

namespace Ui {
class HotkeysWindow;
}

class HotkeysWindow : public QWidget
{
    Q_OBJECT

public:
    HotkeysWindow(QTranslator& translator,
                  QString& language,
                  QString openFile = "",
                  QString saveFile = "",
                  QString newFile = "",
                  QString quitApp = "",
                  QString hotkeySendToPrint = "",
                  QString hotkeyNewTab = "");
    ~HotkeysWindow();
signals:
    void hotkeysWindowClose();
    void hotkeysSave(QList<QStandardItem* > hotkeys);

protected:
    void closeEvent(QCloseEvent* event);

private slots:
    void on_save_clicked();

private:
    void createTable();
    void createSaveButton();

    Ui::HotkeysWindow *ui;
    QStandardItemModel* model;
    QTableView* hotkeys;

    QPushButton* save;

    QTranslator& translate;
    QString& lang;

    QString hotkeyOpen;
    QString hotkeySave;
    QString hotkeyNew;
    QString hotkeySendToPrint;
    QString hotkeyNewTab;
    QString hotkeyQuit;
};

#endif // HOTKEYSWINDOW_H
