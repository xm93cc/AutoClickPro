#include "clickthread.h"
#include <QDebug>
#include<mainwindow.h>
#include<QMessageBox>


Clickthread::Clickthread()
{

}


//(2) run()重新实现
void Clickthread::run()
{



    for (int i = 0; i < count; i++)
    {
        if (GetAsyncKeyState(VK_F4))
        {
            // QMessageBox::warning(NULL,tr("警告"),tr("<p><span style='color: #FFFFFF;'>没有采取连点坐标不能开始</span></p>"),QMessageBox::Yes);
            emit isError();
            return;
        }

        Sleep(seepTime);
        SetCursorPos(curpos.x, curpos.y);
        mouse_event(MOUSEEVENTF_LEFTDOWN, curpos.x, curpos.y, 0, 0);
        mouse_event(MOUSEEVENTF_LEFTUP, curpos.x, curpos.y, 0, 0);
    }

     emit isDone();
        //QMessageBox::information(NULL,tr("进度信息"),tr("<p><span style='color: #FFFFFF;'>连点结束</span></p>"),QMessageBox::Yes);




}
