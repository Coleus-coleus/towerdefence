#ifndef SLEEP_H
#define SLEEP_H
//延时函数
#include <QApplication>
#include <QTime>
inline void sleep(unsigned int msec)
{
    //返回当前系统时间，用当前时间加上msec得到一个新的时刻
    QTime ReachTime=QTime::currentTime().addMSecs(msec);
    while(QTime::currentTime()<ReachTime)
    {
        QCoreApplication::processEvents(QEventLoop::AllEvents,100);
    }
}

#endif // SLEEP_H
