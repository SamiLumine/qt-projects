#ifndef STOPWATCHWINDOW_H
#define STOPWATCHWINDOW_H

#include <QMainWindow>

class QLabel;
class QListWidget;
class QPushButton;
class QTimer;
class QPlainTextEdit;

class StopwatchWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit StopwatchWindow(QWidget *parent = nullptr);
    ~StopwatchWindow() override;

private slots:
    void onTick();      // connected to QTimer::timeout
    void onToggle();    // connected to QTPushButton::clicked from m_startBtn
    void onReset();     // connected to QTPushButton::clicked from m_resetBtn
    void onLap();       // connected to QTPushButton::clicked from m_lapBtn

private:
    void updateDisplay();
    QString formatTime(int totalTenths) const;

    QLabel      *m_display;
    QPushButton *m_startBtn;
    QPushButton *m_resetBtn;
    QPushButton *m_lapBtn;
    QTimer      *m_timer;
    QPlainTextEdit *m_log;

    int  m_elapsed = 0;   // in tenths of a second
    int  m_lapCount = 0;
    bool m_running = false;
};
#endif // STOPWATCHWINDOW_H
