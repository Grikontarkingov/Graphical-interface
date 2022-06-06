#include "hotkeyswindow.h"
#include "ui_hotkeyswindow.h"

#include <QCloseEvent>
#include <QVBoxLayout>

HotkeysWindow::HotkeysWindow(QWidget *parent)
    :
      QWidget(parent),
      ui(new Ui::HotkeysWindow)
{
    ui->setupUi(this);
}
HotkeysWindow::HotkeysWindow(QString openFile,
                             QString saveFile,
                             QString newFile,
                             QString quitApp)
    :
      QWidget(nullptr),
      ui(new Ui::HotkeysWindow),
      hotkeyOpen(openFile),
      hotkeySave(saveFile),
      hotkeyNew(newFile),
      hotkeyQuit(quitApp)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("Hotkeys"));
    this->setGeometry(0, 0, 339, 200);

   createTable();
   createSaveButton();
}

HotkeysWindow::~HotkeysWindow()
{
    if(hotkeys) delete hotkeys;
    if(model) delete model;
    if(save) delete save;
    delete ui;
}

void HotkeysWindow::closeEvent(QCloseEvent* event)
{
    event->accept();
    emit hotkeysWindowClose();
}


void HotkeysWindow::createTable()
{
    model = new QStandardItemModel(this);
    hotkeys = new QTableView(this);
    hotkeys->setModel(model);

    model->setColumnCount(3);

    QStringList* list = new QStringList;
    *list << tr("Hotkeys") << tr("Current") << tr("Set");
    model->setHorizontalHeaderLabels(*list);

    QList<QStandardItem*> row;
    row.reserve(model->columnCount());
    row.append(new QStandardItem(tr("Open file")));
    row.append(new QStandardItem(hotkeyOpen));
    row.append(new QStandardItem(""));
    row.at(0)->setEditable(false);
    row.at(1)->setEditable(false);
    model->appendRow(row);
    row.clear();

    row.append(new QStandardItem(tr("Save file")));
    row.append(new QStandardItem(hotkeySave));
    row.append(new QStandardItem(""));
    row.at(0)->setEditable(false);
    row.at(1)->setEditable(false);
    model->appendRow(row);
    row.clear();

    row.append(new QStandardItem(tr("New file")));
    row.append(new QStandardItem(hotkeyNew));
    row.append(new QStandardItem(""));
    row.at(0)->setEditable(false);
    row.at(1)->setEditable(false);
    model->appendRow(row);
    row.clear();

    row.append(new QStandardItem(tr("Quit")));
    row.append(new QStandardItem(hotkeyQuit));
    row.append(new QStandardItem(""));
    row.at(0)->setEditable(false);
    row.at(1)->setEditable(false);
    model->appendRow(row);
    row.clear();

    QVBoxLayout* vboxLayout = new QVBoxLayout;
    vboxLayout->addWidget(hotkeys);

    this->setLayout(vboxLayout);
}

void HotkeysWindow::createSaveButton()
{
    save = new QPushButton(this);
    save->setText(tr("Save and close"));
    this->layout()->addWidget(save);
    connect(save, &QPushButton::clicked, this, &HotkeysWindow::on_save_clicked);
}

void HotkeysWindow::on_save_clicked()
{
    QList<QStandardItem* > newHotkeys;
    newHotkeys = model->takeColumn(2);
    emit hotkeysSave(newHotkeys);
    QEvent* event = new QEvent(QEvent::Close);
    QGuiApplication::postEvent(this, event, Qt::NormalEventPriority);
}
