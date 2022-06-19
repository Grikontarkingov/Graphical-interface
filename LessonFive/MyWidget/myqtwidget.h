#ifndef MYQTWIDGET_H
#define MYQTWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QTreeView>
#include <QComboBox>
#include <QPushButton>
#include <QStandardItemModel>
#include <QApplication>
#include <QTextEdit>

Q_PROPERTY(QStandardItemModel *model READ getCurrentModel WRITE setNewModel)


class MyQtWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MyQtWidget(QWidget *parent = nullptr);
    ~MyQtWidget();

    void clearTree();

    inline QStandardItemModel *getCurrentModel() const { return model; }
    void setNewModel(QStandardItemModel *newmodel);
    void rebuildModel(QString str);

private slots:
    void chgDisk(int index);
    void goMainPath();
    void selectDirectory(const QModelIndex &index);
    void changePathBar();

private:
    QGridLayout *gridLay;
    QTreeView *tree;
    QPushButton *mainPath;
    QComboBox *diskSelBox;
    QTextEdit* currentPathBar;

    QStandardItemModel *model;
    QString currentPath;
};

#endif // MYQTWIDGET_H
