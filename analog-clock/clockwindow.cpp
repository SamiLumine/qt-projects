#include "clockwindow.h"

#include <QPainter>
#include <QTime>
#include <QTimer>

#include "clockconst.h"

using namespace ClockConstants;

ClockWindow::ClockWindow(QWidget* parent) : QMainWindow(parent)
{
    setWindowTitle("Analog Clock");
    setMinimumSize(400, 400);
    m_timer = new QTimer(this);
    m_timer->setInterval(1000);
    connect(m_timer, &QTimer::timeout, this, QOverload<>::of(&ClockWindow::update));
    m_timer->start();
}

ClockWindow::~ClockWindow() = default;

int ClockWindow::radius() const
{
    return qMin(width(), height()) / 2 - MARGIN;
}

void ClockWindow::drawBackground(QPainter& painter)
{
    painter.fillRect(rect(), Qt::white);

    painter.setBrush(Qt::lightGray);
    painter.setPen(QPen(Qt::black, 3));
    painter.drawEllipse(rect().center(), radius(), radius());
}

void ClockWindow::drawTickMarks(QPainter& painter)
{
    int  rad = radius();
    int  width, height;
    bool isHour = false;

    painter.save();
    painter.setBrush(Qt::black);

    // setting (0,0) coordinates to the center
    painter.translate(rect().center());

    for (int i = 0; i < 60; ++i)
    {
        if (i % 5 == 0)
        {
            width  = HOUR_RECT_W;
            height = HOUR_RECT_H;
        }
        else
        {
            width  = SECOND_RECT_W;
            height = SECOND_RECT_H;
        }

        QRect tick(rad - (BORDER_SPACING + width), -height / 2, width, height);
        painter.drawRect(tick);

        // 6.0° = 360° / 60 graduations
        painter.rotate(6.0);
    }

    painter.restore();
}

void ClockWindow::drawHand(QPainter& painter, double angleDegree, QList<QPointF> list, Qt::GlobalColor color,
                           bool isSecond)
{
    painter.save();
    painter.rotate(angleDegree);
    painter.setBrush(color);
    painter.setPen(Qt::SolidLine);
    painter.drawConvexPolygon(list);
    if (isSecond)
    {
        int r = radius();
        painter.setBrush(Qt::red);
        QPointF p((r * SECOND_HAND_W) * 2 / 3, 0.);
        painter.drawEllipse(p, r * CIRCLE_HAND_RAD, r * CIRCLE_HAND_RAD);
    }
    painter.restore();
}

void ClockWindow::drawHands(QPainter& painter)
{
    int   r    = radius();
    QTime time = QTime::currentTime();

    double secondAngle = time.second() * 6.0;
    double minuteAngle = time.minute() * 6.0 + time.second() * 0.1;
    double hourAngle   = (time.hour() % 12) * 30.0 + time.minute() * 0.5;

    double taper = r * HAND_TAPER_RATIO;

    QList<QPointF> hourHand = {
        QPointF(-r * SIZE_SHIFT,  -r * HOUR_HAND_H / 2),
        QPointF(-r * SIZE_SHIFT,   r * HOUR_HAND_H / 2),
        QPointF( r * HOUR_HAND_W, -r * HOUR_HAND_H / 2 + taper),
        QPointF( r * HOUR_HAND_W,  r * HOUR_HAND_H / 2 - taper),
    };

    QList<QPointF> minuteHand = {
        QPointF(-r * SIZE_SHIFT,    -r * MINUTE_HAND_H / 2),
        QPointF(-r * SIZE_SHIFT,     r * MINUTE_HAND_H / 2),
        QPointF( r * MINUTE_HAND_W, -r * MINUTE_HAND_H / 2 + taper),
        QPointF( r * MINUTE_HAND_W,  r * MINUTE_HAND_H / 2 - taper),
    };

    QList<QPointF> secondHand = {
        QPointF(-r * SIZE_SHIFT,    -r * SECOND_HAND_H / 2),
        QPointF(-r * SIZE_SHIFT,     r * SECOND_HAND_H / 2),
        QPointF( r * SECOND_HAND_W, -r * SECOND_HAND_H / 2 + taper),
        QPointF( r * SECOND_HAND_W,  r * SECOND_HAND_H / 2 - taper),
    };

    painter.save();
    painter.translate(rect().center());
    drawHand(painter, hourAngle   - 90, hourHand,   Qt::black);
    drawHand(painter, minuteAngle - 90, minuteHand, Qt::black);
    drawHand(painter, secondAngle - 90, secondHand, Qt::red, true);
    painter.restore();
}

void ClockWindow::paintEvent(QPaintEvent* event)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    drawBackground(p);
    drawTickMarks(p);
    drawHands(p);
}
