#include "SecondThread.h"
#include <QDebug>

#define LOG qDebug().noquote().nospace()


SecondThread::SecondThread(QString name)
{
    this->name = name;
}

void SecondThread::run()
{
   LOG << name << "is running";

   for (int i = 0; i < 5; i++)
   {
      LOG << name << "'s signal emitted";
      emit sigSecondTh();
      QThread::msleep(100);
   }

   LOG << name << " is finished <-------";
}
