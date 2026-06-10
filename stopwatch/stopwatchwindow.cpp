#include "stopwatchwindow.h"

#include <QWidget>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>
#include <QTimer>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPlainTextEdit>

StopwatchWindow::StopwatchWindow(QWidget *parent)
    : QMainWindow(parent)
{
    m_display = new QLabel(QString("00:00:00.0"), this);
    m_startBtn = new QPushButton(QString("Start"), this);
    m_resetBtn = new QPushButton(QString("Reset"), this);
    m_lapBtn = new QPushButton(QString("Lap"), this);
    m_timer = new QTimer(this);
    m_timer->setInterval(100); // 100ms -> 0.1s
    m_log = new QPlainTextEdit(this);
    m_log->setReadOnly(true);

    // Connects
    connect(m_timer, &QTimer::timeout, this, &StopwatchWindow::onTick);
    connect(m_startBtn, &QPushButton::clicked, this, &StopwatchWindow::onToggle);
    connect(m_resetBtn, &QPushButton::clicked, this, &StopwatchWindow::onReset);
    connect(m_lapBtn, &QPushButton::clicked, this, &StopwatchWindow::onLap);

    // Layouts
    auto *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    auto *mainLayout = new QVBoxLayout(centralWidget);
    auto *btnLayout  = new QHBoxLayout();

    btnLayout->addWidget(m_startBtn);
    btnLayout->addWidget(m_resetBtn);
    btnLayout->addWidget(m_lapBtn);

    m_display->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(m_display);
    mainLayout->addLayout(btnLayout);
    mainLayout->addWidget(m_log);
}

StopwatchWindow::~StopwatchWindow() = default;


QString StopwatchWindow::formatTime(int totalTenths) const
{
    int tenths  = totalTenths % 10;
    int seconds = (totalTenths / 10) % 60;
    int minutes = (totalTenths / 600) % 60;
    int hours   = totalTenths / 36000;
    return QString::asprintf("%02d:%02d:%02d.%d", hours, minutes, seconds, tenths);
}

void StopwatchWindow::onTick()
{
    m_elapsed++;
    updateDisplay();
}

void StopwatchWindow::updateDisplay()
{
    m_display->setText(formatTime(m_elapsed));
}

void StopwatchWindow::onToggle()
{
    m_running = !m_running;
    if(m_running == true)
    {
        m_timer->start();
        m_startBtn->setText(QString("Stop"));
    }
    else
    {
        m_timer->stop();
        m_startBtn->setText(QString("Start"));
    }
}

void StopwatchWindow::onReset()
{
    m_running = false;
    m_elapsed = 0;
    m_lapCount = 0;
    m_timer->stop();
    m_display->setText(QString("00:00:00.0"));
    m_log->clear();
}

void StopwatchWindow::onLap()
{
    m_lapCount ++;
    m_log->appendPlainText(QString::asprintf("Lap %d - %s", m_lapCount, formatTime(m_elapsed).toStdString().c_str()));
}
