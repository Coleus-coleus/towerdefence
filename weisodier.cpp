#include "weisodier.h"
#include "routepoint.h"
#include "differentscence.h"
#include "collisionwithcircle.h"
#include <QPixmap>
#include <QObject>
#include <QPoint>
#include <QColor>
#include <QVector2D>
#include <QtMath>
WeiSodier::WeiSodier(RoutePoint StartCoordinate,DifferentScence *Scence,const QPixmap &Picture)
    :QObject(0),
      WeiSodier_MaxHP(100),//初始化魏军最大血量
      WeiSodier_CurrentHP(100),//初始化魏军当前血量
      WeiSodier_Speed(5.0),//初始化魏军速度
      WeiSodier_Active(false),//初始化魏军是否能动
      WeiSodier_Coordinate(StartCoordinate.Coordinate()),//初始化魏军当前坐标
      WeiSodier_Picture(Picture),//初始化魏军图片
      WeiSodier_DestinationRoutePoint(StartCoordinate.NextRoutePoint()),//初始化魏军目标屯田点
      SetScence(Scence)//初始化场景
{
}
void WeiSodier::draw(QPainter *painter)const
{
    if(!WeiSodier_Active)
        return;
    painter->save();
    QPoint HPPoint=WeiSodier_Coordinate+QPoint(-15,-15);
    painter->setPen(Qt::NoPen);
    painter->setPen(Qt::red);
    QRect MaxHPRect(HPPoint,QSize(10,2));
    painter->drawRect(MaxHPRect);
    painter->setBrush(Qt::blue);
    QRect CurrentHPRect(HPPoint,QSize((double)WeiSodier_CurrentHP/WeiSodier_MaxHP*10,2));
    painter->drawRect(CurrentHPRect);
    QPoint OffsetPoint(-26,-26);
    painter->translate(WeiSodier_Coordinate);
    painter->drawPixmap(OffsetPoint,WeiSodier_Picture);
    painter->restore();
}
void WeiSodier::march()
{
    if(!WeiSodier_Active)
        return;
    if(CollisionWithCircle(WeiSodier_Coordinate,1,WeiSodier_DestinationRoutePoint->Coordinate(),1))
    {
        //如果魏军抵达了屯田点
        if(WeiSodier_DestinationRoutePoint->NextRoutePoint())
        {
            WeiSodier_Coordinate=WeiSodier_DestinationRoutePoint->Coordinate();//魏军当前位置处于屯田点
            WeiSodier_DestinationRoutePoint=WeiSodier_DestinationRoutePoint->NextRoutePoint();//目的地为下一个屯田点
        }
        //如果魏军已经经历所有屯田点
        else
        {
            return;
        }
    }
    //如果魏军还在行军途中
    QPoint AimRoutePoint=WeiSodier_DestinationRoutePoint->Coordinate();
    //向量标准化
    double MarchingSpeed=WeiSodier_Speed;
    QVector2D Normalized(AimRoutePoint-WeiSodier_Coordinate);
    Normalized.normalize();
    WeiSodier_Coordinate=WeiSodier_Coordinate+Normalized.toPoint()*MarchingSpeed;


    
    
}
//命令魏军行动
void WeiSodier::OrderActive()
{
    WeiSodier_Active=true;
}
