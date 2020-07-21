#ifndef BACTHREAD_H
#define BACTHREAD_H

#include <QObject>
#include<QThread>
#include<clickthread.h>

class BacThread : public QThread
{
    Q_OBJECT
public:
    explicit BacThread();
protected:
    void run();

signals:
    void isStart();
    void isStartF9();

public slots:
};

#endif // BACTHREAD_H
