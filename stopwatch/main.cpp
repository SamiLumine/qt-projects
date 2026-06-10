#include "stopwatchwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    StopwatchWindow w;
    w.show();
    return QApplication::exec();
}
