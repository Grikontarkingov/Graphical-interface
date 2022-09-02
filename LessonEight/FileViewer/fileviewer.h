#ifndef FILEVIEWER_H
#define FILEVIEWER_H

#include "findwindow.h"

#include <QWidget>
#include <QStandardItemModel>
#include <QTextEdit>
#include <QPushButton>
#include <QTreeView>
#include <QListView>
#include <QDir>

class FileViewer : public QWidget
{
    Q_OBJECT
public:
    explicit FileViewer(QWidget *parent = nullptr);
    ~FileViewer();

private slots:
    void openResourses(const QModelIndex &index);
    void upLevel();
    void openDirectoryFromNavigation(const QModelIndex &index);
    void openDirectoryFromTree(const QModelIndex &index);
    void expandDir(const QModelIndex & index );
    void finding();
    void deleteFindWindow();

private:
    void rebuildModelList(QString str);
    void rebuildModelTree(QString path);
    QList<QStandardItem*> getDirs(QString dir);
    QList<QStandardItem*> getAllDirs(QString dir);
    bool haveDirectory(QString in);
    void setNewModelTree(QStandardItemModel* newmodel);
    void setNewModelList(QStandardItemModel* newmodel);
    QDir getPath(const QModelIndex &index);

    FindWindow* findWindow;

    QStandardItemModel *modelTree;
    QStandardItemModel *modelList;

    QTextEdit* currentPathText;

    QPushButton* backPath;
    QPushButton* find;

    QTreeView* treePath;
    QListView* listPath;
};

#endif // FILEVIEWER_H
