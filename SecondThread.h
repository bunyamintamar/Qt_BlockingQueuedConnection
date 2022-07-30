#ifndef SECONDTHREAD_H
#define SECONDTHREAD_H

#include <QThread>

class SecondThread
        : public QThread
{
    Q_OBJECT
public:
    SecondThread(QString name);
    void run() override;

signals:
    void sigSecondTh();

private:
    QString name;
};

#endif // SECONDTHREAD_H
