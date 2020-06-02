#ifndef CLOSECOMBATDEFEND_H
#define CLOSECOMBATDEFEND_H
#include <QPoint>
#include "differentscence.h"
#include <QPixmap>
#include <QSize>
#include <QWidget>
class DifferentScence;
class CloseCombatDefend : public QObject
{
    Q_OBJECT
public:
    CloseCombatDefend(QPoint coordinate,DifferentScence *scence,const QPixmap &picture=QPixmap(":/button/backbutton.png"));//构造函数的实现
    void draw(QPainter *painter) const;//载入近战塔防图片;
private:
    int CloseCombatDefend_damage;//近战塔防伤害
    int CloseCombatDefend_radius;//近战塔防攻击范围
    int CloseCombatDefend_frequency;//近战塔防攻击频率
    QPoint CloseCombatDefend_coordinate;//近战塔防坐标
    QPixmap CloseCombatDefend_picture;//近战塔防图片
    DifferentScence* setScence;//设置载入场景对象
signals:

public slots:
};

#endif // CLOSECOMBATDEFEND_H
