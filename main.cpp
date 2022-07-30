#include <QCoreApplication>
#include "MainThread.h"
#include "SecondThread.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    MainThread   *mainTh   = new MainThread("mainTh");
    SecondThread *secondTh = new SecondThread("secondTh");

    QObject::connect(secondTh, SIGNAL(sigSecondTh()),
                     mainTh,   SLOT(slotMainTh()),
                     Qt::BlockingQueuedConnection);
//                     Qt::QueuedConnection);

    mainTh->start();
    secondTh->start();

    return a.exec();
}
