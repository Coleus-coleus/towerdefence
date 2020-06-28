#include "closecombatdefend.h"
#include "differentscence.h"
#include <QPixmap>
#include <QPainter>
#include <QDebug>
#include <QPoint>
#include <QSize>
#include <QTimer>
#include <ctime>
#include <cstdlib>
#include "tower.h"
#include "efficacy.h"
#include <QSound>
#include "wind.h"
CloseCombatDefend::CloseCombatDefend(QPoint coordinate,DifferentScence* scence,const int way,const QPixmap &picture)
    :CloseCombatDefend_damage(0),
     CloseCombatDefend_radius(0),
     CloseCombatDefend_frequency(0),
     My_ChooseWeiSodier(NULL),
     CloseCombatDefend_coordinate(coordinate),
     CloseCombatDefend_picture(picture),
     setScence(scence),
     DefendIdentity(" "),
     AppearSound(NULL),
     DeadSound(NULL),
     Way(way)
{
    Level=1;
    if(Way==0)
    {
    srand(int(time(0)));
    int judge=rand()%4+1;
    if(judge==1)
    {
        AppearSound=new QSound(":/ZhuGe/ZhuGeZhan/ZhuGeZhan_Appear.wav",this);
        DeadSound=new QSound(":/ZhuGe/ZhuGeZhan/ZhuGeZhan_Dead.wav",this);
        AppearSound->play();
        CloseCombatDefend_picture=QPixmap(":/ZhuGe/ZhuGeZhan/ZhuGeZhan.png");
        QSize PictureSize(200,200);
        QPixmap SizePicture=CloseCombatDefend_picture.scaled(PictureSize,Qt::KeepAspectRatio);
        CloseCombatDefend_picture=SizePicture;
        DefendIdentity="ZhuGeZhan";

    }
    else if(judge==2)
    {
        AppearSound=new QSound(":/LiuHan/LiuShen/LiuShen_Appear.wav",this);
        DeadSound=new QSound(":/LiuHan/LiuShen/LiuShen_Dead.wav",this);
        AppearSound->play();
        CloseCombatDefend_picture=QPixmap(":/LiuHan/LiuShen/LiuShen.png");
        QSize PictureSize(200,200);
        QPixmap SizePicture=CloseCombatDefend_picture.scaled(PictureSize,Qt::KeepAspectRatio);
        CloseCombatDefend_picture=SizePicture;
        DefendIdentity="LiuShen";
    }
    else if(judge==3)
    {
        AppearSound=new QSound(":/HanShen/HanShen_Appear.wav",this);
        DeadSound=new QSound(":/HanShen/HanShen_Dead.wav",this);
        AppearSound->play();
        CloseCombatDefend_picture=QPixmap(":/HanShen/HanShen.png");
        QSize PictureSize(200,200);
        CloseCombatDefend_damage=160;
        CloseCombatDefend_frequency=1000;
        CloseCombatDefend_radius=370;
        QPixmap SizePicture=CloseCombatDefend_picture.scaled(PictureSize,Qt::KeepAspectRatio);
        CloseCombatDefend_picture=SizePicture;
        DefendIdentity="HanShen";
        CloseCombatDefend_frequencyTimer= new QTimer(this);
        connect(CloseCombatDefend_frequencyTimer,SIGNAL(timeout()),this,SLOT(CutWeiSodier()));
    }
    else if(judge==4)
    {
        AppearSound=new QSound(":/GuanZhang/GuanXingZhangBao/GuanXingZhangBao_Appear.wav",this);
        DeadSound=new QSound(":/GuanZhang/GuanXingZhangBao/GuanXingZhangBao_Dead.wav",this);
        AppearSound->play();
        CloseCombatDefend_picture=QPixmap(":/GuanZhang/GuanXingZhangBao/GuanXingZhangBao.png");
        QSize PictureSize(200,200);
        CloseCombatDefend_damage=160;
        CloseCombatDefend_frequency=1500;
        CloseCombatDefend_radius=200;
        QPixmap SizePicture=CloseCombatDefend_picture.scaled(PictureSize,Qt::KeepAspectRatio);
        CloseCombatDefend_picture=SizePicture;
        DefendIdentity="GuanXingZhangBao";
        CloseCombatDefend_frequencyTimer= new QTimer(this);
        connect(CloseCombatDefend_frequencyTimer,SIGNAL(timeout()),this,SLOT(CutWeiSodier()));
    }
    }
    else if(Way==1)
    {
        AppearSound=new QSound(":/LiuHan/LiuShen/LiuShen_Appear.wav",this);
        DeadSound=new QSound(":/LiuHan/LiuShen/LiuShen_Dead.wav",this);
        AppearSound->play();
        CloseCombatDefend_picture=QPixmap(":/LiuHan/LiuShen/LiuShen.png");
        QSize PictureSize(200,200);
        QPixmap SizePicture=CloseCombatDefend_picture.scaled(PictureSize,Qt::KeepAspectRatio);
        CloseCombatDefend_picture=SizePicture;
        DefendIdentity="LiuShen";
    }
    else if(Way==2)
    {
        AppearSound=new QSound(":/GuanZhang/GuanXingZhangBao/GuanXingZhangBao_Appear.wav",this);
        DeadSound=new QSound(":/GuanZhang/GuanXingZhangBao/GuanXingZhangBao_Dead.wav",this);
        AppearSound->play();
        CloseCombatDefend_picture=QPixmap(":/GuanZhang/GuanXingZhangBao/GuanXingZhangBao.png");
        QSize PictureSize(200,200);
        CloseCombatDefend_damage=160;
        CloseCombatDefend_frequency=1500;
        CloseCombatDefend_radius=200;
        QPixmap SizePicture=CloseCombatDefend_picture.scaled(PictureSize,Qt::KeepAspectRatio);
        CloseCombatDefend_picture=SizePicture;
        DefendIdentity="GuanXingZhangBao";
        CloseCombatDefend_frequencyTimer= new QTimer(this);
        connect(CloseCombatDefend_frequencyTimer,SIGNAL(timeout()),this,SLOT(CutWeiSodier()));
    }
    else if(Way==3)
    {
        AppearSound=new QSound(":/HanShen/HanShen_Appear.wav",this);
        DeadSound=new QSound(":/HanShen/HanShen_Dead.wav",this);
        AppearSound->play();
        CloseCombatDefend_picture=QPixmap(":/HanShen/HanShen.png");
        QSize PictureSize(200,200);
        CloseCombatDefend_damage=160;
        CloseCombatDefend_frequency=1000;
        CloseCombatDefend_radius=370;
        QPixmap SizePicture=CloseCombatDefend_picture.scaled(PictureSize,Qt::KeepAspectRatio);
        CloseCombatDefend_picture=SizePicture;
        DefendIdentity="HanShen";
        CloseCombatDefend_frequencyTimer= new QTimer(this);
        connect(CloseCombatDefend_frequencyTimer,SIGNAL(timeout()),this,SLOT(CutWeiSodier()));
    }
    else if(Way==4)
    {
        AppearSound=new QSound(":/ZhuGe/ZhuGeZhan/ZhuGeZhan_Appear.wav",this);
        DeadSound=new QSound(":/ZhuGe/ZhuGeZhan/ZhuGeZhan_Dead.wav",this);
        AppearSound->play();
        CloseCombatDefend_picture=QPixmap(":/ZhuGe/ZhuGeZhan/ZhuGeZhan.png");
        QSize PictureSize(200,200);
        QPixmap SizePicture=CloseCombatDefend_picture.scaled(PictureSize,Qt::KeepAspectRatio);
        CloseCombatDefend_picture=SizePicture;
        DefendIdentity="ZhuGeZhan";
    }
}
CloseCombatDefend::~CloseCombatDefend()
{
    delete CloseCombatDefend_frequencyTimer;
    CloseCombatDefend_frequencyTimer=NULL;
}

void CloseCombatDefend::draw(QPainter *painter) const//载入近战塔防图片
{
   painter->save();
   painter->setPen(Qt::white);
   if(DefendIdentity!="ZhuGeLiang"&&DefendIdentity!="ZhuGeZhan"&&DefendIdentity!="LiuBei"&&DefendIdentity!="LiuShen")
   painter->drawEllipse(CloseCombatDefend_coordinate,CloseCombatDefend_radius,CloseCombatDefend_radius);
   static const QPoint offsetPoint(-80,-80);
   painter->translate(CloseCombatDefend_coordinate);
   painter->drawPixmap(offsetPoint,CloseCombatDefend_picture);
   painter->restore();

}
//开始攻击魏军
void CloseCombatDefend::StartAttackWeiSodier()
{
    if(DefendIdentity!="ZhuGeLiang"&&DefendIdentity!="LiuBei"&&DefendIdentity!="LiuShen"&&DefendIdentity!="ZhuGeZhan")
    {
    CloseCombatDefend_frequencyTimer->start(CloseCombatDefend_frequency);
    }
}
//停止攻击魏军
void CloseCombatDefend::StopAttackWeiSodier()
{
    if(DefendIdentity!="ZhuGeLiang"&&DefendIdentity!="LiuBei"&&DefendIdentity!="LiuShen"&&DefendIdentity!="ZhuGeZhan")
    {
    CloseCombatDefend_frequencyTimer->stop();
    }
}

//选择攻击对象
void CloseCombatDefend::ChooseWeiSodier(WeiSodier *weiSodier)
{
    if(DefendIdentity!="ZhuGeLiang"&&DefendIdentity!="LiuBei"&&DefendIdentity!="LiuShen"&&DefendIdentity!="ZhuGeZhan")
    {
    My_ChooseWeiSodier=weiSodier;
    StartAttackWeiSodier();
    My_ChooseWeiSodier->GetAttacked(this);
    }
}
void CloseCombatDefend::CheckWeiSodierInRange()
{
    if(DefendIdentity!="ZhuGeLiang"&&DefendIdentity!="LiuBei"&&DefendIdentity!="LiuShen"&&DefendIdentity!="ZhuGeZhan")
    {
    if(My_ChooseWeiSodier)
    {
        if(!CollisionWithCircle(CloseCombatDefend_coordinate,CloseCombatDefend_radius,My_ChooseWeiSodier->Coordinate(),1))
        {
            WeiSodierEscape();
        }

    }
    else
    {
        QList<WeiSodier *> WeiSodierList=setScence->WeiSodier_list();
        foreach (WeiSodier *weiSodier, WeiSodierList)
        {
            if(CollisionWithCircle(CloseCombatDefend_coordinate,CloseCombatDefend_radius,weiSodier->Coordinate(),0.5))
            {
                ChooseWeiSodier(weiSodier);
                break;
            }
        }

    }
    }
}

//砍杀魏军
void CloseCombatDefend::CutWeiSodier()
{
    if(DefendIdentity!="ZhuGeLiang"&&DefendIdentity!="LiuBei"&&DefendIdentity!="LiuShen"&&DefendIdentity!="ZhuGeZhan")
    {
    Efficacy *efficacy=new Efficacy(CloseCombatDefend_coordinate,My_ChooseWeiSodier->Coordinate(),
    CloseCombatDefend_damage,My_ChooseWeiSodier,setScence);
    if(DefendIdentity=="HanShen")
    {
        if(Level==2)
        {
            efficacy->ChangeVermilion();
            efficacy->Move();
//            efficacy->ReturnSound()->play();
            setScence->AddEfficacy(efficacy);
        }
        else
        {
            efficacy->ChangePicture();
            efficacy->Move();
//            efficacy->ReturnSound()->play();
            setScence->AddEfficacy(efficacy);
        }
    }
    else if(DefendIdentity=="GuanYu")
    {
        efficacy->ChangeDragon();
        efficacy->Move();
        efficacy->ReturnSound()->play();
        setScence->AddEfficacy(efficacy);
    }
    else if(DefendIdentity=="ZhangFei")
    {
            efficacy->ChangeTiger();
            efficacy->Move();
            efficacy->ReturnSound()->play();
            setScence->AddEfficacy(efficacy);
    }
    else if(DefendIdentity=="GuanXingZhangBao")
    {
    efficacy->Move();
//    efficacy->ReturnSound()->play();
    setScence->AddEfficacy(efficacy);
    }
    }
}
//魏军已死
void CloseCombatDefend::WeiSodierKilled()
{
    if(My_ChooseWeiSodier)
        My_ChooseWeiSodier=NULL;
    CloseCombatDefend_frequencyTimer->stop();
}
//魏军已逃
void CloseCombatDefend::WeiSodierEscape()
{
    if(DefendIdentity!="ZhuGeLiang"&&DefendIdentity!="LiuBei"&&DefendIdentity!="LiuShen"&&DefendIdentity!="ZhuGeZhan")
    {
    My_ChooseWeiSodier->Escape(this);
    if(My_ChooseWeiSodier)
        My_ChooseWeiSodier=NULL;
    CloseCombatDefend_frequencyTimer->stop();
    }
}
//返回英烈坐标
QPoint CloseCombatDefend::Coordiante()
{
    return CloseCombatDefend_coordinate;
}
void CloseCombatDefend::UpgradeSpirit()
{
    if(Level==1)
    {
    if(DefendIdentity=="GuanXingZhangBao")
    {
    srand(int(time(0)));
    int judge=rand()%2+1;
    if(judge==1)
    {
        AppearSound=new QSound(":/GuanZhang/GuanYu/GuanYu_Appear.wav",this);
        DeadSound=new QSound(":/GuanZhang/GuanYu/GuanYu_Dead.wav",this);
        AppearSound->play();
        CloseCombatDefend_damage=1200;
        CloseCombatDefend_frequency=1500;
        CloseCombatDefend_radius=240;
        CloseCombatDefend_picture=QPixmap(":/GuanZhang/GuanYu/GuanYu.png");
        QSize PictureSize(200,200);
        QPixmap SizePicture=CloseCombatDefend_picture.scaled(PictureSize,Qt::KeepAspectRatio);
        CloseCombatDefend_picture=SizePicture;
        DefendIdentity="GuanYu";
        Level=2;
    }
    else if(judge==2)
    {
        AppearSound=new QSound(":/GuanZhang/ZhangFei/ZhangFei_Appear.wav",this);
        DeadSound=new QSound(":/GuanZhang/ZhangFei/ZhangFei_Dead.wav",this);
        AppearSound->play();
        CloseCombatDefend_damage=800;
        CloseCombatDefend_frequency=800;
        CloseCombatDefend_radius=240;
        CloseCombatDefend_picture=QPixmap(":/GuanZhang/ZhangFei/ZhangFei.png");
        QSize PictureSize(200,200);
        QPixmap SizePicture=CloseCombatDefend_picture.scaled(PictureSize,Qt::KeepAspectRatio);
        CloseCombatDefend_picture=SizePicture;
        DefendIdentity="ZhangFei";
        Level=2;

    }
    }
    else if(DefendIdentity=="ZhuGeZhan")
    {
        AppearSound=new QSound(":/ZhuGe/ZhuGeLiang/ZhuGeLiang_Appear.wav",this);
        DeadSound=new QSound(":/ZhuGe/ZhuGeLiang/ZhuGeLiang_Dead.wav",this);
        AppearSound->play();
        CloseCombatDefend_damage=1000;
        CloseCombatDefend_frequency=100;
        CloseCombatDefend_picture=QPixmap(":/ZhuGe/ZhuGeLiang/ZhuGeLiang.png");
        QSize PictureSize(200,200);
        QPixmap SizePicture=CloseCombatDefend_picture.scaled(PictureSize,Qt::KeepAspectRatio);
        CloseCombatDefend_picture=SizePicture;
        DefendIdentity="ZhuGeLiang";
        Level=2;

    }
    else if(DefendIdentity=="LiuShen")
    {
        AppearSound=new QSound(":/LiuHan/LiuBei/LiuBei_Appear.wav",this);
        DeadSound=new QSound(":/LiuHan/LiuBei/LiuBei_Dead.wav",this);
        AppearSound->play();
        CloseCombatDefend_damage=0;
        CloseCombatDefend_frequency=1000;
        CloseCombatDefend_picture=QPixmap(":/LiuHan/LiuBei/LiuBei.png");
        QSize PictureSize(200,200);
        QPixmap SizePicture=CloseCombatDefend_picture.scaled(PictureSize,Qt::KeepAspectRatio);
        CloseCombatDefend_picture=SizePicture;
        DefendIdentity="LiuBei";
        Level=2;
    }
    else if (DefendIdentity=="HanShen")
    {
        CloseCombatDefend_damage=400;
        CloseCombatDefend_frequency=800;
        CloseCombatDefend_radius=380;
        Level=2;
    }
    }
    else
    {
        return;
    }
}
//返回英烈的身份信息
QString CloseCombatDefend::ReturnIdentity()
{
    return DefendIdentity;
}
//返回英烈出现时的音乐
QSound* CloseCombatDefend::ReturnAppearSound()
{
    return AppearSound;
}

//返回英烈消失时的音乐
QSound* CloseCombatDefend::ReturnDeadSound()
{
    return DeadSound;
}
//当刘备/刘谌在场时，全场英烈受到鼓舞，攻击能力增强
void CloseCombatDefend::Encouraged()
{
    int Cout1=setScence->ReturnCoutLiuShen();
    int Cout2=setScence->ReturnCoutLiuBei();
    CloseCombatDefend_damage=CloseCombatDefend_damage+Cout1*100+Cout2*350;
    if(CloseCombatDefend_frequency-Cout1*25-Cout2*75>=0)
    CloseCombatDefend_frequency=CloseCombatDefend_frequency-Cout1*25-Cout2*75;
    else
    {
        CloseCombatDefend_frequency=1;
    }
    CloseCombatDefend_radius=CloseCombatDefend_radius+Cout1*5+Cout2*10;

}
//返回英烈等级
int CloseCombatDefend::ReturnLevel()
{
    return Level;
}
