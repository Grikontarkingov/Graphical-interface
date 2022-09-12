#ifndef TASKSVIEW_H
#define TASKSVIEW_H

#include <QSqlRelationalTableModel>
#include <QWidget>

namespace Ui {
class TasksView;
}

class TasksView : public QWidget
{
    Q_OBJECT

public:
    explicit TasksView(QSqlRelationalTableModel* model);
    ~TasksView();

    void updateTasks(QSqlRelationalTableModel* model);

private:
    Ui::TasksView *ui;

signals:
    void closeWindow();

protected:
    void closeEvent(QCloseEvent* event)
    {
        this->close();
        emit closeWindow();
        Q_UNUSED(event)
    }

};

#endif // TASKSVIEW_H
