#ifndef TASKTHREE_H
#define TASKTHREE_H

#include <QWidget>
#include <QTableView>
#include <QPushButton>
#include <QStandardItemModel>

namespace Ui {
class TaskThree;
}

class TaskThree : public QWidget
{
    Q_OBJECT

public:
    explicit TaskThree(QWidget *parent = nullptr);
    ~TaskThree();

signals:
    void mainWindow();

private slots:
    void on_backToMainMenuButton_clicked();
    void on_pChangeColor_clicked();
    void on_pAddRow_clicked();

private:
    void taskThree();

    Ui::TaskThree *ui;
    QTableView* pTableView;
    QStandardItemModel* pStandardItemModel;

    QPushButton* pBackToMainMenu;
    QPushButton* pAddRow;
    QPushButton* pChangeColor;
};

#endif // TASKTHREE_H
