#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "fileselector.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    void onOpen();
    void onSave();
    void loadFile(const QString& path);
    void saveFile(const QString& path);
    void editWindowTitle();

    Ui::MainWindow *ui;
    FileSelector* m_fileSelector;
    QString m_path;
};
#endif // MAINWINDOW_H
