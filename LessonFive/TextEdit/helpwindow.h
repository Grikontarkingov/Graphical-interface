#ifndef HELPWINDOW_H
#define HELPWINDOW_H

#include <QWidget>
#include <QTextEdit>
#include <QCloseEvent>
#include <QTranslator>

namespace Ui {
class HelpWindow;
}

class HelpWindow : public QWidget
{
    Q_OBJECT

public:
    HelpWindow(QTranslator& translator,
               QString& language);
    ~HelpWindow();

signals:
    void helpClose();

protected:
    virtual void closeEvent(QCloseEvent* event);

private:
    void OpenFileTxt();

    Ui::HelpWindow *ui;

    QTextEdit* textEdit;
    QTranslator& translate;
    QString& lang;
};

#endif // HELPWINDOW_H
