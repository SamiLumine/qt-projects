#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFile>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_fileSelector(new FileSelector(this))
{
    ui->setupUi(this);

    // Action connections
    connect(ui->action_Open, &QAction::triggered, this, &MainWindow::onOpen);
    connect(ui->action_Save, &QAction::triggered, this, &MainWindow::onSave);
    connect(ui->action_Quit, &QAction::triggered, this, &QApplication::quit);

    // FileSelector connections
    connect(m_fileSelector, &FileSelector::fileSelected, this, &MainWindow::loadFile);
    connect(m_fileSelector, &FileSelector::fileSaved, this, &MainWindow::saveFile);

    // Title-PlainText connection
    connect(ui->plainTextEdit, &QPlainTextEdit::textChanged, this, &MainWindow::editWindowTitle);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onOpen()
{
    m_fileSelector->openFile(this);
}

void MainWindow::loadFile(const QString& path)
{
    QFile file(path);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        ui->plainTextEdit->setPlainText(file.readAll());
        m_path = path;
        setWindowTitle(QString("Editor - ") + path + QString("[*]"));
        setWindowModified(false);
    }
}

void MainWindow::onSave()
{
    m_fileSelector->saveFile(this);
}

void MainWindow::saveFile(const QString& path)
{
    QFile file(path);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        file.write(ui->plainTextEdit->toPlainText().toUtf8());
        m_path = path;
        setWindowTitle(QString("Editor - ") + path + QString("[*]"));
        setWindowModified(false);
    }
}

void MainWindow::editWindowTitle()
{
    setWindowModified(true);
}