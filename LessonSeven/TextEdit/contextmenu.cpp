#include "contextmenu.h"

#include <QApplication>
#include <QClipboard>
#include <QMenu>
#include <QPrinter>
#include <QPrintDialog>
#include <QPainter>
#include <QContextMenuEvent>

ContextMenu::ContextMenu(QWidget* parent)
    : QTextEdit(parent)
{
    menu = new QMenu(this);
    copyAction = new QAction;
    pasteAction = new QAction;
    sendToPrintAction = new QAction;
    copyFormatAction = new QAction;
    pasteFormatAction = new QAction;

    menu->addAction(copyAction);
    menu->addAction(pasteAction);
    menu->addAction(copyFormatAction);
    menu->addAction(pasteFormatAction);

    menu->addSeparator();

    menu->addAction(sendToPrintAction);

    connect(copyAction, &QAction::triggered, this, &ContextMenu::on_copyText_clicked);
    connect(pasteAction, &QAction::triggered, this, &ContextMenu::on_pasteText_clicked);
    connect(copyFormatAction, &QAction::triggered, this, &ContextMenu::on_copyFormatAction_clicked);
    connect(pasteFormatAction, &QAction::triggered, this, &ContextMenu::on_pasteFormatAction_clicked);
    connect(sendToPrintAction, &QAction::triggered, this, &ContextMenu::on_sendToPrint_clicked);
}

void ContextMenu::contextMenuEvent(QContextMenuEvent* event)
{
    menu->exec(event->globalPos());
}

void ContextMenu::on_copyText_clicked()
{
    QString str = this->textCursor().selectedText();
    qApp->clipboard()->setText(str);
}

void ContextMenu::on_pasteText_clicked()
{
    QString str = qApp->clipboard()->text();
    this->textCursor().insertText(str);
}

void ContextMenu::on_copyFormatAction_clicked()
{
    QFont font = this->textCursor().charFormat().font();

    qApp->clipboard()->setText(font.toString());
}

void ContextMenu::on_pasteFormatAction_clicked()
{
    QFont font = qApp->clipboard()->text();

    QTextCharFormat format;
    format.setFont(font);

    this->textCursor().setCharFormat(format);
}

void ContextMenu::on_sendToPrint_clicked()
{
    QPrinter printer;

    QPrintDialog dialog(&printer, this);
    dialog.setWindowTitle(tr("Print To"));

    if(dialog.exec() != QDialog::Accepted)
    {
        return;
    }

    this->print(&printer);
}

void ContextMenu::setTextCopyButton(QString text)
{
    copyAction->setText(text.toStdString().c_str());
}

void ContextMenu::setTextPasteButton(QString text)
{
    pasteAction->setText(text.toStdString().c_str());
}

void ContextMenu::setTextSendToPrintButton(QString text)
{
    sendToPrintAction->setText(text.toStdString().c_str());
}

void ContextMenu::setTextCopyFormatButton(QString text)
{
    copyFormatAction->setText(text.toStdString().c_str());
}

void ContextMenu::setTextPasteFormatButton(QString text)
{
    pasteFormatAction->setText(text.toStdString().c_str());
}

void ContextMenu::print(QPrinter* printer)
{
    QString printStr = this->toPlainText();
    QChar* list = printStr.data();
    QStringList strlst;

    int line = 0, cursor = 0;

    for(bool gets = true; gets;)
    {
        int index = printStr.indexOf("\n", cursor);

        QString s = "";
        if(index == -1)
        {
            gets = false;
            s.append(&list[cursor], printStr.length() - cursor);
        }
        else
        {
            s.append(&list[cursor], index - cursor);
            cursor = index + 1;
            strlst << s;
        }
    }

    QPainter painter;
    painter.begin(printer);
    int h = painter.window().height();
    int amount = strlst.count();

    QFont font = painter.font();
    QFontMetrics fontMetrics(font);
    line += fontMetrics.height();

    for(int i = 0; i < amount; ++i)
    {
        QPointF pf;
        pf.setX(10);
        pf.setY(line);

        painter.drawText(pf, strlst.at(i));

        line += fontMetrics.height();

        if(h - line <= fontMetrics.height())
        {
            printer->newPage();
            line = 0;
        }
    }

    painter.end();
}
