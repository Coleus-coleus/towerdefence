#include "efficacy.h"
#include "weisodier.h"
#include "differentscence.h"
#include <QPainter>
#include <QPropertyAnimation>
#include <QPoint>
#include <QDebug>
//构造函数
Efficacy::Efficacy(QPoint StartPoint,
                   QPoint TargetPoint,
                   int Hurt,
                   WeiSodier *TargetWeiSodier,
                   DifferentScence *Scence,
                   const QPixmap &Picture)
    :My_StartPoint(StartPoint),
     My_TargetPoint(TargetPoint),
     My_Picture(Picture),
     My_CurrentPoint(StartPoint),
     My_TargetWeiSodier(TargetWeiSodier),
     My_Scence(Scence),
     My_Hurt(Hurt),
     My_kind("Cut"),
     My_Sound(NULL)
{
    My_Sound=new QSound(":/Efficacy/Cut.wav",this);
    QSize PictureSize(100,100);
    QPixmap SizePicture=My_Picture.scaled(PictureSize,Qt::KeepAspectRatio);
    My_Picture=SizePicture;
}
//绘画函数
void Efficacy::draw(QPainter *painter)const
{
    painter->drawPixmap(My_CurrentPoint,My_Picture);
}
//特效的移动
void Efficacy::Move()
{
    static const int Duration=100;
    QPropertyAnimation *Animation=new QPropertyAnimation(this,"My_CurrentPoint");
    Animation->setDuration(Duration);
    Animation->setStartValue(My_StartPoint);
    Animation->setEndValue(My_TargetPoint);
    connect(Animation,SIGNAL(finished()),this,SLOT(CutTarget()));
    Animation->start();
}
//击中魏军
void Efficacy::CutTarget()
{
    if(My_Scence->WeiSodier_list().indexOf(My_TargetWeiSodier)!=-1)
        My_TargetWeiSodier->GetDamaged(My_Hurt);
    My_Scence->destroyEfficacy(this);
}
//设置特效现在坐标
void Efficacy::SetCurrentPoint(QPoint Point)
{
    My_CurrentPoint=Point;
}
//返回特效现在的坐标
QPoint Efficacy::CurrentPoint()const
{
    return My_CurrentPoint;
}
//改变图片，黄忠专用
void Efficacy::ChangePicture()
{
   My_Sound=new QSound(":/Efficacy/Shoot.wav",this);
   My_Picture=QPixmap(":/Efficacy/Jian.png");
   QSize PictureSize(100,100);
   QPixmap SizePicture=My_Picture.scaled(PictureSize,Qt::KeepAspectRatio);
   My_Picture=SizePicture;
   My_kind="Shoot";
}
//返回特效音乐
QSound* Efficacy::ReturnSound()
{
    return My_Sound;
}
