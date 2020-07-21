#ifndef CLICKTHREAD_H
#define CLICKTHREAD_H
#include<QThread>
#include<windows.h>

class Clickthread : public QThread
{
    Q_OBJECT
public:
    explicit Clickthread();

protected:
     void run();//任务处理线程


signals:
    void isDone();
    void isError();

public :
    POINT curpos;
    int seepTime = 100;
    int count = 0;
private slots:

};
#endif // CLICKTHREAD_H
