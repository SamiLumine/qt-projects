#include "fileselector.h"
#include <QFileDialog>

FileSelector::FileSelector(QObject *parent)
    : QObject{parent}
{}

QString FileSelector::openFile(QWidget* parent)
{
    QString path = QFileDialog::getOpenFileName(
        parent,
        tr("Open File"),
        QDir::homePath(),
        "Text files (*.txt);;All files (*)"
    );

    if(!path.isEmpty())
        emit fileSelected(path);

    return path;
}

QString FileSelector::saveFile(QWidget* parent, const QString& name)
{
    QString path = QFileDialog::getSaveFileName(
        parent,
        tr("Save"),
        !name.isEmpty() ? name : QDir::homePath(),
        "Text files (*.txt);;All files (*)"
    );

    if(!path.isEmpty())
        emit fileSaved(path);

    return path;
}