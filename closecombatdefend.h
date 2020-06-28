#ifndef CLOSECOMBATDEFEND_H
#define CLOSECOMBATDEFEND_H
#include <QPoint>
#include "differentscence.h"
#include "weisodier.h"
#include <QPixmap>
#include <QSize>
#include <QObject>
#include <QWidget>
#include <QSound>
#include "wind.h"
class QPainter;
class DifferentScence;
class WeiSodier;
class QTimer;

class CloseCombatDefend : public QObject
{
    Q_OBJECT
public:
    CloseCombatDefend(QPoint coordinate,DifferentScence *scence,const int way=0,const QPixmap &picture=QPixmap(":/GuanZhang/GuanXingZhangBao/GuanXingZhangBao.png"));//构造函数的实现
    ~CloseCombatDefend();//析构函数
    QPoint Coordiante();//返回塔防坐标
    void draw(QPainter *painter) const;//载入近战塔防图片;
    void StartAttackWeiSodier();//开始攻击
    void StopAttackWeiSodier();//停止攻击
    void ChooseWeiSodier(WeiSodier *weiSodier);//选择攻击对象
    void CheckWeiSodierInRange();//检查敌人是否在攻击范围内
    void WeiSodierKilled();//魏军已死
    void WeiSodierEscape();//魏军已逃
    void UpgradeSpirit();//召唤更为强大的蜀国英烈
    void Encouraged();//当刘备/刘谌在场时，全场英烈受到鼓舞，攻击能力增强
    QString ReturnIdentity();//返回英烈的身份信息
    QSound* ReturnAppearSound();//返回英烈出现时的音乐
    QSound* ReturnDeadSound();//返回英烈消失时的音乐
    int ReturnLevel();//返回英烈等级
    
private:
    int CloseCombatDefend_damage;//近战塔防伤害
    int CloseCombatDefend_radius;//近战塔防攻击范围
    int CloseCombatDefend_frequency;//近战塔防攻击频率
    QTimer * CloseCombatDefend_frequencyTimer;//攻击频率计算
    WeiSodier * My_ChooseWeiSodier;//所攻击的对象
    QPoint CloseCombatDefend_coordinate;//近战塔防坐标
    QPixmap CloseCombatDefend_picture;//近战塔防图片
    DifferentScence* setScence;//设置载入场景对象
    QString DefendIdentity;//记录英烈身份
    QSound *AppearSound;//英烈出现时的音乐
    QSound *DeadSound;//英烈消失时出现的音乐
    int Level;//记录英烈等级
    int Way;//判断采用哪种方式安装塔防
signals:

public slots:
private slots:
    void CutWeiSodier();//砍杀魏军
};

#endif // CLOSECOMBATDEFEND_H
