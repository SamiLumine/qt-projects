#include "mainwindow.h"
#include <QList>
#include <QMap>
#include <QVariant>
#include <QListWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QBoxLayout>
#include <QFormLayout>
#include <QDateTime>
#include <QFile>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    auto *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    auto *mainLayout = new QVBoxLayout(centralWidget);
    centralWidget->setLayout(mainLayout);

    auto *formLayout = new QFormLayout();
    m_moodCombo = new QComboBox(this);
    m_moodCombo->addItem("Happy");
    m_moodCombo->addItem("Angry");
    m_moodCombo->addItem("Sad");
    m_moodCombo->addItem("Neutral");
    m_textEdit = new QTextEdit(this);
    formLayout->addRow(QString("Humor :"), m_moodCombo);
    formLayout->addRow(QString("Text :"), m_textEdit);
    mainLayout->addLayout(formLayout);

    auto *buttonLayout = new QHBoxLayout();
    m_btnAdd = new QPushButton("Add", this);
    m_btnSave = new QPushButton("Save", this);
    m_btnLoad = new QPushButton("Load", this);
    buttonLayout->addWidget(m_btnAdd);
    buttonLayout->addWidget(m_btnSave);
    buttonLayout->addWidget(m_btnLoad);
    mainLayout->addLayout(buttonLayout);

    auto *searchLayout = new QHBoxLayout();
    m_searchLabel = new QLabel("Search :", this);
    m_searchEdit = new QLineEdit(this);
    searchLayout->addWidget(m_searchLabel);
    searchLayout->addWidget(m_searchEdit);
    mainLayout->addLayout(searchLayout);

    m_listWidget = new QListWidget(this);
    m_statusLabel = new QLabel("Status", this);
    mainLayout->addWidget(m_listWidget);
    mainLayout->addWidget(m_statusLabel);

    connect(m_btnAdd, &QPushButton::clicked, this, &MainWindow::onAddEntry);
    connect(m_btnSave, &QPushButton::clicked, this, &MainWindow::onSave);
    connect(m_btnLoad, &QPushButton::clicked, this, &MainWindow::onLoad);
    connect(m_searchEdit, &QLineEdit::textChanged, this, &MainWindow::onSearch);
}

MainWindow::~MainWindow() = default;

void MainWindow::onAddEntry()
{
    const QString txt = m_textEdit->toPlainText();
    if(txt.isEmpty())
        return;

    Entry e;
    e["date"] = QDateTime::currentDateTime();
    e["mood"] = m_moodCombo->currentText();
    e["text"] = m_textEdit->toPlainText();
    m_entries.append(e);

    refreshList(m_entries);
    m_textEdit->clear();
}

void MainWindow::refreshList(const QList<Entry> &entries)
{
    m_listWidget->clear();
    for(auto i = entries.cbegin(); i != entries.cend(); ++i)
    {
        const Entry& entry = *i;
        const QString txt = QString("%1 | %2 | %3").arg(
            entry.value("date").toDateTime().toString("dd/MM/yyyy hh:mm"),
            entry.value("mood").toString(),
            entry.value("text").toString());
        m_listWidget->addItem(txt);
    }
}

void MainWindow::onSave()
{
    QFile file("log.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream txtFile(&file);
        for(auto i = m_entries.cbegin(); i != m_entries.cend(); ++i)
        {
            const Entry& entry = *i;
            const QString txt = QString("%1 | %2 | %3").arg(
                entry.value("date").toDateTime().toString("dd/MM/yyyy hh:mm"),
                entry.value("mood").toString(),
                entry.value("text").toString());
            txtFile << txt << '\n';
        }

        file.close();
        setStatus("Saved");
    }
    else
        setStatus("Failed to save", false);
}

void MainWindow::onLoad()
{
    QFile file("log.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        m_entries.clear();
        QTextStream txtFile(&file);
        while (!txtFile.atEnd())
        {
            const QString line = txtFile.readLine();

            const QStringList parts = line.split(" | ");

            //Ignoring possible invalid row
            if (parts.size() < 3)
            {
                continue;
            }

            Entry entry;
            entry.insert("date", QDateTime::fromString(parts.at(0), "dd/MM/yyyy hh:mm"));
            entry.insert("mood", parts.at(1));
            entry.insert("text", parts.mid(2).join(" | "));

            m_entries.append(entry);
        }
        refreshList(m_entries);
        setStatus("Loaded");
    }
    else
        setStatus("Failed to load", false);
}

void MainWindow::onSearch()
{
    if(m_searchEdit->text().isEmpty())
    {
        refreshList(m_entries);
        return;
    }
    QList<Entry> found_entries;
    QRegularExpression re(m_searchEdit->text());
    for(auto i = m_entries.cbegin(); i != m_entries.cend(); ++i)
    {
        if(re.match(i->value("text").toString()).hasMatch())
            found_entries.append(*i);
    }
    refreshList(found_entries);
}

void  MainWindow::setStatus(const QString &msg, bool ok)
{
    m_statusLabel->setText(msg);
    QString color = ok ? "color: green;" : "color: red;";
    m_statusLabel->setStyleSheet(color);
}