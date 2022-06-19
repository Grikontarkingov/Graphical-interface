#include "myqtwidget.h"

#include <QDir>

MyQtWidget::MyQtWidget(QWidget *parent)
    : QWidget(parent),
      model(nullptr)
{
    gridLay = new QGridLayout(this);
    this->setLayout(gridLay);
    tree = new QTreeView(this);
    connect(tree, &QTreeView::doubleClicked, this, &MyQtWidget::selectDirectory);

    gridLay->addWidget(tree, 1, 0, 10, 10);

    setMinimumSize(QSize(500, 600));

    if("windows" == QSysInfo::productType())
    {
        diskSelBox = new QComboBox(this);

        currentPathBar = new QTextEdit(this);
        currentPathBar->setMaximumHeight(23);
        gridLay->addWidget(currentPathBar, 0, 2, 1, 1);
        currentPathBar->setText(diskSelBox->currentText());
        connect(currentPathBar, &QTextEdit::selectionChanged, this, &MyQtWidget::changePathBar);

        QFileInfoList list = QDir::drives();
        QFileInfoList::const_iterator listdisk = list.begin();
        int amount = list.count();

        for(int i = 0; i < amount; i++)
        {
            diskSelBox->addItem(listdisk->path());
            listdisk++;
        }

        if(amount > 0)
        {
            rebuildModel(list.at(0).path());
        }

        gridLay->addWidget(diskSelBox, 0, 0, 1, 2);
        connect(diskSelBox, SIGNAL(activated(int)), this, SLOT(chgDisk(int)));
    }
    else
    {
        mainPath = new QPushButton(this);
        mainPath->setText("/");
        gridLay->addWidget(mainPath, 0, 0, 1, 2);
        connect(mainPath, &QPushButton::clicked, this, &MyQtWidget::goMainPath);
        rebuildModel("/");
    }
}

MyQtWidget::~MyQtWidget()
{
    if(gridLay) delete gridLay;
    if(tree) delete tree;
    if(mainPath) delete mainPath;
    if(diskSelBox) delete diskSelBox;
    if(currentPathBar) delete currentPathBar;
    if(model) delete model;
}

void MyQtWidget::chgDisk(int index)
{
    QFileInfoList list = QDir::drives();
    rebuildModel(list.at(index).path());
}

void MyQtWidget::goMainPath()
{
    rebuildModel("/");
}

void MyQtWidget::setNewModel(QStandardItemModel* newmodel)
{
    tree->setModel(newmodel);
    model = newmodel;
}

void MyQtWidget::rebuildModel(QString str)
{
    currentPath = str;

    currentPathBar->clear();
    currentPathBar->setText(currentPath);

    QStandardItemModel *model = new QStandardItemModel(this);
    QList<QStandardItem*> items;
    items.append(new QStandardItem(QIcon(QApplication::style()->standardIcon(QStyle::SP_DriveHDIcon)), str));
    model->appendRow(items);

    QDir dir(str);
    dir.setFilter(QDir::Hidden | QDir::NoSymLinks | QDir::Dirs);

    QStringList list = dir.entryList();
    int amount = list.count();

    QList<QStandardItem*>folders;
    for (int i = 0; i < amount; i++)
    {
        QStandardItem* f = new QStandardItem(QIcon(QApplication::style()->standardIcon(QStyle::SP_DirIcon)), list.at(i));
        folders.append(f);
    }

    items.at(0)->appendRows(folders);
    dir.setFilter(QDir::Hidden | QDir::NoSymLinks | QDir::Files);
    amount = list.count();

    QList<QStandardItem*>files;
    for (int i = 0; i < amount; i++)
    {
        QStandardItem* f = new QStandardItem(QIcon(QApplication::style()->standardIcon(QStyle::SP_FileIcon)), list.at(i));
        files.append(f);
    }

    items.at(0)->appendRows(files);
    setNewModel(model);
}

void MyQtWidget::selectDirectory(const QModelIndex &index)
{
    QDir check;
    if(check.cd((currentPath + index.data().toString() + "/")))
    {
        currentPath = currentPath + index.data().toString() + "/";
        rebuildModel(currentPath);
    }
}


void MyQtWidget::changePathBar()
{
    QDir check;
    if(check.cd(currentPathBar->toPlainText()))
    {
        currentPath = currentPathBar->toPlainText();
        rebuildModel(currentPath);
    }
}
