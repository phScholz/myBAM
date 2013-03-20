#include "bamwindow.h"
#include "bamcore.h"
#include <QApplication>
#include <QObject>

#define QUELLENDAT "./stuff/quellen.dat"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    bamWindow w;

    w.show();
    
    return a.exec();
}
