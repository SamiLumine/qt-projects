#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class QListWidget;
class QPushButton;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void onAddContact();
    void onDeleteContact();

private:
    QListWidget* m_listWidget;
    QPushButton* m_addButton;
    QPushButton* m_deleteButton;

};
#endif // MAINWINDOW_H
