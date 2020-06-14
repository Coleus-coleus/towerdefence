#ifndef DIFFERENTSCENCE_H
#define DIFFERENTSCENCE_H

#include <QWidget>
#include "closecombatdefend.h"
#include "tower.h"
#include "routepoint.h"
#include "weisodier.h"
#include "efficacy.h"
#include <QWidget>
#include <QList>
#include <QTimer>
#include <QSound>
#include <QPushButton>
class CloseCombatDefend;
class WeiSodier;
class Efficacy;

class DifferentScence : public QWidget
{
    Q_OBJECT
public:
    explicit DifferentScence(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);//重写绘画事件
    bool WhetherWillRespond() const;//蜀国的先烈是否会响应召唤
    void AddMorale(int Morale);//击杀魏军后，增加蜀军士气，可以召唤更多的蜀国英烈
    void ChangeScence(QString flag);//改变关卡场景
    void AttackChengdu(int damage=2);//进攻成都
    void destroyWeiSodier(WeiSodier *weiSodier);//移除魏军
    void AddEfficacy(Efficacy *efficacy);//增添特效
    void destroyEfficacy(Efficacy *efficacy);//移除特效
    void ForceWarLose();//转化WarLose的值
    void DrawBatch(QPainter *Painter);//画出魏军批数
	void DrawChengDuCitizenry(QPainter *Painter);//画出成都民心
	void DrawShuMorale(QPainter *Painter);//画出蜀军士气
    void AddBatch();//增加总批数
    void AddCurrentBatch();//增加当前批数
    void DecreaseBatch();//减少总批数
    void DecreaseCurrentBatch();//减少当前批数
    void Endless();//变为无尽模式
    QList<WeiSodier *> WeiSodier_list();//返回魏军管理信息
    QSound* ReturnScenceSound();//返回背景音乐
    QTimer* ReturnWeiTimer();//返回增强魏军能力的计时器
    QTimer* ReturnLiuTimer();//返回增强蜀军能力的计时器
    int ReturnCoutLiuBei();//返回在场刘备数目
    int ReturnCoutLiuShen();//返回在场刘谌数目
protected:
    void mousePressEvent(QMouseEvent *event);//重写鼠标点击事件,召唤蜀国英烈
    void mouseDoubleClickEvent(QMouseEvent *event);//重写鼠标双击事件，召唤更为强大的蜀国英烈
private:
    QList<Tower> AzureDragonScenceTower_List;//管理青龙关塔信息;
    QList<Tower> BlackTortoiseScenceTower_List;//管理玄武关塔信息;
    QList<Tower> VermilionBirdScenceTower_List;//管理朱雀关塔信息;
    QList<Tower> WhiteTigerScenceTower_List;//管理白虎关塔信息;
    QList<RoutePoint *> AzureDragonScenceRoutePoint_List;//管理青龙关屯田点信息
    QList<RoutePoint *> BlackTortoiseScenceRoutePoint_List;//管理玄武关屯田点信息
    QList<RoutePoint *> VermilionBirdScenceRoutePoint_List;//管理朱雀关屯田点信息
    QList<RoutePoint *> WhiteTigerScenceRoutePoint_List;//管理白虎关屯田点信息
    QList<CloseCombatDefend *> CloseCombatDefend_List;//管理近战塔防信息
    QList<WeiSodier *> WeiSodier_List;//管理魏军信息
    QList<Efficacy *> Efficacy_List;//管理特效信息
    void LoadTowerCoordinate();//载入塔信息
    void LoadRoutePoint();//载入屯田点信息
    bool LoadBatch();//载入魏军批数
    QString Flag=NULL;//选关信号
    int WeiSodier_Batch;//魏军批数
    int Batch;//波数，对比值
    bool WarWin;//战争胜利
    bool WarLose;//战争失败
    int ChengDuCitizenry;//成都民心，当民心为0时，战争失败，后主投降
    int ShuMorale;//蜀国士气，消耗士气，可以召唤蜀国英烈抵御魏军攻击
    QTimer *mousetimer;
    bool singleClicked;//单击信号
    QSound *ScenceSound;//背景音乐
    QSound *GetDamage1;//成都被攻击时的音乐1
    QSound *GetDamage2;//成都被攻击时的音乐2
    QSound *GetDamage3;//成都被攻击时的音乐3
    QTimer *WeiSodier_Timer;//定时器，增强魏军能力
    QTimer *Liu_Timer;//定时器，定时检测刘备/刘谌个数的变化
    int WeiTime;//数值，随着时间的增加而增加
    int Cout;//记录经过了多少次计时
    int CoutLiuBei;//记录战场上出现了多少个刘备
    int CoutLiuShen;//记录战场上出现了多少个刘谌
    int CoutLiuBeiRecord;//对比值，刘备
    int CoutLiuShenRecord;//对比值，刘谌
    QPushButton *btnAddBatch;//增加总批数按钮
    QPushButton *btnAddCurrentBatch;//增加当前批数按钮
    QPushButton *btnDecreaseBatch;//减少总批数按钮
    QPushButton *btnDecreaseCurrentBatch;//减少当前批数按钮


signals:

public slots:
    void mouseClick();
private slots:
    void RenewMap();//更新地图模拟帧数
    void WarBegin();//战争开始
};

#endif // DIFFERENTSCENCE_H
