#include "mainwindow.h"
#include "addcontactdialog.h"
#include <QBoxLayout>
#include <QListWidget>
#include <QPushButton>
#include <QPointer>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget* central = new QWidget(this);
    setCentralWidget(central);

    QVBoxLayout* layout = new QVBoxLayout(central);

    m_listWidget = new QListWidget(this);
    layout->addWidget(m_listWidget);

    m_addButton = new QPushButton(QString("Add contact"), this);
    layout->addWidget(m_addButton);

    m_deleteButton = new QPushButton(QString("Delete contact"), this);
    m_deleteButton->setEnabled(false);
    layout->addWidget(m_deleteButton);

    m_listWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_addButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_deleteButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    connect(m_addButton, &QPushButton::clicked, this, &MainWindow::onAddContact);
    connect(m_deleteButton, &QPushButton::clicked, this, &MainWindow::onDeleteContact);
    connect(m_listWidget, &QListWidget::itemSelectionChanged, this, [this]() {
        m_deleteButton->setEnabled(!m_listWidget->selectedItems().isEmpty());
    });
}

MainWindow::~MainWindow() = default;

void MainWindow::onAddContact()
{
    QPointer<AddContactDialog> dlg(new AddContactDialog(this));

    if(dlg->run())
    {
        //only access dlg after check that is still exists
        if(dlg)
        {
            const QString name = dlg->name();
            const QString phone = dlg->phone();

            m_listWidget->addItem(name + " - " + phone);
        }
    }
    delete dlg;
}

void MainWindow::onDeleteContact()
{
    QListWidgetItem* item = m_listWidget->currentItem();
    if(item)
    {
        const auto answer = QMessageBox::question(
            this,
            "Confirm deletion",
            QString("Delete " + item->text() + " ?")
        );

        if (answer == QMessageBox::Yes)
            delete item;
    }
}
