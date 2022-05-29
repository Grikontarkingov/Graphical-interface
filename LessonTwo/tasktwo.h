#ifndef TASKTWO_H
#define TASKTWO_H

#include <QWidget>
#include <QStandardItemModel>
#include <QListView>
#include <QPushButton>
#include <QCheckBox>

namespace Ui {
class TaskTwo;
}

class TaskTwo : public QWidget
{
    Q_OBJECT

public:
    explicit TaskTwo(QWidget *parent = nullptr);
    ~TaskTwo();

signals:
    void mainWindow();

private slots:
    void on_pBackToMainMenu_clicked();
    void on_pAddLangProg_clicked();
    void on_pDeleteLangProg_clicked();
    void on_pWithIcon_clicked();
    void on_pUp_clicked();
    void on_pDown_clicked();

private:
    void taskTwo();

    Ui::TaskTwo *ui;
    QStandardItemModel* model;
    QListView* listView;

    QPushButton* pBackToMainMenu;
    QPushButton* pAddLangProg;
    QPushButton* pDeleteLangProg;
    QPushButton* pDown;
    QPushButton* pUp;

    QCheckBox* pWithIcon;
};

#endif // TASKTWO_H
