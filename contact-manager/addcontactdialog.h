#ifndef ADDCONTACTDIALOG_H
#define ADDCONTACTDIALOG_H

#include <QDialog>
class QLineEdit;
class QDialogButtonBox;
class QComboBox;

class AddContactDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddContactDialog(QWidget *parent = nullptr);

    QString name() const;
    QString phone() const;
    bool run();

private slots:
    void updatePhoneMask();
    void validateFields();

private:
    QLineEdit* m_nameEdit;
    QLineEdit* m_phoneEdit;
    QDialogButtonBox* m_box;
    QComboBox* m_countryBox;
};

#endif // ADDCONTACTDIALOG_H
