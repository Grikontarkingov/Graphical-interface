#ifndef CONTEXTMENU_H
#define CONTEXTMENU_H

#include <QMainWindow>
#include <QObject>
#include <QTextEdit>

class QMenu;
class QPrinter;
class QContextEvent;


class ContextMenu : public QTextEdit
{
    Q_OBJECT

public:
    ContextMenu(QWidget* parent = nullptr);
    void print(QPrinter* printer);

    void setTextCopyButton(QString text);
    void setTextPasteButton(QString text);
    void setTextSendToPrintButton(QString text);
    void setTextCopyFormatButton(QString text);
    void setTextPasteFormatButton(QString text);
    void setTextPasteCurrentDate(QString text);
    void setTextPasteCurrentTime(QString text);

protected:
    void contextMenuEvent(QContextMenuEvent* event) override;

public slots:
    void on_copyText_clicked();
    void on_pasteText_clicked();
    void on_sendToPrint_clicked();
    void on_copyFormatAction_clicked();
    void on_pasteFormatAction_clicked();
    void on_pasteCurrentDate();
    void on_pasteCurrentTime();

private:
    QMenu* menu;

    QAction* copyAction;
    QAction* pasteAction;
    QAction* sendToPrintAction;
    QAction* copyFormatAction;
    QAction* pasteFormatAction;
    QAction* pasteCurrentDate;
    QAction* pasteCurrentTime;

    QString lang;
};

#endif // CONTEXTMENU_H
