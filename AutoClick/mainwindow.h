#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <windows.h>
#include <windowsx.h>
#include <QMouseEvent>
#include <QWidget>
#include"clickthread.h"
#include<pointget.h>
#include"bacthread.h"
#include"execpoints.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
//处理信号
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void dealDone();
    void dealError();
    void dealPointOk();
    void dealStaet();
    void dealStaetF9();
    void dealDoneF9();



protected:
    bool nativeEvent(const QByteArray &eventType, void *message, long *result);
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);

private slots:

    void on_exit_clicked();

    void on_maxWindow_clicked();

    void on_openFileWindow_clicked();

    void on_savePoint_clicked();

    void on_execPoints_clicked();

    void on_recording_clicked();

    void on_execPoint_clicked();

private:
    Ui::MainWindow *ui;
    int boundaryWidth;
    QPoint clickPos;
    Clickthread *clicks;
    PointGet *point;
    BacThread *bac;
    int isOne=0;
    ExecPoints *execPoint;
};


#endif // MAINWINDOW_H
