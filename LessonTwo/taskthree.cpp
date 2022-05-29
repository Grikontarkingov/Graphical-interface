#include "taskthree.h"
#include "ui_taskthree.h"

#include <QVBoxLayout>
#include <QGroupBox>

TaskThree::TaskThree(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TaskThree)
{
    ui->setupUi(this);
    this->setWindowTitle("Task Three");

    taskThree();
}

TaskThree::~TaskThree()
{
    delete pTableView;
    delete pBackToMainMenu;
    delete ui;
}


void TaskThree::on_backToMainMenuButton_clicked()
{
    this->close();
    emit mainWindow();
}

void TaskThree::on_pChangeColor_clicked()
{
    int row = pTableView->currentIndex().row();

    for(int i {0}; i < pStandardItemModel->columnCount(); ++i)
    {
        pStandardItemModel->setData(pStandardItemModel->index(row, i), QColor(Qt::red), Qt::BackgroundRole);
    }
}

void TaskThree::on_pAddRow_clicked()
{
    QList<QStandardItem*> row;
    row.reserve(pStandardItemModel->columnCount());
    pStandardItemModel->appendRow(row);
}


void TaskThree::taskThree()
{
    pStandardItemModel = new QStandardItemModel(this);

    pTableView = new QTableView(this);
    pTableView->setModel(pStandardItemModel);
    pStandardItemModel->setColumnCount(4);
    QStringList* list = new QStringList;
    *list << "№" << "Computer name" << "IP address" << "Mac address";
    pStandardItemModel->setHorizontalHeaderLabels(*list);

    pBackToMainMenu = new QPushButton(this);
    pBackToMainMenu->setText("Main menu");
    pBackToMainMenu->setFont(QFont("Segoe UI", 11));
    connect(pBackToMainMenu, SIGNAL(clicked()), this, SLOT(on_pBackToMainMenu_clicked()));

    pChangeColor = new QPushButton(this);
    pChangeColor->setText("Change color");
    pChangeColor->setFont(QFont("Segoe UI", 11));
    connect(pChangeColor, SIGNAL(clicked()), this, SLOT(on_pChangeColor_clicked()));

    pAddRow = new QPushButton(this);
    pAddRow->setText("Add row");
    pAddRow->setFont(QFont("Segoe UI", 11));
    connect(pAddRow, SIGNAL(clicked()), this, SLOT(on_pAddRow_clicked()));

    QGroupBox* pGroupBoxUpper = new QGroupBox;
    QHBoxLayout* phboxLayoutUpper = new QHBoxLayout;
    phboxLayoutUpper->addWidget(pBackToMainMenu);
    phboxLayoutUpper->addWidget(pAddRow);
    phboxLayoutUpper->addWidget(pChangeColor);
    pGroupBoxUpper->setLayout(phboxLayoutUpper);

    QVBoxLayout* pvboxLayout = new QVBoxLayout;
    pvboxLayout->addWidget(pGroupBoxUpper);
    pvboxLayout->addWidget(pTableView);

    this->setLayout(pvboxLayout);
}
