#include "customvalidator.h"
#include <QLineEdit>

NameValidator::NameValidator(QLineEdit* parent) : QValidator(parent) {}

NameValidator::State NameValidator::validate(QString& input, int& pos) const
{
    Q_UNUSED(pos)
    for (const QChar &c : input) {
        if (!c.isLetter() && c != ' ' && c != '-' && c != '\'')
            return Invalid;
    }
    return input.trimmed().isEmpty() ? Intermediate : Acceptable;
}

PhoneValidator::PhoneValidator(QLineEdit* parent) : QValidator(parent) {}

PhoneValidator::State PhoneValidator::validate(QString& input, int& pos) const
{
    Q_UNUSED(pos)
    for (const QChar &c : input) {
        if (!c.isDigit() && c != ' ' && c != '-' && c != '_')
            return Invalid;
    }

    if (input.contains('_'))
        return Intermediate;

    return input.trimmed().isEmpty() ? Intermediate : Acceptable;
}