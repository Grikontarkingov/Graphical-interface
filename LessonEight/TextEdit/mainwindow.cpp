#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "hotkeyswindow.h"
#include "helpwindow.h"
#include "contextmenu.h"

#include <QFileDialog>
#include <QTextStream>
#include <QApplication>
#include <QDebug>
#include <QPrinter>
#include <QPrintDialog>
#include <QShortcut>
#include <QStandardItem>
#include <QMdiArea>
#include <QGridLayout>
#include <QMdiSubWindow>
#include <QToolBar>
#include <QFontComboBox >
#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpinBox>
#include <QFontDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setGeometry(QRect(0, 0, 800, 900));

    fileMenu = new QMenu;
    ui->menubar->addMenu(fileMenu);

    hotkeysWindow = nullptr;
    helpWindow = nullptr;

    textsEditors = new QMdiArea(this);
    QWidget* centralWidget = new QWidget(this);

    setCentralWidget(centralWidget);

    QGridLayout* layout = new QGridLayout(this);
    centralWidget->setLayout(layout);
    layout->addWidget(textsEditors, 0, 0, 1, 1);

    textsEditors->addSubWindow(new ContextMenu(this));
    textsEditors->setGeometry(QRect(10, 30, 480, 560));

    QFont font;
    font.setPointSize(11);
    font.setFamily("Times New Roman");

    ((ContextMenu*)textsEditors->currentSubWindow()->widget())->setFont(font);

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

    saveTo = new QAction;
    fileMenu->addAction(saveTo);
    connect(saveTo, &QAction::triggered, this, &MainWindow::on_saveTo_clicked);

    newTab = new QAction;
    fileMenu->addAction(newTab);
    connect(newTab, &QAction::triggered, this, &MainWindow::on_newTab_clicked);

    fileMenu->insertSeparator(changeLangToRu);

    changeLangToRu = new QAction;
    fileMenu->addAction(changeLangToRu);
    connect(changeLangToRu, &QAction::triggered, this, &MainWindow::on_changeLangToRu_clicked);

    changeLangToEn = new QAction;
    fileMenu->addAction(changeLangToEn);
    connect(changeLangToEn, &QAction::triggered, this, &MainWindow::on_changeLangToEn_clicked);

    fileMenu->insertSeparator(sendToPrint);

    sendToPrint = new QAction;
    fileMenu->addAction(sendToPrint);
    connect(sendToPrint, &QAction::triggered, this, &MainWindow::on_sendToPrint_clicked);

    fileMenu->insertSeparator(exitApp);

    exitApp = new QAction;
    fileMenu->addAction(exitApp);
    connect(exitApp, &QAction::triggered, this, &MainWindow::on_exitApp_clicked);

    settings = new QMenu;
    ui->menubar->addMenu(settings);

    hotkeys = new QAction;
    settings->addAction(hotkeys);
    connect(hotkeys, &QAction::triggered, this, &MainWindow::on_changeHotkeys_clicked);

    theme = new QMenu;
    settings->addMenu(theme);

    classicTheme = new QAction;
    theme->addAction(classicTheme);
    connect(classicTheme, &QAction::triggered, this, &MainWindow::on_classicTheme_clicked);

    darkTheme = new QAction;
    theme->addAction(darkTheme);
    connect(darkTheme, &QAction::triggered, this, &MainWindow::on_darkTheme_clicked);

    colorfulTheme = new QAction;
    theme->addAction(colorfulTheme);
    connect(colorfulTheme, &QAction::triggered, this, &MainWindow::on_colorfulTheme_clicked);

    help = new QMenu;
    ui->menubar->addMenu(help);

    about = new QAction;
    help->addAction(about);
    connect(about, &QAction::triggered, this, &MainWindow::on_help_clicked);

    toolBar = addToolBar(tr("Formated"));
    QGroupBox* formated = new QGroupBox(this);
    toolBar->addWidget(formated);

    QGridLayout* formatedLayout = new QGridLayout(this);
    formated->setLayout(formatedLayout);

    QFontComboBox* fonts = new QFontComboBox(this);
    fonts->setEditable(false);
    fonts->setCurrentText(((ContextMenu*)textsEditors->currentSubWindow()->widget())->font().family());
    formatedLayout->addWidget(fonts, 0, 0);
    connect(fonts, &QFontComboBox::currentTextChanged, this, &MainWindow::on_font_changed);

    QSpinBox* sizeFont = new QSpinBox(this);
    sizeFont->setRange(1, 72);
    sizeFont->setValue(((ContextMenu*)textsEditors->currentSubWindow()->widget())->textCursor().charFormat().font().pointSize());
    formatedLayout->addWidget(sizeFont, 0, 1, 1, 2);
    connect(sizeFont, &QSpinBox::textChanged, this, &MainWindow::on_pointSize_changed);

    bold = new QPushButton;
    formatedLayout->addWidget(bold, 1, 0);
    connect(bold, &QPushButton::clicked, this, &MainWindow::on_bold_clicked);

    italic = new QPushButton;
    formatedLayout->addWidget(italic, 1, 1);
    connect(italic, &QPushButton::clicked, this, &MainWindow::on_italic_clicked);

    underLined = new QPushButton;
    formatedLayout->addWidget(underLined, 1, 2);
    connect(underLined, &QPushButton::clicked, this, &MainWindow::on_underLined_clicked);

    toolBar->addSeparator();

    QGroupBox* alignment = new QGroupBox(this);
    toolBar->addWidget(alignment);

    QGridLayout* alignmentLayout = new QGridLayout(this);
    alignment->setLayout(alignmentLayout);

    alignmentLeft = new QPushButton;
    alignmentLayout->addWidget(alignmentLeft, 0, 0);
    connect(alignmentLeft, &QPushButton::clicked, this, &MainWindow::on_alignmentLeft_clicked);

    alignmentCenter = new QPushButton;
    alignmentLayout->addWidget(alignmentCenter, 0, 1);
    connect(alignmentCenter, &QPushButton::clicked, this, &MainWindow::on_alignmentCenter_clicked);

    alignmentRight = new QPushButton;
    alignmentLayout->addWidget(alignmentRight, 0, 2);
    connect(alignmentRight, &QPushButton::clicked, this, &MainWindow::on_alignmentRight_clicked);

    keyOpen = new QShortcut(this);
    keyOpen->setKey(Qt::CTRL + Qt::Key_O);
    connect(keyOpen, &QShortcut::activated, this, &MainWindow::on_open_clicked);

    keySave = new QShortcut(this);
    keySave->setKey(Qt::CTRL + Qt::Key_S);
    connect(keySave, &QShortcut::activated, this, &MainWindow::on_saveTo_clicked);

    keyNew = new QShortcut(this);
    keyNew->setKey(Qt::CTRL + Qt::Key_N);
    connect(keyNew, &QShortcut::activated, this, &MainWindow::on_newFile_clicked);

    keyQuit = new QShortcut(this);
    keyQuit->setKey(Qt::CTRL + Qt::Key_Q);
    connect(keyQuit, &QShortcut::activated, this, &MainWindow::quitApp);


    keySendToPrint = new QShortcut(this);
    keySendToPrint->setKey(Qt::CTRL + Qt::Key_P);
    connect(keySendToPrint, &QShortcut::activated, this, &MainWindow::on_sendToPrint_clicked);

    keyNewTab = new QShortcut(this);
    keyNewTab->setKey(Qt::CTRL + Qt::Key_T);
    connect(keyNewTab, &QShortcut::activated, this, &MainWindow::on_newTab_clicked);

    lang = "en";
    setLanguage(lang);
    on_classicTheme_clicked();
}

MainWindow::~MainWindow()
{
    if(fileMenu) delete fileMenu;
    if(settings) delete settings;
    if(help) delete help;
    if(newFile) delete newFile;
    if(open) delete open;
    if(openReadOnly) delete openReadOnly;
    if(save) delete save;
    if(saveTo) delete saveTo;
    if(exitApp) delete exitApp;
    if(changeLangToRu) delete changeLangToRu;
    if(changeLangToEn) delete changeLangToEn;
    if(about) delete about;
    if(helpWindow) delete helpWindow;
    if(hotkeysWindow) delete hotkeysWindow;
    if(theme) delete theme;
    if(keyOpen) delete keyOpen;
    if(keySave) delete keySave;
    if(keyNew) delete keyNew;
    if(keyQuit) delete keyQuit;
    delete ui;
}

void MainWindow::on_newFile_clicked()
{
    ((ContextMenu*)textsEditors->activeSubWindow()->widget())->clear();
}

void MainWindow::on_open_clicked()
{
    filename = QFileDialog::getOpenFileName(this, tr("Choose txt file..."), QDir::currentPath(), "Text(*.txt)");

    if(filename.length() > 0)
    {
        ((ContextMenu*)textsEditors->activeSubWindow()->widget())->setReadOnly(false);
        OpenFileTxt();
    }
}

void MainWindow::on_openReadOnly_clicked()
{
    filename = QFileDialog::getOpenFileName(this, tr("Choose txt file..."), QDir::currentPath(), "Text(*.txt)");

    if(filename.length() > 0)
    {
        ((ContextMenu*)textsEditors->activeSubWindow()->widget())->setReadOnly(true);
        OpenFileTxt();
    }
}

void MainWindow::on_save_clicked()
{
    QFile file(filename);
    if(file.exists())
    {
        SaveTextFile();
    }
    else
    {
        on_saveTo_clicked();
    }
}

void MainWindow::on_saveTo_clicked()
{
    filename = QFileDialog::getSaveFileName(this, tr("Choose directory..."), QDir::current().path(), "Text(*.txt)");
    if(filename.length() > 0)
    {
        SaveTextFile();
    }
}


void MainWindow::on_newTab_clicked()
{
    ContextMenu* newContextMenu = new ContextMenu(this);
    newContextMenu->setTextCopyButton(tr("Copy"));
    newContextMenu->setTextPasteButton(tr("Paste"));
    newContextMenu->setTextSendToPrintButton(tr("SendToPrint"));
    newContextMenu->setTextCopyFormatButton(tr("Copy format"));
    newContextMenu->setTextPasteFormatButton(tr("Paste format"));

    QMdiSubWindow* textEditor = textsEditors->addSubWindow(newContextMenu);
    textEditor->setAttribute(Qt::WA_DeleteOnClose);
    textEditor->show();
}


void MainWindow::on_sendToPrint_clicked()
{
    QPrinter printer;

    QPrintDialog dialog(&printer, this);
    dialog.setWindowTitle(tr("Print To"));

    if(dialog.exec() != QDialog::Accepted)
    {
        return;
    }

    ((ContextMenu*)textsEditors->activeSubWindow()->widget())->print(&printer);
}

void MainWindow::on_exitApp_clicked()
{
    quitApp();
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

void MainWindow::on_font_changed(const QString& font)
{
    ((ContextMenu*)textsEditors->currentSubWindow()->widget())->setFontFamily(font);
}

void MainWindow::on_pointSize_changed(const QString& size)
{
    ((ContextMenu*)textsEditors->currentSubWindow()->widget())->setFontPointSize(size.toInt());
}

void MainWindow::on_bold_clicked()
{
    QFont font = ((ContextMenu*)textsEditors->activeSubWindow()->widget())->textCursor().charFormat().font();

    font.setBold(!font.bold());

    QTextCharFormat format;
    format.setFont(font);

    ((ContextMenu*)textsEditors->activeSubWindow()->widget())->textCursor().setCharFormat(format);
}

void MainWindow::on_italic_clicked()
{
    QFont font = ((ContextMenu*)textsEditors->activeSubWindow()->widget())->textCursor().charFormat().font();

    font.setItalic(!font.italic());

    QTextCharFormat format;
    format.setFont(font);

    ((ContextMenu*)textsEditors->activeSubWindow()->widget())->textCursor().setCharFormat(format);
}

void MainWindow::on_underLined_clicked()
{
    QFont font = ((ContextMenu*)textsEditors->activeSubWindow()->widget())->textCursor().charFormat().font();

    font.setUnderline(!font.underline());

    QTextCharFormat format;
    format.setFont(font);

    ((ContextMenu*)textsEditors->activeSubWindow()->widget())->textCursor().setCharFormat(format);
}

void MainWindow::on_alignmentLeft_clicked()
{
    ((ContextMenu*)textsEditors->activeSubWindow()->widget())->setAlignment(Qt::AlignmentFlag::AlignLeft);
}

void MainWindow::on_alignmentCenter_clicked()
{
    ((ContextMenu*)textsEditors->activeSubWindow()->widget())->setAlignment(Qt::AlignmentFlag::AlignCenter);
}

void MainWindow::on_alignmentRight_clicked()
{
    ((ContextMenu*)textsEditors->activeSubWindow()->widget())->setAlignment(Qt::AlignmentFlag::AlignRight);
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
            ((ContextMenu*)textsEditors->activeSubWindow()->widget())->setPlainText(stream.readAll());
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
        if(file.open(QFile::WriteOnly))
        {
            QTextStream stream(&file);
            stream << ((ContextMenu*)textsEditors->activeSubWindow()->widget())->toPlainText();
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
                                      keyQuit->key().toString(),
                                      keySendToPrint->key().toString(),
                                      keyNewTab->key().toString());
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
    if(!(hotkeys[4]->text().isEmpty()))
    {
        keyQuit->setKey(hotkeys[4]->text());
    }
    if(!(hotkeys[5]->text().isEmpty()))
    {
        keyQuit->setKey(hotkeys[5]->text());
    }
}

void MainWindow::on_classicTheme_clicked()
{
    setStyleApp(":/ClassicTheme.qss");
}

void MainWindow::on_darkTheme_clicked()
{
    setStyleApp(":/DarkTheme.qss");
}

void MainWindow::on_colorfulTheme_clicked()
{
    setStyleApp(":/ColorfulTheme.qss");
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
    saveTo->setText(tr("Save To"));
    newTab->setText(tr("New Tab"));
    sendToPrint->setText(tr("Send to print"));
    exitApp->setText(tr("Exit"));
    changeLangToRu->setText(tr("Change language to Ru"));
    changeLangToEn->setText(tr("Change language to En"));
    hotkeys->setText(tr("Change hotkeys"));
    theme->setTitle(tr("Theme"));
    classicTheme->setText(tr("Classic theme"));
    darkTheme->setText(tr("Dark Theme"));
    colorfulTheme->setText(tr("Colorful theme"));
    about->setText(tr("About"));
    bold->setText(tr("Bold"));
    italic->setText(tr("Italic"));
    underLined->setText(tr("Underline"));
    alignmentLeft->setText(tr("Left"));
    alignmentCenter->setText(tr("Center"));
    alignmentRight->setText(tr("Right"));

    QList<QMdiSubWindow* > subWindowList = textsEditors->subWindowList();
    for(int i = 0; i < subWindowList.length(); ++i)
    {
        QWidget* widget = subWindowList.at(i)->widget();
        ContextMenu* temp = (ContextMenu*) widget;
        temp->setTextCopyButton(tr("Copy"));
        temp->setTextPasteButton(tr("Paste"));
        temp->setTextSendToPrintButton(tr("SendToPrint"));
        temp->setTextCopyFormatButton(tr("Copy format"));
        temp->setTextPasteFormatButton(tr("Paste format"));
        temp->setTextPasteCurrentDate(tr("Paste current date"));
        temp->setTextPasteCurrentTime(tr("Paste current time"));
    }
}


void MainWindow::setStyleApp(const QString style)
{
    QFile qss(style);
    if(qss.open(QFile::ReadOnly | QFile::ExistingOnly))
    {
        qApp->setStyleSheet(qss.readAll());
        qss.close();
    }
}
