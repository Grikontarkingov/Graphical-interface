#ifndef HELPWINDOW_H
#define HELPWINDOW_H

#include <QWidget>
#include <QTextEdit>
#include <QCloseEvent>

namespace Ui {
class HelpWindow;
}

class HelpWindow : public QWidget
{
    Q_OBJECT

public:
    explicit HelpWindow(QWidget *parent = nullptr);
    ~HelpWindow();

signals:
    void helpClose();

protected:
    virtual void closeEvent(QCloseEvent* event);

private:
    void OpenFileTxt();

    Ui::HelpWindow *ui;

    QTextEdit* textEdit;
};

#endif // HELPWINDOW_H
