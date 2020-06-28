#include "endscence.h"
#include <QIcon>
#include <QPushButton>
#include "mybutton.h"
#include "differentscence.h"
#include <QSound>
#include <QAbstractAnimation>
#include <QDebug>
EndScence::EndScence(QWidget *parent) : QWidget(parent)
{
    EndSound=NULL;
    Endflag=" ";
    setWindowIcon(QIcon(":/logo/logo.png"));
    this->setFixedSize(1600,1000);
    setWindowTitle("蜀汉悲歌");
}
void EndScence::paintEvent(QPaintEvent *)
{
    //加载结束背景
    QPainter painter(this);
    QPixmap pix;
    if(Endflag=="WarLose")
    {
        pix.load(":/background/WarLose.png");
        painter.drawPixmap(0,0,this->width(),this->height(),pix);
        QString text="战争失败,汉室倾颓!";
        QFont Font("宋体",50,QFont::Bold,true);
        painter.setFont(Font);
        painter.setPen(Qt::red);
        painter.drawText(rect(), Qt::AlignCenter, text);
    }
    else if(Endflag=="WarWin")
    {
        pix.load(":/background/WarWin.png");
        painter.drawPixmap(0,0,this->width(),this->height(),pix);
        QString text="战争胜利,汉室中兴!";
        QFont Font("宋体",50,QFont::Bold,true);
        painter.setFont(Font);
        painter.setPen(Qt::black);
        painter.drawText(rect(), Qt::AlignCenter, text);

    }
}
void EndScence::EndFlag(QString string)
{
    Endflag=string;
}
QSound* EndScence::ReturnEndMusic()
{
    return EndSound;
}
void EndScence::ChangSound()
{
    if(Endflag=="WarLose")
    {
        EndSound=new QSound(":/Music/WarLose.wav");
        EndSound->setLoops(1000000);
    }
    else if(Endflag=="WarWin")
    {
        EndSound=new QSound(":/Music/WarWin.wav");
        EndSound->setLoops(1000000);
    }
}
