#include "weisodier.h"
#include "routepoint.h"
#include "differentscence.h"
#include "collisionwithcircle.h"
#include <QPixmap>
#include <QObject>
#include <QPoint>
#include <QColor>
#include <QTimer>
#include <QVector2D>
#include <QtMath>
#include <QDebug>
#include <ctime>
#include <cstdlib>
WeiSodier::WeiSodier(RoutePoint StartCoordinate,DifferentScence *Scence,const QPixmap &Picture)
    :QObject(0),
      WeiSodier_MaxHP(0),//初始化魏军最大血量
      WeiSodier_CurrentHP(0),//初始化魏军当前血量
      WeiSodier_Speed(0),//初始化魏军速度
      WeiSodier_Active(false),//初始化魏军是否能动
      WeiSodier_Coordinate(StartCoordinate.Coordinate()),//初始化魏军当前坐标
      WeiSodier_Picture(Picture),//初始化魏军图片
      WeiSodier_DestinationRoutePoint(StartCoordinate.NextRoutePoint()),//初始化魏军目标屯田点
      SetScence(Scence),//初始化场景象
      WeiSodier_Kind(" ")//魏军种类
{
    QSize PictureSize(125,125);
    QPixmap SizePicture=WeiSodier_Picture.scaled(PictureSize,Qt::KeepAspectRatio);
    WeiSodier_Picture=SizePicture;
}
WeiSodier::~WeiSodier()
{
    AttackMeShuDefendList.clear();
    WeiSodier_DestinationRoutePoint=NULL;
    SetScence=NULL;
}

void WeiSodier::draw(QPainter *painter)const
{
    if(WeiSodier_Active==false)
        return;
    painter->save();
    if(WeiSodier_Kind=="WeiInfantry")
    {
        QPoint HPPoint=WeiSodier_Coordinate+QPoint(15,-15);
        painter->setPen(Qt::NoPen);
        painter->setPen(Qt::black);
        QRect MaxHPRect(HPPoint,QSize(120,10));
        painter->drawRect(MaxHPRect);
        painter->setBrush(Qt::blue);
        QRect CurrentHPRect(HPPoint,QSize((double)WeiSodier_CurrentHP/WeiSodier_MaxHP*120,10));
        painter->drawRect(CurrentHPRect);
        QPoint OffsetPoint(30,-10);//修正坐标
        painter->translate(WeiSodier_Coordinate);
        painter->drawPixmap(OffsetPoint,WeiSodier_Picture);
        painter->restore();
    }
    else if(WeiSodier_Kind=="WeiCavalry")
    {
        QPoint HPPoint=WeiSodier_Coordinate+QPoint(15,-15);
        painter->setPen(Qt::NoPen);
        painter->setPen(Qt::black);
        QRect MaxHPRect(HPPoint,QSize(120,10));
        painter->drawRect(MaxHPRect);
        painter->setBrush(Qt::blue);
        QRect CurrentHPRect(HPPoint,QSize((double)WeiSodier_CurrentHP/WeiSodier_MaxHP*120,10));
        painter->drawRect(CurrentHPRect);
        QPoint OffsetPoint(10,-10);//修正坐标
        painter->translate(WeiSodier_Coordinate);
        painter->drawPixmap(OffsetPoint,WeiSodier_Picture);
        painter->restore();
    }
    else if(WeiSodier_Kind=="ZhongHui")
    {
        QPoint HPPoint=WeiSodier_Coordinate+QPoint(20,-40);
        painter->setPen(Qt::NoPen);
        painter->setPen(Qt::black);
        QRect MaxHPRect(HPPoint,QSize(120,10));
        painter->drawRect(MaxHPRect);
        painter->setBrush(Qt::blue);
        QRect CurrentHPRect(HPPoint,QSize((double)WeiSodier_CurrentHP/WeiSodier_MaxHP*120,10));
        painter->drawRect(CurrentHPRect);
        QPoint OffsetPoint(25,-40);//修正坐标
        painter->translate(WeiSodier_Coordinate);
        painter->drawPixmap(OffsetPoint,WeiSodier_Picture);
        painter->restore();
    }
    else if(WeiSodier_Kind=="DengAi")
    {
        QPoint HPPoint=WeiSodier_Coordinate+QPoint(20,-40);
        painter->setPen(Qt::NoPen);
        painter->setPen(Qt::black);
        QRect MaxHPRect(HPPoint,QSize(120,10));
        painter->drawRect(MaxHPRect);
        painter->setBrush(Qt::blue);
        QRect CurrentHPRect(HPPoint,QSize((double)WeiSodier_CurrentHP/WeiSodier_MaxHP*120,10));
        painter->drawRect(CurrentHPRect);
        QPoint OffsetPoint(25,-40);//修正坐标
        painter->translate(WeiSodier_Coordinate);
        painter->drawPixmap(OffsetPoint,WeiSodier_Picture);
        painter->restore();
    }
}
void WeiSodier::march()
{
    if(WeiSodier_Active==false)
        return;
    if(CollisionWithCircle(WeiSodier_Coordinate,1,WeiSodier_DestinationRoutePoint->Coordinate(),1))
    {
        if(WeiSodier_DestinationRoutePoint->NextRoutePoint())
        {
            WeiSodier_Coordinate=WeiSodier_DestinationRoutePoint->Coordinate();//魏军当前位置处于屯田点
            WeiSodier_DestinationRoutePoint=WeiSodier_DestinationRoutePoint->NextRoutePoint();//目的地为下一个屯田点
        }
        else
        {
            SetScence->AttackChengdu(1);
            SetScence->destroyWeiSodier(this);
            return;
        }
    }
    QPoint AimRoutePoint=WeiSodier_DestinationRoutePoint->Coordinate();
    //向量标准化
    QVector2D Normalized(AimRoutePoint-WeiSodier_Coordinate);
    Normalized.normalize();
    double Distance1=fabs(WeiSodier_Coordinate.x()-WeiSodier_DestinationRoutePoint->Coordinate().x());
    double Distance2=fabs(WeiSodier_Coordinate.y()-WeiSodier_DestinationRoutePoint->Coordinate().y());
    if(Distance1>=WeiSodier_Speed||Distance2>=WeiSodier_Speed)
    {
        WeiSodier_Coordinate=WeiSodier_Coordinate+Normalized.toPoint()*WeiSodier_Speed;
    }
    else
    {
        WeiSodier_Coordinate=WeiSodier_DestinationRoutePoint->Coordinate();
    }
}
//命令魏军行动
void WeiSodier::OrderActive()
{
    WeiSodier_Active=true;
}
//返回魏军的坐标
QPoint WeiSodier::Coordinate()
{
    return WeiSodier_Coordinate;
}
//减少魏军血量
void WeiSodier::GetDamaged(int Damage)
{
    WeiSodier_CurrentHP=WeiSodier_CurrentHP-Damage;
    if(WeiSodier_CurrentHP<=0)
    {
        SetScence->AddMorale(60);
        GetRemoved();
    }
}
//魏军被攻击
void WeiSodier::GetAttacked(CloseCombatDefend *closeCombatDefend)
{
    if(closeCombatDefend->ReturnIdentity()!="ZhuGeLiang"&&closeCombatDefend->ReturnIdentity()!="LiuBei"&&closeCombatDefend->ReturnIdentity()!="LiuShen"&&closeCombatDefend->ReturnIdentity()!="ZhuGeJin")
    {
    AttackMeShuDefendList.push_back(closeCombatDefend);
    }
}
//魏军已逃离
void WeiSodier::Escape(CloseCombatDefend *closeCombatDefend)
{
    if(closeCombatDefend->ReturnIdentity()!="ZhuGeLiang"&&closeCombatDefend->ReturnIdentity()!="LiuBei"&&closeCombatDefend->ReturnIdentity()!="LiuShen"&&closeCombatDefend->ReturnIdentity()!="ZhuGeJin")
    {
    AttackMeShuDefendList.removeOne(closeCombatDefend);
    }
}

//移除魏军
void WeiSodier::GetRemoved()
{
    if(AttackMeShuDefendList.empty())
        return;
    foreach(CloseCombatDefend *ShuDefend,AttackMeShuDefendList)
        ShuDefend->WeiSodierKilled();
    //通知界面，该魏军已经阵亡并且移除该魏军
    SetScence->destroyWeiSodier(this);
    
}
//改变魏军类型
void WeiSodier::ChangeWeiSodier(int Order)
{
    if(Order==1)
    {
    srand(int(time(0)));
    int judge=rand()%2+1;
    if(judge==1)
    {
        WeiSodier_Picture=QPixmap(":/WeiSodier/WeiInfantry.png");
        QSize PictureSize(125,125);
        QPixmap SizePicture=WeiSodier_Picture.scaled(PictureSize,Qt::KeepAspectRatio);
        WeiSodier_Picture=SizePicture;
        WeiSodier_MaxHP=1500;
        WeiSodier_CurrentHP=1500;
        WeiSodier_Speed=1.0;
        WeiSodier_Kind="WeiInfantry";
    }
    else if(judge==2)
    {
        WeiSodier_Picture=QPixmap(":/WeiSodier/WeiCavalry.png");
        QSize PictureSize(125,125);
        QPixmap SizePicture=WeiSodier_Picture.scaled(PictureSize,Qt::KeepAspectRatio);
        WeiSodier_Picture=SizePicture;
        WeiSodier_MaxHP=800;
        WeiSodier_CurrentHP=800;
        WeiSodier_Speed=2.0;
        WeiSodier_Kind="WeiCavalry";
    }
    }
    else if(Order==2)
    {
        WeiSodier_Picture=QPixmap(":/WeiGeneral/ZhongHui.png");
        QSize PictureSize(150,150);
        QPixmap SizePicture=WeiSodier_Picture.scaled(PictureSize,Qt::KeepAspectRatio);
        WeiSodier_Picture=SizePicture;
        WeiSodier_MaxHP=10000;
        WeiSodier_CurrentHP=10000;
        WeiSodier_Speed=0.5;
        WeiSodier_Kind="ZhongHui";
    }
    else if(Order==3)
    {
        WeiSodier_Picture=QPixmap(":/WeiGeneral/ZhongHui.png");
        QSize PictureSize(150,150);
        QPixmap SizePicture=WeiSodier_Picture.scaled(PictureSize,Qt::KeepAspectRatio);
        WeiSodier_Picture=SizePicture;
        WeiSodier_MaxHP=10000;
        WeiSodier_CurrentHP=10000;
        WeiSodier_Speed=0.5;
        WeiSodier_Kind="DengAi";
    }

}
//随着时间增强魏军
void WeiSodier::StrengthWeiSodier()
{
        WeiSodier_Speed=WeiSodier_Speed*1.0005;//1.005的900次方是1.568，所以经过15分钟后，魏军的速度将变为原来的1.5倍左右
        WeiSodier_CurrentHP=WeiSodier_CurrentHP*1.0005;//魏军在被攻击过程中也在不断回血
        WeiSodier_MaxHP=WeiSodier_MaxHP*1.0005;//经过15分钟后，魏军的血量变为原来的1.5倍
}
