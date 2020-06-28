#ifndef WIND_H
#define WIND_H

#include <QObject>
#include <QPoint>
#include <QSize>
#include <QPixmap>
#include <QObject>
#include "weisodier.h"
#include "differentscence.h"
#include <QSound>
class QPainter;
class WeiSodier;
class DifferentScence;

class Wind : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QPoint My_CurrentPoint READ CurrentPoint WRITE SetCurrentPoint)
public:
    Wind(QPoint StartPoint,QPoint TargetPoint,int Hurt,WeiSodier *TargetWeiSodier,DifferentScence *Scence,
    const QPixmap &Picture=QPixmap(":/Wind/Wind.png"));//构造函数
    void draw(QPainter *painter)const;//绘画函数
    void SetCurrentPoint(QPoint Point);//设置现在的位置
    QPoint CurrentPoint()const;//返回现在的位置
    QSound* ReturnSound();//返回特效音乐
    void Appear();//风的出现
    void ChangePicture();//改变图片大小
private:
    QPoint My_StartPoint;
    QPoint My_TargetPoint;
    QPoint  My_CurrentPoint;
    QPixmap	My_Picture;
    WeiSodier *		My_TargetWeiSodier;
    DifferentScence * My_Scence;
    int				My_Hurt;
    QSound* My_Sound;//攻击音效

signals:
public slots:
private slots:
    void HitTarget();//击中魏军

};

#endif // WIND_H
