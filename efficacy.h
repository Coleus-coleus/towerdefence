#ifndef EFFICACY_H
#define EFFICACY_H

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
class Efficacy : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QPoint My_CurrentPoint READ CurrentPoint WRITE SetCurrentPoint)
public:
    Efficacy(QPoint StartPoint,QPoint TargetPoint,int Hurt,WeiSodier *TargetWeiSodier,DifferentScence *Scence,
    const QPixmap &Picture=QPixmap(":/Efficacy/Cut.png"));//构造函数
    void draw(QPainter *painter)const;//绘画函数
    void Move();//移动
    void SetCurrentPoint(QPoint Point);//设置现在的位置
    void ChangePicture();//改变图片，黄忠专用
    QPoint CurrentPoint()const;//返回现在的位置
    QSound* ReturnSound();//返回特效音乐
private:
    QPoint	My_StartPoint;
    QPoint	My_TargetPoint;
    QPixmap	My_Picture;
    QPoint			My_CurrentPoint;
    WeiSodier *		My_TargetWeiSodier;
    DifferentScence * My_Scence;
    int				My_Hurt;
    QString My_kind;//记录攻击的类型，从而使用不同音效
    QSound* My_Sound;//攻击音效


signals:

public slots:
private slots:
    void CutTarget();//击中魏军
};

#endif // EFFICACY_H
