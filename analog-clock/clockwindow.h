#ifndef CLOCKWINDOW_H
#define CLOCKWINDOW_H

#include <QMainWindow>
class QTimer;

class ClockWindow : public QMainWindow
{
    Q_OBJECT

  public:
    explicit ClockWindow(QWidget* parent = nullptr);
    ~ClockWindow() override;

  protected:
    void paintEvent(QPaintEvent* event) override;

  private:
    void drawBackground(QPainter& painter);
    void drawTickMarks(QPainter& painter);
    void drawHand(QPainter& painter, double angleDegree, QList<QPointF> list, Qt::GlobalColor color,
                  bool isSecond = false);

    void drawHands(QPainter& painter);
    int  radius() const;

    QTimer* m_timer;
};
#endif // CLOCKWINDOW_H
