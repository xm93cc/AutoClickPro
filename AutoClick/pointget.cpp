#include "pointget.h"


PointGet::PointGet()
{



}

void PointGet::run(){
    while (1)
    {
        Sleep(50);
        if (GetAsyncKeyState(VK_F2))
        {
            GetCursorPos(&point);
            //ui->local->setText(QString::number( point.x)+"*"+QString::number( clicks->curpos.y));
            qDebug()<<"当前记录坐标："+QString::number( point.x)+"*"+QString::number( point.y)<<endl;
            emit isDeno();
            break;
        }

    }
}
