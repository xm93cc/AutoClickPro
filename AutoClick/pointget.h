#ifndef POINTGET_H
#define POINTGET_H

#include <QObject>
#include<QThread>
#include<windows.h>
#include<QDebug>

class PointGet : public QThread
{
    Q_OBJECT
public:
    explicit PointGet();

protected:
        void run();

signals:
        void isDeno();

public:
     POINT point;

public slots:
};

#endif // POINTGET_H
