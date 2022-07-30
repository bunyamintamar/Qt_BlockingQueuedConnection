#include "MainThread.h"
#include <QDebug>

#define LOG qDebug().noquote().nospace()


MainThread::MainThread(QString name)
{
    this->name = name;
}

void MainThread::run()
{
    LOG << name << "is running";
}

void MainThread::slotMainTh()
{
    LOG << name << "'s slot started";
    QThread::msleep(200);
    LOG << name << "'s slot finished\n";
}
