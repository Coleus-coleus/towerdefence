#ifndef DIFFERENTSCENCE_H
#define DIFFERENTSCENCE_H

#include <QWidget>
#include "closecombatdefend.h"
#include "tower.h"
#include "routepoint.h"
#include "weisodier.h"
#include <QWidget>
#include <QList>
class CloseCombatDefend;
class WeiSodier;

class DifferentScence : public QWidget
{
    Q_OBJECT
public:
    explicit DifferentScence(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);//重写绘画事件
    void mousePressEvent(QMouseEvent *event);//重写鼠标点击事件
    bool WhetherCanBuy() const;//确定是否能买塔防
    void ChangeScence(QString flag);//改变关卡场景
    void AttackChengdu(int damage=2);//进攻成都
    void destroyWeiSodier(WeiSodier *weiSodier);//移除魏军
private:
    QList<Tower> AzureDragonScenceTower_List;//管理青龙关塔信息;
    QList<Tower> BlackTortoiseScenceTower_List;//管理玄武关塔信息;
    QList<Tower> VermilionBirdScenceTower_List;//管理朱雀关塔信息;
    QList<Tower> WhiteTigerScenceTower_List;//管理白虎关塔信息;
    QList<RoutePoint> AzureDragonScenceRoutePoint_List;//管理青龙关屯田点信息
    QList<RoutePoint> BlackTortoiseScenceRoutePoint_List;//管理玄武关屯田点信息
    QList<RoutePoint> VermilionBirdScenceRoutePoint_List;//管理朱雀关屯田点信息
    QList<RoutePoint> WhiteTigerScenceRoutePoint_List;//管理白虎关屯田点信息
    QList<CloseCombatDefend *> CloseCombatDefend_List;//管理近战塔防信息
    QList<WeiSodier *> WeiSodier_List;//管理魏军信息
    void LoadTowerCoordinate();//载入塔信息
    void LoadRoutePoint();//载入屯田点信息
    bool LoadBatch();//载入批数信息
    QString Flag=NULL;//选关信号
    int WeiSodier_Batch;//魏军批数

signals:

public slots:
private slots:
    void RenewMap();//更新地图模拟帧数
};

#endif // DIFFERENTSCENCE_H
