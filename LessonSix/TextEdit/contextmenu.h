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

protected:
    void contextMenuEvent(QContextMenuEvent* event) override;

public slots:
    void on_copyText_clicked();
    void on_pasteText_clicked();
    void on_sendToPrint_clicked();

private:
    QMenu* menu;

    QAction* copyAction;
    QAction* pasteAction;
    QAction* sendToPrintAction;
};

#endif // CONTEXTMENU_H
