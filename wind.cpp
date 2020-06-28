#include "wind.h"
#include "weisodier.h"
#include "differentscence.h"
#include <QPainter>
#include <QPropertyAnimation>
#include <QPoint>
#include <QDebug>
Wind::Wind(QPoint StartPoint,
           QPoint TargetPoint,
           int Hurt,
           WeiSodier *TargetWeiSodier,
           DifferentScence *Scence,
           const QPixmap &Picture)
    : My_StartPoint(StartPoint),
      My_TargetPoint(TargetPoint),
      My_CurrentPoint(StartPoint),
      My_Picture(Picture),
      My_TargetWeiSodier(TargetWeiSodier),
      My_Scence(Scence),
      My_Hurt(Hurt),
      My_Sound(NULL)
{
    QSize PictureSize(125,125);
    QPixmap SizePicture=My_Picture.scaled(PictureSize,Qt::KeepAspectRatio);
    My_Picture=SizePicture;
}
//绘画函数
void Wind::draw(QPainter *painter)const
{
    painter->drawPixmap(My_CurrentPoint,My_Picture);
}
//击中魏军
void Wind::HitTarget()
{
    if(My_Scence->WeiSodier_list().indexOf(My_TargetWeiSodier)!=-1)
        My_TargetWeiSodier->GetDamaged(My_Hurt);
    My_Scence->destroyWind(this);
}
//设置风现在坐标
void Wind::SetCurrentPoint(QPoint Point)
{
    My_CurrentPoint=Point;
}
//返回风现在的坐标
QPoint Wind::CurrentPoint()const
{
    return My_CurrentPoint;
}
//风的出现
void Wind::Appear()
{
    static const int Duration=100;
    QPropertyAnimation *Animation=new QPropertyAnimation(this,"My_CurrentPoint");
    Animation->setDuration(Duration);
    Animation->setStartValue(My_StartPoint);
    Animation->setEndValue(My_TargetPoint);
    connect(Animation,SIGNAL(finished()),this,SLOT(HitTarget()));
    Animation->start();
}
//改变图片大小
void Wind::ChangePicture()
{
    QSize PictureSize(175,175);
    QPixmap SizePicture=My_Picture.scaled(PictureSize,Qt::KeepAspectRatio);
    My_Picture=SizePicture;
}
