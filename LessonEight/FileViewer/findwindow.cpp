#include "findwindow.h"

#include <QCloseEvent>
#include <QDir>
#include <QStatusBar>

FindWindow::FindWindow(QWidget *parent)
: QMainWindow(parent)
{
    QWidget *centerWidget = new QWidget(this);
    setCentralWidget(centerWidget);

    QGridLayout *layout = new QGridLayout(this);
    centerWidget->setLayout(layout);

    searchEdit = new QLineEdit(this);
    layout->addWidget(searchEdit, 0, 0, 1, 3);

    selDrive = new QComboBox(this);
    layout->addWidget(selDrive, 0, 3);

    if (QSysInfo::productType() == "windows") // Для ОС Windows
    {
        QFileInfoList infolist = QDir::drives();
        int amount = infolist.count();
        for (int i = 0; i < amount; i++)
        {
            selDrive->addItem(infolist.at(i).path());
        }
    }
    else { // Для UNIX-подобных систем
        QStringList str = {"/", "/home/", "/mount/", "/opt/"};
        int amount = str.count();
        for (int i = 0; i < amount; i++)
        {
            selDrive->addItem(str.at(i));
        }
    }

    startFindButton = new QPushButton(this);
    startFindButton->setText(tr("Find"));
    layout->addWidget(startFindButton, 0, 5);
    connect(startFindButton, &QPushButton::clicked, this, &FindWindow::findFileSlot);

    infoText = new QTextEdit(this);
    layout->addWidget(infoText, 1, 0, 10, 10);

    controllerl = new Controller(this);

    statusLabel = new QLabel(this);

    QStatusBar *statusBar = this->statusBar();
    statusBar->addWidget(statusLabel);
    connect(controllerl, &Controller::changFindPath, this, &FindWindow::changStatusLabel);
    connect(controllerl, &Controller::genPathOfFile, this, &FindWindow::printFindFile);
    connect(controllerl, &Controller::genPathOfDir, this, &FindWindow::printFindDir);
    connect(controllerl, &Controller::newFind, infoText, &QTextEdit::clear);
}

FindWindow::~FindWindow()
{
}

void FindWindow::findFileSlot()
{
    QString linesearch = searchEdit->text();

    if (linesearch.length() == 0) return;

    controllerl->startFind(selDrive->currentText(), linesearch);
}

void FindWindow::changStatusLabel(QString line)
{
    statusLabel->setText(line);
}

void FindWindow::printFindFile(QString str)
{
    infoText->append(str);
}

void FindWindow::printFindDir(QString dir)
{
    infoText->append(dir);
}

void FindWindow::closeEvent(QCloseEvent* event)
{
    event->accept();
    emit findWindowClose();
}
