#ifndef FRAMELESSWIDGET_H
#define FRAMELESSWIDGET_H

#include <QWidget>
#include <windows.h>        //注意头文件
#include <windowsx.h>
#include <QMouseEvent>
class FramelessWidget : public QWidget
{
    Q_OBJECT

public:
    FramelessWidget(QWidget *parent = 0);
    ~FramelessWidget();
protected:
    bool nativeEvent(const QByteArray &eventType, void *message, long *result);
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
private:
    int boundaryWidth;
    QPoint clickPos;
};

#endif // FRAMELESSWIDGET_H
