#ifndef WEISODIER_H
#define WEISODIER_H

#include <QWidget>
#include <QPoint>
#include <QPainter>
#include <QPixmap>
#include "routepoint.h"
#include "differentscence.h"
#include "collisionwithcircle.h"
class DifferentScence;
class WeiSodier : public QObject
{
    Q_OBJECT
public:
    WeiSodier(RoutePoint StartCoordinate,DifferentScence *Scence,const QPixmap &Picture=QPixmap(":/button/startbutton.png"));//构造函数
    void draw(QPainter *painter) const;//载入魏军图片
    void march();//魏军行军
    void OrderActive();//命令魏军行动

signals:

public slots:
private:
    int WeiSodier_MaxHP;//魏军最大血量
    int WeiSodier_CurrentHP;//魏军目前血量
    double WeiSodier_Speed;//魏军速度
    bool WeiSodier_Active;//魏军是否移动
    QPoint WeiSodier_Coordinate;//魏军坐标
    QPixmap WeiSodier_Picture;//魏军贴图
    RoutePoint *WeiSodier_DestinationRoutePoint;//魏军目标屯田点
    DifferentScence *SetScence;//载入场景






};

#endif // WEISODIER_H
