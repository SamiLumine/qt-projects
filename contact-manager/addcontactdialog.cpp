#include "addcontactdialog.h"
#include "customvalidator.h"
#include <QBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QComboBox>
#include <QRegularExpressionValidator>
#include <QValidator>

AddContactDialog::AddContactDialog(QWidget* parent) : QDialog(parent)
{
    setWindowTitle("Add a contact");

    m_nameEdit = new QLineEdit(this);
    m_nameEdit->setValidator(new NameValidator(m_nameEdit));

    m_phoneEdit = new QLineEdit(this);
    // First mask in comboBox by default
    m_phoneEdit->setInputMask("00 00 00 00 00;_");
    m_phoneEdit->setValidator(new PhoneValidator(m_phoneEdit));

    m_box = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                                 Qt::Horizontal, this);
    m_box->button(QDialogButtonBox::Ok)->setEnabled(false);

    m_countryBox = new QComboBox(this);
    m_countryBox->addItem("France",       "00 00 00 00 00;_");
    m_countryBox->addItem("Belgium",     "000 00 00 00;_");
    m_countryBox->addItem("Switzerland",       "000 000 00 00;_");
    m_countryBox->addItem("United-States",   "000-000-0000;_");

    QFormLayout* formLayout = new QFormLayout();
    formLayout->addRow("Name :", m_nameEdit);
    formLayout->addRow("Country :", m_countryBox);
    formLayout->addRow("Phone :", m_phoneEdit);

    connect(m_box, &QDialogButtonBox::accepted, this, &AddContactDialog::accept);
    connect(m_box, &QDialogButtonBox::rejected, this, &AddContactDialog::reject);
    connect(m_countryBox, &QComboBox::currentIndexChanged, this, &AddContactDialog::updatePhoneMask);
    connect(m_nameEdit,  &QLineEdit::textChanged, this, &AddContactDialog::validateFields);
    connect(m_phoneEdit, &QLineEdit::textChanged, this, &AddContactDialog::validateFields);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(m_box);
}

QString AddContactDialog::name() const
{
    return m_nameEdit->text().trimmed();
}

QString AddContactDialog::phone() const
{
    return m_phoneEdit->text().trimmed();
}

bool AddContactDialog::run()
{
    return exec() == QDialog::Accepted;
}

void AddContactDialog::updatePhoneMask()
{
    const QString mask = m_countryBox->currentData().toString();
    m_phoneEdit->setInputMask(mask);
    m_phoneEdit->clear();
}

void AddContactDialog::validateFields()
{
    bool valid = m_nameEdit->hasAcceptableInput() && m_phoneEdit->hasAcceptableInput();
    m_box->button(QDialogButtonBox::Ok)->setEnabled(valid);
}
