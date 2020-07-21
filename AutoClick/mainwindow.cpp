#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>
#include<QMessageBox>
#include"clickthread.h"
#include<QFileDialog>
#include<QFile>
#define GET_ARRAY_LEN(array,len) {len = (sizeof(array) / sizeof(array[0]));}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    boundaryWidth=4;                                    //设置触发resize的宽度
    this->setMinimumSize(317,546);                        //设置最小尺寸
    this->setMaximumSize(317,546);

    ui->local->setReadOnly(true);
    this->setWindowIcon(QIcon(":/res/aci.ico"));

    bac= new BacThread;
    bac->start();                   //启动线程监听F11触发钩子发送信号
    clicks= new Clickthread;
    point =new PointGet;

    execPoint =new ExecPoints;

    //绑定信号和槽
    connect(clicks,&Clickthread::isDone,this,&MainWindow::dealDone);
    connect(clicks,&Clickthread::isError,this,&MainWindow::dealError);
    connect(point,&PointGet::isDeno,this,&MainWindow::dealPointOk);
    connect(bac,&BacThread::isStart,this,&MainWindow::dealStaet);
    connect(bac,&BacThread::isStartF9,this,&MainWindow::dealStaetF9);
    connect(execPoint,&ExecPoints::isDone,this,&MainWindow::dealDoneF9);
    connect(execPoint,&ExecPoints::isError,this,&MainWindow::dealError);
    clicks->curpos.x=0;
    clicks->curpos.y=0;


}

MainWindow::~MainWindow()
{
    delete ui;
}


bool MainWindow::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    MSG* msg = (MSG*)message;
    switch(msg->message)
    {
    case WM_NCHITTEST:
        int xPos = GET_X_LPARAM(msg->lParam) - this->frameGeometry().x();
        int yPos = GET_Y_LPARAM(msg->lParam) - this->frameGeometry().y();
        if(xPos < boundaryWidth && yPos<boundaryWidth)                    //左上角
            *result = HTTOPLEFT;
        else if(xPos>=width()-boundaryWidth&&yPos<boundaryWidth)          //右上角
            *result = HTTOPRIGHT;
        else if(xPos<boundaryWidth&&yPos>=height()-boundaryWidth)         //左下角
            *result = HTBOTTOMLEFT;
        else if(xPos>=width()-boundaryWidth&&yPos>=height()-boundaryWidth)//右下角
            *result = HTBOTTOMRIGHT;
        else if(xPos < boundaryWidth)                                     //左边
            *result =  HTLEFT;
        else if(xPos>=width()-boundaryWidth)                              //右边
            *result = HTRIGHT;
        else if(yPos<boundaryWidth)                                       //上边
            *result = HTTOP;
        else if(yPos>=height()-boundaryWidth)                             //下边
            *result = HTBOTTOM;
        else              //其他部分不做处理，返回false，留给其他事件处理器处理
            return false;
        return true;
    }
    return false;         //此处返回false，留给其他事件处理器处理
}


void MainWindow::mousePressEvent(QMouseEvent *e)
{
    if(e->button()==Qt::LeftButton)
        clickPos=e->pos();
}
void MainWindow::mouseMoveEvent(QMouseEvent *e)
{
    if(e->buttons()&Qt::LeftButton)
        move(e->pos()+pos()-clickPos);
}

void MainWindow::dealDone()
{
    QMessageBox::information(this,tr("进度信息"),tr("<p><span style='color: #FFFFFF;'>连点完成</span></p>"),QMessageBox::Yes);
}


void MainWindow::dealError()
{
    QMessageBox::warning(this,tr("警告"),tr("<p><span style='color: #FFFFFF;'>连点终止</span></p>"),QMessageBox::Yes);
}

void MainWindow::on_execPoint_clicked()
{

    QString str=ui->count->text();
    QString time=ui->time->text();
    if(str.isNull()||str.isEmpty())
        clicks->count=150;
    else
        clicks->count=str.toInt();
    if(time.isNull()||time.isEmpty())
        clicks->seepTime=50;
    else
        clicks->seepTime=time.toInt();

    if( clicks->curpos.x==0|| clicks->curpos.y==0)
    {
        // QMessageBox::information(this,"进度信息","连点结束",QMessageBox::Ok,QMessageBox::Cancel);
        QMessageBox::warning(this,tr("warning"),tr("<p><span style='color: #FFFFFF;'>没有采取连点坐标不能开始</span></p>"),QMessageBox::Yes);
        return;
    }




    clicks->start();
    //   qDebug("\n连点结束....\n\n\n");
    //   QMessageBox::information(this,tr("进度信息"),tr("<p><span style='color: #FFFFFF;'>连点结束</span></p>"),QMessageBox::Yes);



}

void MainWindow::on_exit_clicked(){


    exit(1);


}

void MainWindow::on_recording_clicked()
{
    ui->recording->setText("将鼠标移动到连点位置，按F2记录");
    point->start();
}

void MainWindow::dealPointOk()
{

    ui->local->setText(QString::number( point->point.x)+"*"+QString::number( point->point.y));
    clicks->curpos.x=point->point.x;
    clicks->curpos.y=point->point.y;
    ui->recording->setText("开始记录");
}


void MainWindow::dealStaet()
{

    on_execPoint_clicked();
}

void MainWindow::on_maxWindow_clicked()
{
    if(isOne==0)
    {
        ui->maxWindow->setText("关闭宏坐标集");
        this->setMinimumSize(622,546);
        this->setMaximumSize(622,546);
        ui->exit->setGeometry(581,-1,41,41);
        ui->title->setGeometry(2,3,618,31);
        isOne++;
    }else {
        ui->maxWindow->setText("使用坐标集");
        this->setMinimumSize(317,546);                        //设置最小尺寸
        this->setMaximumSize(317,546);
        ui->exit->setGeometry(278,-1,41,41);
        ui->title->setGeometry(2,3,311,31);
        isOne--;
    }

}

void MainWindow::on_openFileWindow_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("选择文件"),
                                                    "C:",
                                                    tr("坐标集文件(*ini *point);;"));
    QFile file(fileName);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray t = file.readAll();
    ui->pointEdit->setPlainText(QString(t));
    file.close();


}

void MainWindow::on_savePoint_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("保存当前坐标"),
                                                    "",
                                                    tr("日志文件(*.point)"));
    QFile file(fileName);

    if (!file.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        QMessageBox::information(this, "提示", tr("取消保存"),
                                 QMessageBox::Yes, QMessageBox::Yes);
    }
    else
    {
        QTextStream stream(&file);
        stream << ui->pointEdit->toPlainText();
        stream.flush();
        file.close();
    }

}

void MainWindow::on_execPoints_clicked()
{

    try {
        int countP=0;
        QString proints= ui->pointEdit->toPlainText();
        QStringList pointsList=proints.split("\n");
        QList<QString>::Iterator it = pointsList.begin(),itend = pointsList.end();
        int i = 0,j=0;
        for (;it != itend; it++,j++){
            if((*it).length()<3)
                break;
        }
        POINT p[j];
        it = pointsList.begin();itend = pointsList.end();
        for (;it != itend; it++,i++){
            if(i==j)
                break;
            QStringList points=(*it).split("*");
            POINT temp;
            temp.x=points.begin()->toInt();
            temp.y=points.last().toInt();
            //execPoint->points.insert(temp,1);
            p[i]=temp;
//            qDebug()<<(*it)<<endl;
        }
        int len=0;
        GET_ARRAY_LEN(p,len);
        if(len>0)
        {
            for(int i=0;i<len;i++)
            {
                if(p[i].x==0&&p[i].y==0)
                {
//                QMessageBox::warning(this,"警告","上下文中有不确定内容，请按照要求定义!",QMessageBox::Yes);
//                return;
                    throw 100;
                }

//                 qDebug()<<p[i].x<<"\t"<<p[i].y<<endl;
            }
            execPoint->points=list<POINT>(p,p+len);
        }

       execPoint->count= ui->pointCount->text().toInt();
       execPoint->seepTime=ui->poinTime->text().toLong();

       execPoint->start();


    } catch (...) {
        QMessageBox::warning(this,"警告","上下文中有不确定内容，请按照要求定义!",QMessageBox::Yes);
    }

}

void MainWindow::dealStaetF9()
{
    execPoint->start();
}

void MainWindow::dealDoneF9()
{
    dealDone();
}

