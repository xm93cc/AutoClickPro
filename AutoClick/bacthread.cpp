#include "bacthread.h"

BacThread::BacThread()
{

}

void BacThread::run()
{
    while(1)
    {
        Sleep(100);
        if (GetAsyncKeyState(VK_F11))
        {
            emit isStart();
        }else if(GetAsyncKeyState(VK_F9)){
            emit isStartF9();
        }
    }

}
