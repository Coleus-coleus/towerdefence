#ifndef WEISODIER_H
#define WEISODIER_H

#include <QWidget>
#include <QPoint>
#include <QPainter>
#include <QPixmap>
#include "routepoint.h"
#include "differentscence.h"
#include "collisionwithcircle.h"
#include "closecombatdefend.h"
class DifferentScence;
class CloseCombatDefend;
class WeiSodier : public QObject
{
    Q_OBJECT
public:
    WeiSodier(RoutePoint StartCoordinate,DifferentScence *Scence,const QPixmap &Picture=QPixmap(":/WeiSodier/WeiCavalry.png"));//构造函数
    ~WeiSodier();//析构函数
    void draw(QPainter *painter) const;//载入魏军图片
    void march();//魏军行军
    void GetAttacked(CloseCombatDefend *closeCombatDefend);//魏军被攻击
    void Escape(CloseCombatDefend *closeCombatDefend);//魏军已逃离
    void GetRemoved();//移除魏军
    void GetDamaged(int Damage);//减少魏军血量
    void ChangeWeiSodier(int Order);//改变魏军类型
    QPoint Coordinate();//返回魏军的坐标
    void StrengthWeiSodier();//随着时间增强魏军
    int ReturnCurrentHP();//返回魏军现在的血量

signals:

public slots:
    void OrderActive();//命令魏军行动
private:
    int WeiSodier_MaxHP;//魏军最大血量
    int WeiSodier_CurrentHP;//魏军目前血量
    qreal WeiSodier_Speed;//魏军速度
    bool WeiSodier_Active;//魏军是否移动
    QPoint WeiSodier_Coordinate;//魏军坐标
    QPixmap WeiSodier_Picture;//魏军贴图
    RoutePoint *WeiSodier_DestinationRoutePoint;//魏军目标屯田点
    DifferentScence *SetScence;//载入场景
    QList<CloseCombatDefend *> AttackMeShuDefendList;//攻击我的蜀军信息管理
    QString WeiSodier_Kind;//记录魏军信息






};

#endif // WEISODIER_H
