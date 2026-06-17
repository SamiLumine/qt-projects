#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class QListWidget;
class QLineEdit;
class QTextEdit;
class QComboBox;
class QLabel;
class QPushButton;

template <typename T>
class QList;

template <typename Key, typename T>
class QMap;

class QVariant;


using Entry = QMap<QString, QVariant>;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onAddEntry();
    void onSave();
    void onLoad();
    void onSearch();

private:
    // Widgets
    QTextEdit   *m_textEdit;
    QComboBox   *m_moodCombo;
    QLineEdit   *m_searchEdit;
    QListWidget *m_listWidget;
    QLabel      *m_searchLabel;
    QLabel      *m_statusLabel;
    QPushButton *m_btnAdd;
    QPushButton *m_btnSave;
    QPushButton *m_btnLoad;

    // Données
    QList<Entry> m_entries;

    // Helpers
    void refreshList(const QList<Entry> &entries);
    void setStatus(const QString &msg, bool ok = true);
};

#endif