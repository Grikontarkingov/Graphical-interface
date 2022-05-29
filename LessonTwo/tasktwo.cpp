#include "tasktwo.h"
#include "ui_tasktwo.h"

#include <QGroupBox>
#include <QHBoxLayout>
#include <QPushButton>

TaskTwo::TaskTwo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TaskTwo)
{
    ui->setupUi(this);
    this->setWindowTitle("Task Two");

    taskTwo();
}

TaskTwo::~TaskTwo()
{
    delete model;
    delete listView;

    delete pBackToMainMenu;
    delete pAddLangProg;
    delete pDeleteLangProg;
    delete pDown;
    delete pUp;

    delete pWithIcon;
    delete ui;
}

void TaskTwo::on_pBackToMainMenu_clicked()
{
    this->close();
    emit mainWindow();
}

void TaskTwo::on_pAddLangProg_clicked()
{
    model->appendRow(new QStandardItem(QIcon("F:/GBTest/Graphical interface in C++(Qt)/LessonTwo/LessonTwo/Icon/Default.png"), "New Lang"));
}

void TaskTwo::on_pDeleteLangProg_clicked()
{

    int row = listView->currentIndex().row();

    model->removeRow(row);
}

void TaskTwo::on_pWithIcon_clicked()
{
    if(pWithIcon->isChecked())
    {
        listView->setViewMode(QListView::IconMode);
    }
    else
    {
        listView->setViewMode(QListView::ListMode);
    }
}

void TaskTwo::on_pUp_clicked()
{
    int row = listView->currentIndex().row();
    if(0 == row) return;

    QList<QStandardItem* > current = model->takeRow(row);
    model->insertRow(row - 1, current);
}

void TaskTwo::on_pDown_clicked()
{
    int row = listView->currentIndex().row();
    if(row == (model->rowCount() - 1)) return;

    QList<QStandardItem* > current = model->takeRow(row);
    model->insertRow(row + 1, current);
}

void TaskTwo::taskTwo()
{
    model = new QStandardItemModel(this);
    model->appendRow(new QStandardItem(QIcon("F:/GBTest/Graphical interface in C++(Qt)/LessonTwo/LessonTwo/Icon/C++.png"), "C++"));
    model->appendRow(new QStandardItem(QIcon("F:/GBTest/Graphical interface in C++(Qt)/LessonTwo/LessonTwo/Icon/Python.png"), "Python"));
    model->appendRow(new QStandardItem(QIcon("F:/GBTest/Graphical interface in C++(Qt)/LessonTwo/LessonTwo/Icon/Java.png"), "Java"));
    model->appendRow(new QStandardItem(QIcon("F:/GBTest/Graphical interface in C++(Qt)/LessonTwo/LessonTwo/Icon/C#.png"), "C#"));
    model->appendRow(new QStandardItem(QIcon("F:/GBTest/Graphical interface in C++(Qt)/LessonTwo/LessonTwo/Icon/PHP.png"), "PHP"));
    model->appendRow(new QStandardItem(QIcon("F:/GBTest/Graphical interface in C++(Qt)/LessonTwo/LessonTwo/Icon/JavaScript.png"), "JavaScript"));

    pBackToMainMenu = new QPushButton(this);
    pBackToMainMenu->setText("Main menu");
    pBackToMainMenu->setFont(QFont("Segoe UI", 11));
    connect(pBackToMainMenu, SIGNAL(clicked()), this, SLOT(on_pBackToMainMenu_clicked()));

    pAddLangProg = new QPushButton(this);
    pAddLangProg->setText("Add");
    pAddLangProg->setFont(QFont("Segoe UI", 11));
    connect(pAddLangProg, SIGNAL(clicked()), this, SLOT(on_pAddLangProg_clicked()));

    pDeleteLangProg = new QPushButton(this);
    pDeleteLangProg->setText("Delete");
    pDeleteLangProg->setFont(QFont("Segoe UI", 11));
    connect(pDeleteLangProg, SIGNAL(clicked()), this, SLOT(on_pDeleteLangProg_clicked()));

    pWithIcon = new QCheckBox(this);
    pWithIcon->setText("With Icon");
    pWithIcon->setFont(QFont("Segoe UI", 11));
    pWithIcon->setChecked(true);
    connect(pWithIcon, SIGNAL(clicked()), this, SLOT(on_pWithIcon_clicked()));

    QGroupBox* pGroupBoxUpper = new QGroupBox;
    QHBoxLayout* phboxLayoutUpperGroupBox = new QHBoxLayout;
    phboxLayoutUpperGroupBox->addWidget(pBackToMainMenu);
    phboxLayoutUpperGroupBox->addWidget(pAddLangProg);
    phboxLayoutUpperGroupBox->addWidget(pDeleteLangProg);
    phboxLayoutUpperGroupBox->addWidget(pWithIcon);
    pGroupBoxUpper->setLayout(phboxLayoutUpperGroupBox);

    pUp = new QPushButton(this);
    pUp->setText("Up");
    pUp->setFont(QFont("Segoe UI", 11));
    connect(pUp, SIGNAL(clicked()), this, SLOT(on_pUp_clicked()));

    pDown = new QPushButton(this);
    pDown->setText("Down");
    pDown->setFont(QFont("Segoe UI", 11));
    connect(pDown, SIGNAL(clicked()), this, SLOT(on_pDown_clicked()));

    QGroupBox* pGroupBoxUpDown = new QGroupBox;
    QVBoxLayout* pBoxLayoutUpDown = new QVBoxLayout;
    pBoxLayoutUpDown->addWidget(pUp);
    pBoxLayoutUpDown->addWidget(pDown);
    pGroupBoxUpDown->setLayout(pBoxLayoutUpDown);

    listView = new QListView;
    listView->setMovement(QListView::Snap);
    listView->setModel(model);
    listView->setViewMode(QListView::IconMode);
    listView->setDragDropMode(QListView::NoDragDrop);
    listView->setResizeMode(QListView::Adjust);

    QGroupBox* pGroupBoxDowner = new QGroupBox;
    QHBoxLayout* phboxLayoutDownerGroupBox = new QHBoxLayout;
    phboxLayoutDownerGroupBox->addWidget(listView);
    phboxLayoutDownerGroupBox->addWidget(pGroupBoxUpDown);
    pGroupBoxDowner->setLayout(phboxLayoutDownerGroupBox);

    QVBoxLayout* pBoxLayout = new QVBoxLayout;
    pBoxLayout->addWidget(pGroupBoxUpper);
    pBoxLayout->addWidget(pGroupBoxDowner);
    this->setLayout(pBoxLayout);
}
