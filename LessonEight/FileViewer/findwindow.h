#ifndef FINDWINDOW_H
#define FINDWINDOW_H

#include "controller.h"

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QGridLayout>
#include <QComboBox>
#include <QLabel>

class FindWindow : public QMainWindow
{
    Q_OBJECT
public:
    FindWindow(QWidget *parent = 0);
    ~FindWindow();

private:
    QLineEdit *searchEdit;

    QPushButton *startFindButton;

    QTextEdit *infoText;

    QComboBox *selDrive;

    Controller *controllerl;

    QLabel *statusLabel;

private slots:
    void findFileSlot();
    void changStatusLabel(QString);
    void printFindFile(QString);
    void printFindDir(QString);

signals:
    void findWindowClose();

protected:
    void closeEvent(QCloseEvent* event);
};

#endif // FINDWINDOW_H
