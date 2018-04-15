#include "witconsole.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WitConsole w;
    w.show();

    return a.exec();
}
