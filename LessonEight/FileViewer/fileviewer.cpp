#include "fileviewer.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDir>
#include <QApplication>

FileViewer::FileViewer(QWidget *parent)
    : QWidget(parent),
      modelTree(nullptr),
      modelList(nullptr),
      currentPathText(new QTextEdit(this)),
      backPath(new QPushButton(this)),
      find(new QPushButton(this)),
      treePath(new QTreeView(this)),
      listPath(new QListView(this))
{
    findWindow = nullptr;
    QVBoxLayout* verticalLayout = new QVBoxLayout;

    QHBoxLayout* upperHorizontalLayout = new QHBoxLayout;

    backPath->setMaximumHeight(30);
    backPath->setMaximumWidth(25);
    backPath->setText("\u2191");
    upperHorizontalLayout->addWidget(backPath);
    connect(backPath, &QPushButton::clicked, this, &FileViewer::upLevel);

    currentPathText->setMaximumHeight(23);
    upperHorizontalLayout->addWidget(currentPathText);
    currentPathText->setText("This Computer\\");
    currentPathText->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    find->setText("Find");
    upperHorizontalLayout->addWidget(find);
    connect(find, &QPushButton::clicked, this, &FileViewer::finding);

    verticalLayout->addLayout(upperHorizontalLayout);

    QHBoxLayout* downereHorizontalLayout = new QHBoxLayout;

    downereHorizontalLayout->addWidget(treePath);
    treePath->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    connect(treePath, &QTreeView::clicked, this, &FileViewer::openDirectoryFromNavigation);
    connect(treePath, &QTreeView::expanded, this, &FileViewer::expandDir);
//    connect(treePath, &QTreeView::doubleClicked, this, &FileViewer::)

    verticalLayout->addLayout(downereHorizontalLayout);

    downereHorizontalLayout->addWidget(listPath);
    listPath->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    connect(listPath, &QListView::doubleClicked, this, &FileViewer::openResourses);

    this->setLayout(verticalLayout);
    this->setMinimumSize(800, 600);

    rebuildModelList(currentPathText->toPlainText());
    rebuildModelTree("plug");
}

FileViewer::~FileViewer()
{
    if(modelTree) delete modelTree;
    if(modelList) delete modelList;
    if(currentPathText) delete currentPathText;
    if(backPath) delete backPath;
    if(treePath) delete treePath;
    if(listPath) delete listPath;
    if(find) delete find;
    if(findWindow) delete findWindow;
}

void FileViewer::setNewModelTree(QStandardItemModel* newmodel)
{
    treePath->setModel(newmodel);
    modelTree = newmodel;
}

void FileViewer::setNewModelList(QStandardItemModel* newmodel)
{
    listPath->setModel(newmodel);
    modelList = newmodel;
}

void FileViewer::rebuildModelList(QString str)
{
    if("This Computer\\" == str )
    {
        QStandardItemModel* model = new QStandardItemModel(this);

        QFileInfoList list = QDir::drives();
        QFileInfoList::const_iterator listDisk = list.begin();
        int amount = list.count();

        for(int i = 0; i < amount; ++i)
        {
            model->appendRow(new QStandardItem(QIcon(QApplication::style()->standardIcon(QStyle::SP_DriveHDIcon)), listDisk->path()));
            listDisk++;
        }
        setNewModelList(model);
    }
    else
    {
        QStandardItemModel* model = new QStandardItemModel(this);

        QDir dir(str);
        dir.setFilter(QDir::Hidden | QDir::NoSymLinks | QDir::Dirs | QDir::NoDotAndDotDot);

        QStringList list = dir.entryList();
        int amount = list.count();

        for(int i = 0; i < amount; ++i)
        {

            QStandardItem* f = new QStandardItem(QIcon(QApplication::style()->standardIcon(QStyle::SP_DirIcon)), list.at(i));
            model->appendRow(f);
        }

        dir.setFilter(QDir::Hidden | QDir::NoSymLinks | QDir::Files | QDir::NoDotAndDotDot);
        amount = list.count();

        for(int i = 0; i < amount; ++i)
        {
            QStandardItem* f = new QStandardItem(QIcon(QApplication::style()->standardIcon(QStyle::SP_FileIcon)), list.at(i));
            model->appendRow(f);
        }

        setNewModelList(model);
    }
}

void FileViewer::openResourses(const QModelIndex &index)
{
    QDir dir = currentPathText->toPlainText();
    if(dir.cd(index.data().toString()))
    {
        currentPathText->setText(dir.path());
        rebuildModelList(currentPathText->toPlainText());
    }
}

void FileViewer::upLevel()
{
    QString out = currentPathText->toPlainText();

    while(true)
    {
        if(out.isEmpty())
        {
            currentPathText->setText("This Computer\\");
            rebuildModelList(currentPathText->toPlainText());
            return;
        }
        else if('/' == out.at(out.size() - 1))
        {
            out.chop(1);
            currentPathText->setText(out);
            rebuildModelList(currentPathText->toPlainText());
            return;
        }
        else
        {
            out.chop(1);
        }
    }
}

void FileViewer::rebuildModelTree(QString path)
{
    QStandardItemModel *model = new QStandardItemModel(this);

    QFileInfoList list = QDir::drives();
    QFileInfoList::const_iterator listDisk = list.begin();
    int amountDisk = list.count();

    for(int i = 0; i < amountDisk; ++i)
    {
        QList<QStandardItem*> items;
        items.append(new QStandardItem(QIcon(QApplication::style()->standardIcon(QStyle::SP_DriveHDIcon)), listDisk->path()));
        model->appendRow(items);

        items.at(0)->appendRows(getDirs(listDisk->path()));

        ++listDisk;
    }

    setNewModelTree(model);

    Q_UNUSED(path)
}

void FileViewer::expandDir(const QModelIndex & index )
{
    QDir directory = getPath(index);
    getDirs(directory.path());
}

void FileViewer::finding()
{
    findWindow = new FindWindow;
    connect(findWindow, &FindWindow::findWindowClose, this, &FileViewer::deleteFindWindow);

    findWindow->show();
}

void FileViewer::deleteFindWindow()
{
    delete findWindow;
    findWindow = nullptr;
}

QList<QStandardItem*> FileViewer::getDirs(QString dir)
{
    QDir directory(dir);
    directory.setFilter(QDir::Hidden | QDir::NoSymLinks | QDir::Dirs | QDir::NoDotAndDotDot);

    QStringList list = directory.entryList();
    int amount = list.count();

    QList<QStandardItem*> folders;
    for(int i = 0; i < amount; i++)
    {
        if(haveDirectory(dir + list.at(i)))
        {
            folders.append(new QStandardItem(QIcon(QApplication::style()->standardIcon(QStyle::SP_DirIcon)), list.at(i)));
        }
        else
        {
            folders.append(new QStandardItem(QIcon(QApplication::style()->standardIcon(QStyle::SP_DirIcon)), list.at(i)));
        }
    }

    return folders;
}

QList<QStandardItem*> FileViewer::getAllDirs(QString dir)
{
    QDir directory(dir);
    directory.setFilter(QDir::Hidden | QDir::NoSymLinks | QDir::Dirs | QDir::NoDotAndDotDot);

    QStringList list = directory.entryList();
    int amount = list.count();

    QList<QStandardItem*>folders;
    for(int i = 0; i < amount; i++)
    {
        if(haveDirectory(dir + list.at(i)))
        {
            folders.append(new QStandardItem(QIcon(QApplication::style()->standardIcon(QStyle::SP_DirIcon)), list.at(i)));
            folders.at(i)->appendRows(getAllDirs(dir + list.at(i) + "/"));
        }
        else
        {
            folders.append(new QStandardItem(QIcon(QApplication::style()->standardIcon(QStyle::SP_DirIcon)), list.at(i)));
        }
    }

    return folders;
}

bool FileViewer::haveDirectory(QString in)
{
    QDir directory(in);
    directory.setFilter(QDir::Hidden | QDir::NoSymLinks | QDir::Dirs | QDir::NoDotAndDotDot);

    if(directory.entryList().isEmpty())
    {
        return false;
    }
    else
    {
        return true;
    }
}

void FileViewer::openDirectoryFromNavigation(const QModelIndex &index)
{
    QDir dir = getPath(index);
    currentPathText->setText(dir.path());
    rebuildModelList(currentPathText->toPlainText());
}

void FileViewer::openDirectoryFromTree(const QModelIndex &index)
{
    QDir dir = getPath(index);
    currentPathText->setText(dir.path());
    rebuildModelList(currentPathText->toPlainText());
}

QDir FileViewer::getPath(const QModelIndex &index)
{
    QDir path;

    if(index.parent().isValid())
    {
        path = getPath(index.parent());
    }

    path.cd(index.data().toString());

    return path;
}
