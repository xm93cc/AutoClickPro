#include "execpoints.h"

ExecPoints::ExecPoints()
{

}

/**
 * @brief ExecPoints::run 线程执行宏定义指令
 */
void ExecPoints::run(){
   // sleep(seepTime);
    for (int i = 0; i < count; i++)
    {
        for (typename list<POINT>::iterator it = points.begin(); it != points.end(); ++it)
        {
            if(isClickKey())
                return;
            Sleep(seepTime);
            SetCursorPos(it->x, it->y);
            mouse_event(MOUSEEVENTF_LEFTDOWN, it->x, it->y, 0, 0);
            mouse_event(MOUSEEVENTF_LEFTUP, it->x, it->y, 0, 0);
        }
        if (isClickKey())
            return;
    }
    emit isDone();


}

/**
 * @brief ExecPoints::isClickF9 监听是否按下F9
 */
bool ExecPoints::isClickKey()
{
    if (GetAsyncKeyState(VK_F10))
    {
        // QMessageBox::warning(NULL,tr("警告"),tr("<p><span style='color: #FFFFFF;'>没有采取连点坐标不能开始</span></p>"),QMessageBox::Yes);
        emit isError();
        return true;
    }
    return false;
}
