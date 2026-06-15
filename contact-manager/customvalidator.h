#ifndef CUSTOMVALIDATOR_H
#define CUSTOMVALIDATOR_H

#include <QValidator>
class QLineEdit;

class NameValidator : public QValidator
{
    Q_OBJECT
public:
    explicit NameValidator(QLineEdit* parent = nullptr);
    State validate (QString& input, int& pos) const override;
};

class PhoneValidator : public QValidator
{
    Q_OBJECT
public:
    explicit PhoneValidator(QLineEdit* parent = nullptr);
    State validate (QString& input, int& pos) const override;
};

#endif // CUSTOMVALIDATOR_H
