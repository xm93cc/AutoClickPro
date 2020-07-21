#ifndef EXECPOINTS_H
#define EXECPOINTS_H

#include <QObject>
#include<QThread>
#include<windows.h>
#include<list>
using namespace std;

class ExecPoints : public QThread
{
    Q_OBJECT
public:
    explicit ExecPoints();

protected:
    void run();
    bool isClickKey();

signals:
    void isDone();
    void isError();
public:
    unsigned long seepTime = 100;
    int count = 0;
    list<POINT> points;

public slots:
};

#endif // EXECPOINTS_H
