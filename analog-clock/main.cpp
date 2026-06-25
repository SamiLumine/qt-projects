#include "clockwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ClockWindow w;
    w.resize(400, 400);
    w.show();
    return QApplication::exec();
}
