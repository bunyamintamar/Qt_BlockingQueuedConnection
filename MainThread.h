#ifndef MAINTHREAD_H
#define MAINTHREAD_H

#include <QThread>

class MainThread
        : public QThread
{
    Q_OBJECT
public:
    MainThread(QString name);
    void run() override;

signals:

private:
    QString name;

public slots:
    void slotMainTh();
};

#endif // MAINTHREAD_H
