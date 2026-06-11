#ifndef FILESELECTOR_H
#define FILESELECTOR_H

#include <QObject>

class QFileDialog;

class FileSelector : public QObject
{
    Q_OBJECT
public:
    explicit FileSelector(QObject *parent = nullptr);

    QString openFile(QWidget* parent = nullptr);
    QString saveFile(QWidget* parent = nullptr, const QString& name = "");

signals:
    void fileSelected(const QString& chemin);
    void fileSaved(const QString& chemin);
};

#endif // FILESELECTOR_H
