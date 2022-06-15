#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "hotkeyswindow.h"
#include "helpwindow.h"

#include <QFileDialog>
#include <QTextStream>
#include <QApplication>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setGeometry(QRect(0, 0, 500, 600));

    fileMenu = new QMenu;
    ui->menubar->addMenu(fileMenu);
    settings = new QMenu;
    ui->menubar->addMenu(settings);
    help = new QMenu;
    ui->menubar->addMenu(help);

    hotkeysWindow = nullptr;
    helpWindow = nullptr;

    textEdit = new QTextEdit(this);
    textEdit->setGeometry(QRect(10, 30, 480, 560));

    newFile = new QAction;
    fileMenu->addAction(newFile);
    connect(newFile, &QAction::triggered, this, &MainWindow::on_newFile_clicked);

    open = new QAction;
    fileMenu->addAction(open);
    connect(open, &QAction::triggered, this, &MainWindow::on_open_clicked);

    openReadOnly = new QAction;
    fileMenu->addAction(openReadOnly);
    connect(openReadOnly, &QAction::triggered, this, &MainWindow::on_openReadOnly_clicked);

    save = new QAction;
    fileMenu->addAction(save);
    connect(save, &QAction::triggered, this, &MainWindow::on_save_clicked);

    changeLangToRu = new QAction;
    fileMenu->addAction(changeLangToRu);
    connect(changeLangToRu, &QAction::triggered, this, &MainWindow::on_changeLangToRu_clicked);

    changeLangToEn = new QAction;
    fileMenu->addAction(changeLangToEn);
    connect(changeLangToEn, &QAction::triggered, this, &MainWindow::on_changeLangToEn_clicked);

    hotkeys = new QAction;
    settings->addAction(hotkeys);
    connect(hotkeys, &QAction::triggered, this, &MainWindow::on_changeHotkeys_clicked);

    about = new QAction;
    help->addAction(about);
    connect(about, &QAction::triggered, this, &MainWindow::on_help_clicked);

    keyOpen = new QShortcut(this);
    keyOpen->setKey(Qt::CTRL + Qt::Key_O);
    connect(keyOpen, &QShortcut::activated, this, &MainWindow::on_open_clicked);

    keySave = new QShortcut(this);
    keySave->setKey(Qt::CTRL + Qt::Key_S);
    connect(keySave, &QShortcut::activated, this, &MainWindow::on_save_clicked);

    keyNew = new QShortcut(this);
    keyNew->setKey(Qt::CTRL + Qt::Key_N);
    connect(keyNew, &QShortcut::activated, this, &MainWindow::on_newFile_clicked);

    keyQuit = new QShortcut(this);
    keyQuit->setKey(Qt::CTRL + Qt::Key_Q);
    connect(keyQuit, &QShortcut::activated, this, &MainWindow::quitApp);

    lang = "en";
    setLanguage(lang);
}

MainWindow::~MainWindow()
{
    if(textEdit) delete textEdit;
    if(fileMenu) delete fileMenu;
    if(settings) delete settings;
    if(help) delete help;
    if(newFile) delete newFile;
    if(open) delete open;
    if(openReadOnly) delete openReadOnly;
    if(save) delete save;
    if(changeLangToRu) delete changeLangToRu;
    if(changeLangToEn) delete changeLangToEn;
    if(about) delete about;
    if(helpWindow) delete helpWindow;
    if(hotkeysWindow) delete hotkeysWindow;
    if(keyOpen) delete keyOpen;
    if(keySave) delete keySave;
    if(keyNew) delete keyNew;
    if(keyQuit) delete keyQuit;
    delete ui;
}


void MainWindow::on_newFile_clicked()
{
    this->textEdit->clear();
}

void MainWindow::on_open_clicked()
{
    filename = QFileDialog::getOpenFileName(this, tr("Choose txt file..."), QDir::currentPath(), "Text(*.txt)");

    if(filename.length() > 0)
    {
        textEdit->setReadOnly(false);
        OpenFileTxt();
    }
}

void MainWindow::on_openReadOnly_clicked()
{
    filename = QFileDialog::getOpenFileName(this, tr("Choose txt file..."), QDir::currentPath(), "Text(*.txt)");

    if(filename.length() > 0)
    {
        textEdit->setReadOnly(true);
        OpenFileTxt();
    }
}

void MainWindow::on_save_clicked()
{
    filename = QFileDialog::getSaveFileName(this, tr("Choose directory..."), QDir::current().path(), "Text(*.txt)");
    if(filename.length() > 0)
    {
        SaveTextFile();
    }
}

void MainWindow::on_changeLangToRu_clicked()
{
    lang.clear();
    lang = "ru";
    setLanguage(lang);
}


void MainWindow::on_changeLangToEn_clicked()
{
    lang.clear();
    lang = "en";
    setLanguage(lang);
}

void MainWindow::on_help_clicked()
{
    helpWindow = new HelpWindow(translator, lang);
    connect(helpWindow, &HelpWindow::helpClose, this, &MainWindow::deleteHelpWindow);
    helpWindow->show();
}

void MainWindow::deleteHelpWindow()
{
    delete helpWindow;
    helpWindow = nullptr;
}

void MainWindow::OpenFileTxt()
{
    int index = filename.indexOf(".txt");

    if(index != -1 && filename.length() - 4 == index)
    {
        QFile file(filename);
        if(file.open(QIODevice::ReadOnly | QIODevice::ExistingOnly))
        {
            QTextStream stream(&file);
            textEdit->setPlainText(stream.readAll());
            file.close();
        }
    }
}

void MainWindow::SaveTextFile()
{
    QString ext = QString(&(filename.data()[filename.length() - 4]));
    if(ext == ".txt")
    {
        QFile file(filename);
        if(file.open(QFile::WriteOnly | QFile::NewOnly))
        {
            QTextStream stream(&file);
            stream << textEdit->toPlainText();
            file.close();
        }
    }
}


void MainWindow::quitApp()
{
    qApp->quit();
}


void MainWindow::on_changeHotkeys_clicked()
{
    hotkeysWindow = new HotkeysWindow(translator,
                                      lang,
                                      keyOpen->key().toString(),
                                      keySave->key().toString(),
                                      keyNew->key().toString(),
                                      keyQuit->key().toString());
    connect(hotkeysWindow, &HotkeysWindow::hotkeysWindowClose, this, &MainWindow::deleteChangeHotkeysWindow);
    connect(hotkeysWindow, &HotkeysWindow::hotkeysSave, this, &MainWindow::changeHotkeys);
    hotkeysWindow->show();
}

void MainWindow::deleteChangeHotkeysWindow()
{
    delete hotkeysWindow;
    hotkeysWindow = nullptr;
}

void MainWindow::changeHotkeys(QList<QStandardItem* > hotkeys)
{
    if(!(hotkeys[0]->text().isEmpty()))
    {
        keyOpen->setKey(hotkeys[0]->text());
    }
    if(!(hotkeys[1]->text().isEmpty()))
    {
        keySave->setKey(hotkeys[1]->text());
    }
    if(!(hotkeys[2]->text().isEmpty()))
    {
        keyNew->setKey(hotkeys[2]->text());
    }
    if(!(hotkeys[3]->text().isEmpty()))
    {
        keyQuit->setKey(hotkeys[3]->text());
    }
}

void MainWindow::setLanguage(const QString lang)
{
    if(translator.load(":/TextEdit_" + lang))
    {
        qApp->installTranslator(&translator);
    }

    this->setWindowTitle(tr("Text Editor"));
    fileMenu->setTitle(tr("File"));
    settings->setTitle(tr("Settings"));
    help->setTitle(tr("Help"));
    newFile->setText(tr("New"));
    open->setText(tr("Open"));
    openReadOnly->setText(tr("Open read-only"));
    save->setText(tr("Save"));
    changeLangToRu->setText(tr("Change language to Ru"));
    changeLangToEn->setText(tr("Change language to En"));
    hotkeys->setText(tr("Change hotkeys"));
    about->setText(tr("About"));
}
