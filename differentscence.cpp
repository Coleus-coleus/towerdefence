#include "differentscence.h"
#include "closecombatdefend.h"
#include "tower.h"
#include "routepoint.h"
#include "weisodier.h"
#include "efficacy.h"
#include <QPainter>
#include <QPixmap>
#include <QIcon>
#include <QPoint>
#include <QList>
#include <QDebug>
#include <QString>
#include <QTimer>
#include <QObject>
#include <ctime>
#include <cstdlib>
#include <QSound> //多媒体模块下的音效文件
#include "sleep.h"
#include <QPushButton>
#include "endscence.h"
#include "wind.h"
class CloseCombatDefend;
int g_unused=(srand(time(NULL)),0);
//构造函数的实现
DifferentScence::DifferentScence(QWidget *parent) :
    QWidget(parent),
    WeiSodier_Batch(1),
    WarWin(false),
    WarLose(false),
    ChengDuCitizenry(10),
    ShuMorale(1000)
{
    this->setAttribute(Qt::WA_DeleteOnClose,true);
    btnAddMorale=new QPushButton("增加士气",this);//增加士气,每次增加1000
    connect(btnAddMorale,&QPushButton::clicked,this,[=]()
    {
        ShuMorale=ShuMorale+1000;
    });
    Defend_Kind=" ";
    btnZhuGeZhan=new QPushButton("诸葛瞻",this);//标记诸葛瞻
    btnHanShen=new QPushButton("黄忠",this);//标记黄忠
    btnGuanXingZhangBao=new QPushButton("关兴张苞",this);//标记关兴张苞
    btnLiuShen=new QPushButton("刘谌",this);//标记刘谌
    connect(btnZhuGeZhan,&QPushButton::clicked,this,[=]()
    {
        ChangeKind("ZhuGeZhan");
    });
    connect(btnGuanXingZhangBao,&QPushButton::clicked,this,[=]()
    {
        ChangeKind("GuanXingZhangBao");
    });
    connect(btnHanShen,&QPushButton::clicked,this,[=]()
    {
        ChangeKind("HanShen");
    });
    connect(btnLiuShen,&QPushButton::clicked,this,[=]()
    {
        ChangeKind("LiuShen");
    });
    CoutZhuGeLiang=0;
    CoutZhuGeZhan=0;
    Endscence=new EndScence;//实例化，结束场景
    IsEndless=false;
    btnAddBatch=new QPushButton("增加总批数",this);//增加总批数按钮
    btnAddCurrentBatch=new QPushButton("增加当前批数",this);//增加当前批数按钮
    btnDecreaseBatch=new QPushButton("减少总批数",this);//减少总批数按钮
    btnDecreaseCurrentBatch=new QPushButton("减少当前批数",this);//减少当前批数按钮
    btnEndless=new QPushButton("无尽模式",this);//无尽模式按钮
    connect(btnAddBatch,&QPushButton::clicked,this,[=]()
    {
        AddBatch();
    });
    connect(btnAddCurrentBatch,&QPushButton::clicked,this,[=]()
    {
        AddCurrentBatch();
    });
    connect(btnDecreaseBatch,&QPushButton::clicked,this,[=]()
    {
        DecreaseBatch();
    });
    connect(btnDecreaseCurrentBatch,&QPushButton::clicked,this,[=]()
    {
        DecreaseCurrentBatch();
    });
    connect(btnEndless,&QPushButton::clicked,this,[=]()
    {
        Endless();
    });
    Batch=60;
    CoutLiuBei=0;
    CoutLiuShen=0;
    CoutLiuBeiRecord=0;
    CoutLiuShenRecord=0;
    GetDamage1=new QSound(":/LiuHan/ChengDu_LiuShan/ChengDu_LiuShanGetDamaged1.wav",this);
    GetDamage2=new QSound(":/LiuHan/ChengDu_LiuShan/ChengDu_LiuShanGetDamaged2.wav",this);
    GetDamage3=new QSound(":/LiuHan/ChengDu_LiuShan/ChengDu_LiuShanGetDamaged3.wav",this);
    ScenceSound=new QSound(":/Music/ScenceMusic.wav",this);
    ScenceSound->setLoops(1000000);
    WeiTime=0;
    Cout=0;
    singleClicked=false;
    mousetimer = new QTimer(this);
    connect(mousetimer, SIGNAL(timeout()), this, SLOT(mouseClick()));
    setWindowIcon(QIcon(":/logo/logo.png"));
    this->setFixedSize(1600,1000);
    setWindowTitle("蜀汉悲歌");
    QTimer *timer=new QTimer(this);
    connect(timer,&QTimer::timeout,this,&DifferentScence::RenewMap);
    timer->start(20);
    WeiSodier_Timer=new QTimer(this);
    Liu_Timer=new QTimer(this);
    ZhuGeLiangTimer=new QTimer(this);
    ZhuGeZhanTimer=new QTimer(this);
    connect(WeiSodier_Timer,&QTimer::timeout,this,[=]()
    {
        WeiTime=WeiTime+10;
        Cout=WeiTime/10;
    });
    connect(Liu_Timer,&QTimer::timeout,this,[=]()
    {
        int i=0;
        int j=0;
        int m=0;
        int n=0;
        foreach (CloseCombatDefend *closeCombatDefend, CloseCombatDefend_List )
        {
            if(closeCombatDefend->ReturnIdentity()=="LiuShen")
            {
                i++;
            }
            else if(closeCombatDefend->ReturnIdentity()=="LiuBei")
            {
                j++;
            }
            else if(closeCombatDefend->ReturnIdentity()=="ZhuGeLiang")
            {
                m++;
            }
            else if(closeCombatDefend->ReturnIdentity()=="ZhuGeZhan")
            {
                n++;
            }
        }
        CoutLiuShen=i;
        CoutLiuBei=j;
        CoutZhuGeLiang=m;
        CoutZhuGeZhan=n;
        foreach (CloseCombatDefend *closeCombatDefend, CloseCombatDefend_List )
        {
            closeCombatDefend->Encouraged();
        }
        CoutLiuShenRecord=CoutLiuShen;
        CoutLiuBeiRecord=CoutLiuBei;
    });
    connect(ZhuGeLiangTimer,&QTimer::timeout,this,[=]()
    {
        for(int num=0;num<CoutZhuGeLiang;num++)
        {
        foreach (WeiSodier *weisodier, WeiSodier_List)
        {
            Wind *wind=new Wind(weisodier->Coordinate(),weisodier->Coordinate(),25,weisodier,this);
            wind->ChangePicture();
            wind->Appear();
            this->AddWind(wind);
//            QSound *Wind_Sound=new QSound(":/Wind/Wind.wav",this);
//            Wind_Sound->play();
            if(weisodier->ReturnCurrentHP()<=0)
            {
                destroyWeiSodier(weisodier);
            }
        }
        }
    });
    connect(ZhuGeZhanTimer,&QTimer::timeout,this,[=]()
    {
        for(int num=0;num<CoutZhuGeZhan;num++)
        {
        foreach (WeiSodier *weisodier, WeiSodier_List)
        {
            Wind *wind=new Wind(weisodier->Coordinate(),weisodier->Coordinate(),50,weisodier,this);
            wind->Appear();
            this->AddWind(wind);
//            QSound *Wind_Sound=new QSound(":/Wind/Wind.wav",this);
//            Wind_Sound->play();
            if(weisodier->ReturnCurrentHP()<=0)
            {
                destroyWeiSodier(weisodier);
            }
        }
        }
    });
    ZhuGeZhanTimer->start(3000);
    ZhuGeLiangTimer->start(1500);
}
//传入选关信号
void DifferentScence::ChangeScence(QString flag)
{
    Flag=flag;
    if(Flag=="AzureDragonScence")
    {
        btnLiuShen->move(1430,380);
        btnGuanXingZhangBao->move(1430,420);
        btnZhuGeZhan->move(1430,460);
        btnHanShen->move(1430,500);
        btnAddBatch->move(1430,160);
        btnAddCurrentBatch->move(1430,200);
        btnDecreaseBatch->move(1430,240);
        btnDecreaseCurrentBatch->move(1430,280);
        btnEndless->move(1430,320);
        btnAddMorale->move(1430,560);
    }
    else if(Flag=="VermilionBirdScence")
    {
        btnLiuShen->move(800,0);
        btnGuanXingZhangBao->move(800,40);
        btnZhuGeZhan->move(800,80);
        btnHanShen->move(800,120);
        btnAddBatch->move(1430,160);
        btnAddCurrentBatch->move(1430,200);
        btnDecreaseBatch->move(1430,240);
        btnDecreaseCurrentBatch->move(1430,280);
        btnEndless->move(1430,320);
        btnAddMorale->move(800,160);
    }
    else if(Flag=="WhiteTigerScence")
    {
        btnLiuShen->move(890,130);
        btnGuanXingZhangBao->move(890,90);
        btnZhuGeZhan->move(890,50);
        btnHanShen->move(1010,130);
        btnDecreaseCurrentBatch->move(1010,90);
        btnEndless->move(1010,50);
        btnAddBatch->move(1130,50);
        btnAddCurrentBatch->move(1130,90);
        btnDecreaseBatch->move(1130,130);
        btnAddMorale->move(1430,160);
    }
    else if(Flag=="BlackTortoiseScence")
    {
        btnLiuShen->move(50,340);
        btnGuanXingZhangBao->move(50,380);
        btnZhuGeZhan->move(50,420);
        btnHanShen->move(50,460);
        btnAddBatch->move(50,120);
        btnAddCurrentBatch->move(50,160);
        btnDecreaseBatch->move(50,200);
        btnDecreaseCurrentBatch->move(50,240);
        btnEndless->move(50,280);
        btnAddMorale->move(50,60);
    }
    LoadTowerCoordinate();
    LoadRoutePoint();
    QTimer::singleShot(300,this,SLOT(WarBegin()));//开始游戏
}
//重写绘画事件(载入图片)
void DifferentScence::paintEvent(QPaintEvent *)
{
    //加载选关背景
    //青龙关
    if(Flag=="AzureDragonScence")
    {
        if(WarLose==true)
        {
            ScenceSound->stop();
            this->close();
            Endscence->EndFlag("WarLose");
            Endscence->show();
            Endscence->ChangSound();
            Endscence->ReturnEndMusic()->play();
         }
        else if(WarWin==true)
        {
            ScenceSound->stop();
            this->close();
            Endscence->EndFlag("WarWin");
            Endscence->show();
            Endscence->ChangSound();
            Endscence->ReturnEndMusic()->play();
        }
    QPixmap pix;
    pix.load(":/background/Azure DragonScence.png");
    QPainter painter(this);
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    foreach (const Tower &Tower_Coordinate,AzureDragonScenceTower_List )
    {
        Tower_Coordinate.draw(&painter);
    }
    foreach (CloseCombatDefend *closeCombatDefend, CloseCombatDefend_List )
    {
        closeCombatDefend->draw(&painter);
    }
    foreach(const RoutePoint *routePoint,AzureDragonScenceRoutePoint_List)
    {
        routePoint->draw(&painter);
    }
    foreach(const WeiSodier *weiSodier,WeiSodier_List)
    {
        weiSodier->draw(&painter);
    }
    foreach(const Efficacy *efficacy,Efficacy_List)
    {
        efficacy->draw(&painter);
    }
    foreach (const Wind *wind, Wind_List)
    {
        wind->draw(&painter);
    }
    DrawBatch(&painter);
    DrawChengDuCitizenry(&painter);
    DrawShuMorale(&painter);

    }
    //玄武关
    else if(Flag=="BlackTortoiseScence")
    {
        if(WarLose==true)
        {
            ScenceSound->stop();
            this->close();
            Endscence->EndFlag("WarLose");
            Endscence->show();
            Endscence->ChangSound();
            Endscence->ReturnEndMusic()->play();
         }
        else if(WarWin==true)
        {
            ScenceSound->stop();
            this->close();
            Endscence->EndFlag("WarWin");
            Endscence->show();
            Endscence->ChangSound();
            Endscence->ReturnEndMusic()->play();
        }

    QPixmap pix;
    pix.load(":/background/Black TortoiseScence.jpg");
    QPainter painter(this);
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    foreach (const Tower &Tower_Coordinate,BlackTortoiseScenceTower_List )
    {
        Tower_Coordinate.draw(&painter);
    }
    foreach (CloseCombatDefend *closeCombatDefend, CloseCombatDefend_List )
    {
        closeCombatDefend->draw(&painter);
    }
    foreach(const RoutePoint *routePoint,BlackTortoiseScenceRoutePoint_List)
    {
        routePoint->draw(&painter);
    }
    foreach(const WeiSodier *weiSodier,WeiSodier_List)
    {
        weiSodier->draw(&painter);
    }
    foreach(const Efficacy *efficacy,Efficacy_List)
    {
        efficacy->draw(&painter);
    }
    foreach (const Wind *wind, Wind_List)
    {
        wind->draw(&painter);
    }
    DrawBatch(&painter);
    DrawChengDuCitizenry(&painter);
    DrawShuMorale(&painter);
    }
    //朱雀关
    else if(Flag=="VermilionBirdScence")
    {
        if(WarLose==true)
        {
            ScenceSound->stop();
            this->close();
            Endscence->EndFlag("WarLose");
            Endscence->show();
            Endscence->ChangSound();
            Endscence->ReturnEndMusic()->play();
         }
        else if(WarWin==true)
        {
            ScenceSound->stop();
            this->close();
            Endscence->EndFlag("WarWin");
            Endscence->show();
            Endscence->ChangSound();
            Endscence->ReturnEndMusic()->play();
        }

        QPixmap pix;
        pix.load(":/background/Vermilion BirdScence.jpg");
        QPainter painter(this);
        painter.drawPixmap(0,0,this->width(),this->height(),pix);
        foreach (const Tower &Tower_Coordinate,VermilionBirdScenceTower_List )
        {
            Tower_Coordinate.draw(&painter);
        }
        foreach (CloseCombatDefend *closeCombatDefend, CloseCombatDefend_List )
        {
            closeCombatDefend->draw(&painter);
        }
        foreach(const RoutePoint *routePoint,VermilionBirdScenceRoutePoint_List)
        {
            routePoint->draw(&painter);
        }
        foreach(const WeiSodier *weiSodier,WeiSodier_List)
        {
            weiSodier->draw(&painter);
        }
        foreach(const Efficacy *efficacy,Efficacy_List)
        {
            efficacy->draw(&painter);
        }
        foreach (const Wind *wind, Wind_List)
        {
            wind->draw(&painter);
        }
        DrawBatch(&painter);
        DrawChengDuCitizenry(&painter);
        DrawShuMorale(&painter);
    }
    //白虎关
    else if(Flag=="WhiteTigerScence")
    {
        if(WarLose==true)
        {
            ScenceSound->stop();
            this->close();
            Endscence->EndFlag("WarLose");
            Endscence->show();
            Endscence->ChangSound();
            Endscence->ReturnEndMusic()->play();
         }
        else if(WarWin==true)
        {
            ScenceSound->stop();
            this->close();
            Endscence->EndFlag("WarWin");
            Endscence->show();
            Endscence->ChangSound();
            Endscence->ReturnEndMusic()->play();
        }
    QPixmap pix;
    pix.load(":/background/White TigerScence.png");
    QPainter painter(this);
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    foreach (const Tower &Tower_Coordinate,WhiteTigerScenceTower_List )
    {
        Tower_Coordinate.draw(&painter);
    }
    foreach (CloseCombatDefend *closeCombatDefend, CloseCombatDefend_List )
    {
        closeCombatDefend->draw(&painter);
    }
    foreach(const RoutePoint *routePoint,WhiteTigerScenceRoutePoint_List)
    {
        routePoint->draw(&painter);
    }
    foreach(const WeiSodier *weiSodier,WeiSodier_List)
    {
        weiSodier->draw(&painter);
    }
    foreach(const Efficacy *efficacy,Efficacy_List)
    {
        efficacy->draw(&painter);
    }
    foreach (const Wind *wind, Wind_List)
    {
        wind->draw(&painter);
    }
    DrawBatch(&painter);
    DrawChengDuCitizenry(&painter);
    DrawShuMorale(&painter);
    }
}
//重写鼠标点击事件，召唤蜀国英烈
void DifferentScence::mousePressEvent(QMouseEvent *event)
{
    mousetimer->start(200);
    if(singleClicked==true)
    {
    if(Flag=="AzureDragonScence")
    {
        if(event->button()==Qt::LeftButton)
        {
            QPoint MousePressCoordinate=event->pos();
            auto it=AzureDragonScenceTower_List.begin();
            while(it!=AzureDragonScenceTower_List.end())
            {
                if(WhetherWillRespond()&&it->inArea(MousePressCoordinate)&&!it->existence())
                {
                    if(Defend_Kind==" ")
                    {
                        if(ShuMorale>=150)
                        {
                            ShuMorale=ShuMorale-150;
                            it->tower_exist(true);
                            CloseCombatDefend *closeCombatDefend=new CloseCombatDefend(it->tower_centercoordinate(),this);
                            Defend_Kind=" ";
                            CloseCombatDefend_List.push_back(closeCombatDefend);
                            update();
                            break;
                        }
                    }
                    else if(Defend_Kind=="LiuShen")
                    {
                        if(ShuMorale>=200)
                        {
                            ShuMorale=ShuMorale-200;
                            it->tower_exist(true);
                            CloseCombatDefend *closeCombatDefend=new CloseCombatDefend(it->tower_centercoordinate(),this,1);
                            Defend_Kind=" ";
                            CloseCombatDefend_List.push_back(closeCombatDefend);
                            update();
                            break;
                        }
                    }
                    else if(Defend_Kind=="GuanXingZhangBao")
                    {
                        if(ShuMorale>=100)
                        {
                            ShuMorale=ShuMorale-100;
                            it->tower_exist(true);
                            CloseCombatDefend *closeCombatDefend=new CloseCombatDefend(it->tower_centercoordinate(),this,2);
                            Defend_Kind=" ";
                            CloseCombatDefend_List.push_back(closeCombatDefend);
                            update();
                            break;
                        }
                    }
                    else if(Defend_Kind=="HanShen")
                    {
                        if(ShuMorale>=150)
                        {
                            ShuMorale=ShuMorale-150;
                            it->tower_exist(true);
                            CloseCombatDefend *closeCombatDefend=new CloseCombatDefend(it->tower_centercoordinate(),this,3);
                            Defend_Kind=" ";
                            CloseCombatDefend_List.push_back(closeCombatDefend);
                            update();
                            break;
                        }
                    }
                    else if(Defend_Kind=="ZhuGeZhan")
                    {
                        if(ShuMorale>=300)
                        {
                            ShuMorale=ShuMorale-300;
                            it->tower_exist(true);
                            CloseCombatDefend *closeCombatDefend=new CloseCombatDefend(it->tower_centercoordinate(),this,4);
                            Defend_Kind=" ";
                            CloseCombatDefend_List.push_back(closeCombatDefend);
                            update();
                            break;
                        }
                    }

                }
                ++it;
            }
        }
        else if(event->button()==Qt::RightButton)
        {
            QPoint MousePressCoordinate=event->pos();
            auto it=AzureDragonScenceTower_List.begin();
            while(it!=AzureDragonScenceTower_List.end())
            {
                if(it->inArea(MousePressCoordinate)&&it->existence())
                {
                    for(int i=0;i<CloseCombatDefend_List.size();i++)
                    {
                        QPoint point=CloseCombatDefend_List[i]->Coordiante();
                        if(point==it->tower_centercoordinate())
                        {
                                CloseCombatDefend_List[i]->ReturnAppearSound()->stop();
                                CloseCombatDefend_List[i]->ReturnDeadSound()->play();
                                CloseCombatDefend_List[i]->StopAttackWeiSodier();
                                if(CloseCombatDefend_List[i]->ReturnLevel()==2)
                                {
                                    if(CloseCombatDefend_List[i]->ReturnIdentity()=="LiuBei")
                                    {
                                        ShuMorale=ShuMorale+560;
                                    }
                                    else if(CloseCombatDefend_List[i]->ReturnIdentity()=="ZhuGeLiang")
                                    {
                                        ShuMorale=ShuMorale+720;
                                    }
                                    else if(CloseCombatDefend_List[i]->ReturnIdentity()=="HanShen")
                                    {
                                        ShuMorale=ShuMorale+360;
                                    }
                                    else if(CloseCombatDefend_List[i]->ReturnIdentity()=="GuanYu")
                                    {
                                         ShuMorale=ShuMorale+400;
                                    }
                                    else if(CloseCombatDefend_List[i]->ReturnIdentity()=="ZhangFei")
                                    {
                                        ShuMorale=ShuMorale+400;
                                    }
                                }
                                else if(CloseCombatDefend_List[i]->ReturnLevel()==1)
                                {
                                    if(CloseCombatDefend_List[i]->ReturnIdentity()=="LiuShen")
                                    {
                                        ShuMorale=ShuMorale+160;
                                    }
                                    else if(CloseCombatDefend_List[i]->ReturnIdentity()=="ZhuGeZhan")
                                    {
                                        ShuMorale=ShuMorale+240;
                                    }
                                    else if(CloseCombatDefend_List[i]->ReturnIdentity()=="HanShen")
                                    {
                                        ShuMorale=ShuMorale+120;
                                    }
                                    else if(CloseCombatDefend_List[i]->ReturnIdentity()=="GuanXingZhangBao")
                                    {
                                         ShuMorale=ShuMorale+80;
                                    }
                                }
                                CloseCombatDefend_List.removeOne(CloseCombatDefend_List[i]);
                                it->tower_exist(false);
                                break;
                        }
                    }
                    break;
                }
                ++it;
            }
        }
        singleClicked=false;
    }
    else if(Flag=="BlackTortoiseScence")
    {
        if(event->button()==Qt::LeftButton)
        {
            QPoint MousePressCoordinate=event->pos();
            auto it=BlackTortoiseScenceTower_List.begin();
            while(it!=BlackTortoiseScenceTower_List.end())
            {
                if(WhetherWillRespond()&&it->inArea(MousePressCoordinate)&&!it->existence())
                {
                    if(Defend_Kind==" ")
                    {
                        if(ShuMorale>=150)
                        {
                            ShuMorale=ShuMorale-150;
                            it->tower_exist(true);
                            CloseCombatDefend *closeCombatDefend=new CloseCombatDefend(it->tower_centercoordinate(),this);
                            Defend_Kind=" ";
                            CloseCombatDefend_List.push_back(closeCombatDefend);
                            update();
                            break;
                        }
                    }
                    else if(Defend_Kind=="LiuShen")
                    {
                        if(ShuMorale>=200)
                        {
                            ShuMorale=ShuMorale-200;
                            it->tower_exist(true);
                            CloseCombatDefend *closeCombatDefend=new CloseCombatDefend(it->tower_centercoordinate(),this,1);
                            Defend_Kind=" ";
                            CloseCombatDefend_List.push_back(closeCombatDefend);
                            update();
                            break;
                        }
                    }
                    else if(Defend_Kind=="GuanXingZhangBao")
                    {
                        if(ShuMorale>=100)
                        {
                            ShuMorale=ShuMorale-100;
                            it->tower_exist(true);
                            CloseCombatDefend *closeCombatDefend=new CloseCombatDefend(it->tower_centercoordinate(),this,2);
                            Defend_Kind=" ";
                            CloseCombatDefend_List.push_back(closeCombatDefend);
                            update();
                            break;
                        }
                    }
                    else if(Defend_Kind=="HanShen")
                    {
                        if(ShuMorale>=150)
                        {
                            ShuMorale=ShuMorale-150;
                            it->tower_exist(true);
                            CloseCombatDefend *closeCombatDefend=new CloseCombatDefend(it->tower_centercoordinate(),this,3);
                            Defend_Kind=" ";
                            CloseCombatDefend_List.push_back(closeCombatDefend);
                            update();
                            break;
                        }
                    }
                    else if(Defend_Kind=="ZhuGeZhan")
                    {
                        if(ShuMorale>=300)
                        {
                            ShuMorale=ShuMorale-300;
                            it->tower_exist(true);
                            CloseCombatDefend *closeCombatDefend=new CloseCombatDefend(it->tower_centercoordinate(),this,4);
                            Defend_Kind=" ";
                            CloseCombatDefend_List.push_back(closeCombatDefend);
                            update();
                            break;
                        }
                    }

                }
                ++it;
            }
        }
        else if(event->button()==Qt::RightButton)
        {
            QPoint MousePressCoordinate=event->pos();
            auto it=BlackTortoiseScenceTower_List.begin();
            while(it!=BlackTortoiseScenceTower_List.end())
            {
                if(it->inArea(MousePressCoordinate)&&it->existence())
                {
                    for(int i=0;i<CloseCombatDefend_List.size();i++)
                    {
                        QPoint point=CloseCombatDefend_List[i]->Coordiante();
                        if(point==it->tower_centercoordinate())
                        {
                                CloseCombatDefend_List[i]->ReturnAppearSound()->stop();
                                CloseCombatDefend_List[i]->ReturnDeadSound()->play();
                                CloseCombatDefend_List[i]->StopAttackWeiSodier();
                                if(CloseCombatDefend_List[i]->ReturnLevel()==2)
                                {
                                    if(CloseCombatDefend_List[i]->ReturnIdentity()=="LiuBei")
                                    {
                                        ShuMorale=ShuMorale+560;
                                    }
                                    else if(CloseCombatDefend_List[i]->ReturnIdentity()=="ZhuGeLiang")
                                    {
                                        ShuMorale=ShuMorale+720;
                                    }
                                    else if(CloseCombatDefend_List[i]->ReturnIdentity()=="HanShen")
                                    {
                                        ShuMorale=ShuMorale+360;
                                    }
                                    else if(CloseCombatDefend_List[i]->ReturnIdentity()=="GuanYu")
                                    {
                                         ShuMorale=ShuMorale+400;
                                    }
                                    else if(CloseCombatDefend_List[i]->ReturnIdentity()=="ZhangFei")
                                    {
                                        ShuMorale=ShuMorale+400;
                                    }
                                }
                                else if(CloseCombatDefend_List[i]->ReturnLevel()==1)
                                {
                                    if(CloseCombatDefend_List[i]->ReturnIdentity()=="LiuShen")
                                    {
                                        ShuMorale=ShuMorale+160;
                                    }
                                    else if(CloseCombatDefend_List[i]->ReturnIdentity()=="ZhuGeZhan")
                                    {
                                        ShuMorale=ShuMorale+240;
                                    }
                                    else if(CloseCombatDefend_List[i]->ReturnIdentity()=="HanShen")
                                    {
                                        ShuMorale=ShuMorale+120;
                                    }
                                    else if(CloseCombatDefend_List[i]->ReturnIdentity()=="GuanXingZhangBao")
                                    {
                                         ShuMorale=ShuMorale+80;
                                    }
                                }
                                CloseCombatDefend_List.removeOne(CloseCombatDefend_List[i]);
                                it->tower_exist(false);
                                break;
                        }
                    }
                    break;
                }
                ++it;
            }
        }
        singleClicked=false;
    }
    if(Flag=="VermilionBirdScence")
    {
        if(event->button()==Qt::LeftButton)
        {
            QPoint MousePressCoordinate=event->pos();
            auto it=VermilionBirdScenceTower_List.begin();
            while(it!=VermilionBirdScenceTower_List.end())
            {
                if(WhetherWillRespond()&&it->inArea(MousePressCoordinate)&&!it->existence())
                {
                    if(Defend_Kind==" ")
                    {
                        if(ShuMorale>=150)
                        {
                            ShuMorale=ShuMorale-150;
                            it->tower_exist(true);
                            CloseCombatDefend *closeCombatDefend=new CloseCombatDefend(it->tower_centercoordinate(),this);
                            Defend_Kind=" ";
                            CloseCombatDefend_List.push_back(closeCombatDefend);
                            update();
                            break;
                        }
                    }
                    else if(Defend_Kind=="LiuShen")
                    {
                        if(ShuMorale>=200)
                        {
                            ShuMorale=ShuMorale-200;
                            it->tower_exist(true);
                            CloseCombatDefend *closeCombatDefend=new CloseCombatDefend(it->tower_centercoordinate(),this,1);
                            Defend_Kind=" ";
                            CloseCombatDefend_List.push_back(closeCombatDefend);
                            update();
                            break;
                        }
                    }
                    else if(Defend_Kind=="GuanXingZhangBao")
                    {
                        if(ShuMorale>=100)
                        {
                            ShuMorale=ShuMorale-100;
                            it->tower_exist(true);
                            CloseCombatDefend *closeCombatDefend=new CloseCombatDefend(it->tower_centercoordinate(),this,2);
                            Defend_Kind=" ";
                            CloseCombatDefend_List.push_back(closeCombatDefend);
                            update();
                            break;
                        }
                    }
                    else if(Defend_Kind=="HanShen")
                    {
                        if(ShuMorale>=150)
                        {
                            ShuMorale=ShuMorale-150;
                            it->tower_exist(true);
                            CloseCombatDefend *closeCombatDefend=new CloseCombatDefend(it->tower_centercoordinate(),this,3);
                            Defend_Kind=" ";
                            CloseCombatDefend_List.push_back(closeCombatDefend);
                            update();
                            break;
                        }
                    }
                    else if(Defend_Kind=="ZhuGeZhan")
                    {
                        if(ShuMorale>=300)
                        {
                            ShuMorale=ShuMorale-300;
                            it->tower_exist(true);
                            CloseCombatDefend *closeCombatDefend=new CloseCombatDefend(it->tower_centercoordinate(),this,4);
                            Defend_Kind=" ";
                            CloseCombatDefend_List.push_back(closeCombatDefend);
                            update();
                            break;
                        }
                    }

                }
                ++it;
            }
        }
        else if(event->button()==Qt::RightButton)
        {
            QPoint MousePressCoordinate=event->pos();
            auto it=VermilionBirdScenceTower_List.begin();
            while(it!=VermilionBirdScenceTower_List.end())
            {
                if(it->inArea(MousePressCoordinate)&&it->existence())
                {
                    for(int i=0;i<CloseCombatDefend_List.size();i++)
                    {
                        QPoint point=CloseCombatDefend_List[i]->Coordiante();
                        if(point==it->tower_centercoordinate())
                        {
                                CloseCombatDefend_List[i]->ReturnAppearSound()->stop();
                                CloseCombatDefend_List[i]->ReturnDeadSound()->play();
                                CloseCombatDefend_List[i]->StopAttackWeiSodier();
                                if(CloseCombatDefend_List[i]->ReturnLevel()==2)
                                {
                                    if(CloseCombatDefend_List[i]->ReturnIdentity()=="LiuBei")
                                    {
                                        ShuMorale=ShuMorale+560;
                                    }
                                    else if(CloseCombatDefend_List[i]->ReturnIdentity()=="ZhuGeLiang")
                                    {
                                        ShuMorale=ShuMorale+720;
                                    }
                                    else if(CloseCombatDefend_List[i]->ReturnIdentity()=="HanShen")
                                    {
                                        ShuMorale=ShuMorale+360;
                                    }
                                    else if(CloseCombatDefend_List[i]->ReturnIdentity()=="GuanYu")
                                    {
                                         ShuMorale=ShuMorale+400;
                                    }
                                    else if(CloseCombatDefend_List[i]->ReturnIdentity()=="ZhangFei")
                                    {
                                        ShuMorale=ShuMorale+400;
                                    }
                                }
                                else if(CloseCombatDefend_List[i]->ReturnLevel()==1)
                                {
                                    if(CloseCombatDefend_List[i]->ReturnIdentity()=="LiuShen")
                                    {
                                        ShuMorale=ShuMorale+160;
                                    }
                                    else if(CloseCombatDefend_List[i]->ReturnIdentity()=="ZhuGeZhan")
                                    {
                                        ShuMorale=ShuMorale+240;
                                    }
                                    else if(CloseCombatDefend_List[i]->ReturnIdentity()=="HanShen")
                                    {
                                        ShuMorale=ShuMorale+120;
                                    }
                                    else if(CloseCombatDefend_List[i]->ReturnIdentity()=="GuanXingZhangBao")
                                    {
                                         ShuMorale=ShuMorale+80;
                                    }
                                }
                                CloseCombatDefend_List.removeOne(CloseCombatDefend_List[i]);
                                it->tower_exist(false);
                                break;
                        }
                    }
                    break;
                }
                ++it;
            }
        }
        singleClicked=false;
    }
    if(Flag=="WhiteTigerScence")
    {
        if(event->button()==Qt::LeftButton)
        {
            QPoint MousePressCoordinate=event->pos();
            auto it=WhiteTigerScenceTower_List.begin();
            while(it!=WhiteTigerScenceTower_List.end())
            {
                if(WhetherWillRespond()&&it->inArea(MousePressCoordinate)&&!it->existence())
                {
                    if(Defend_Kind==" ")
                    {
                        if(ShuMorale>=150)
                        {
                            ShuMorale=ShuMorale-150;
                            it->tower_exist(true);
                            CloseCombatDefend *closeCombatDefend=new CloseCombatDefend(it->tower_centercoordinate(),this);
                            Defend_Kind=" ";
                            CloseCombatDefend_List.push_back(closeCombatDefend);
                            update();
                            break;
                        }
                    }
                    else if(Defend_Kind=="LiuShen")
                    {
                        if(ShuMorale>=200)
                        {
                            ShuMorale=ShuMorale-200;
                            it->tower_exist(true);
                            CloseCombatDefend *closeCombatDefend=new CloseCombatDefend(it->tower_centercoordinate(),this,1);
                            Defend_Kind=" ";
                            CloseCombatDefend_List.push_back(closeCombatDefend);
                            update();
                            break;
                        }
                    }
                    else if(Defend_Kind=="GuanXingZhangBao")
                    {
                        if(ShuMorale>=100)
                        {
                            ShuMorale=ShuMorale-100;
                            it->tower_exist(true);
                            CloseCombatDefend *closeCombatDefend=new CloseCombatDefend(it->tower_centercoordinate(),this,2);
                            Defend_Kind=" ";
                            CloseCombatDefend_List.push_back(closeCombatDefend);
                            update();
                            break;
                        }
                    }
                    else if(Defend_Kind=="HanShen")
                    {
                        if(ShuMorale>=150)
                        {
                            ShuMorale=ShuMorale-150;
                            it->tower_exist(true);
                            CloseCombatDefend *closeCombatDefend=new CloseCombatDefend(it->tower_centercoordinate(),this,3);
                            Defend_Kind=" ";
                            CloseCombatDefend_List.push_back(closeCombatDefend);
                            update();
                            break;
                        }
                    }
                    else if(Defend_Kind=="ZhuGeZhan")
                    {
                        if(ShuMorale>=300)
                        {
                            ShuMorale=ShuMorale-300;
                            it->tower_exist(true);
                            CloseCombatDefend *closeCombatDefend=new CloseCombatDefend(it->tower_centercoordinate(),this,4);
                            Defend_Kind=" ";
                            CloseCombatDefend_List.push_back(closeCombatDefend);
                            update();
                            break;
                        }
                    }

                }
                ++it;
            }
        }
        else if(event->button()==Qt::RightButton)
        {
            QPoint MousePressCoordinate=event->pos();
            auto it=WhiteTigerScenceTower_List.begin();
            while(it!=WhiteTigerScenceTower_List.end())
            {
                if(it->inArea(MousePressCoordinate)&&it->existence())
                {
                    for(int i=0;i<CloseCombatDefend_List.size();i++)
                    {
                        QPoint point=CloseCombatDefend_List[i]->Coordiante();
                        if(point==it->tower_centercoordinate())
                        {
                                CloseCombatDefend_List[i]->ReturnAppearSound()->stop();
                                CloseCombatDefend_List[i]->ReturnDeadSound()->play();
                                CloseCombatDefend_List[i]->StopAttackWeiSodier();
                                if(CloseCombatDefend_List[i]->ReturnLevel()==2)
                                {
                                    if(CloseCombatDefend_List[i]->ReturnIdentity()=="LiuBei")
                                    {
                                        ShuMorale=ShuMorale+560;
                                    }
                                    else if(CloseCombatDefend_List[i]->ReturnIdentity()=="ZhuGeLiang")
                                    {
                                        ShuMorale=ShuMorale+720;
                                    }
                                    else if(CloseCombatDefend_List[i]->ReturnIdentity()=="HanShen")
                                    {
                                        ShuMorale=ShuMorale+360;
                                    }
                                    else if(CloseCombatDefend_List[i]->ReturnIdentity()=="GuanYu")
                                    {
                                         ShuMorale=ShuMorale+400;
                                    }
                                    else if(CloseCombatDefend_List[i]->ReturnIdentity()=="ZhangFei")
                                    {
                                        ShuMorale=ShuMorale+400;
                                    }
                                }
                                else if(CloseCombatDefend_List[i]->ReturnLevel()==1)
                                {
                                    if(CloseCombatDefend_List[i]->ReturnIdentity()=="LiuShen")
                                    {
                                        ShuMorale=ShuMorale+160;
                                    }
                                    else if(CloseCombatDefend_List[i]->ReturnIdentity()=="ZhuGeZhan")
                                    {
                                        ShuMorale=ShuMorale+240;
                                    }
                                    else if(CloseCombatDefend_List[i]->ReturnIdentity()=="HanShen")
                                    {
                                        ShuMorale=ShuMorale+120;
                                    }
                                    else if(CloseCombatDefend_List[i]->ReturnIdentity()=="GuanXingZhangBao")
                                    {
                                         ShuMorale=ShuMorale+80;
                                    }
                                }
                                CloseCombatDefend_List.removeOne(CloseCombatDefend_List[i]);
                                it->tower_exist(false);
                                break;
                        }
                    }
                    break;
                }
                ++it;
            }
        }
        singleClicked=false;
    }
    }
}
//重写鼠标双击事件，召唤更为强大的蜀国英烈
void DifferentScence:: mouseDoubleClickEvent(QMouseEvent *event)
{
        mousetimer->stop();
        QPoint MousePressCoordinate=event->pos();
        if(Flag=="AzureDragonScence")
        {
        auto it=AzureDragonScenceTower_List.begin();
        while(it!=AzureDragonScenceTower_List.end())
        {
            if(WhetherWillRespond()&&it->inArea(MousePressCoordinate)&&it->existence())
            {
                for(int i=0;i<CloseCombatDefend_List.size();i++)
                {
                    QPoint point=CloseCombatDefend_List[i]->Coordiante();
                    if(point==it->tower_centercoordinate())
                    {
                        if(CloseCombatDefend_List[i]->ReturnLevel()==1)
                        {
                            if(CloseCombatDefend_List[i]->ReturnIdentity()=="LiuShen")
                            {
                                if(ShuMorale>=500)
                                {
                                ShuMorale=ShuMorale-500;
                                CloseCombatDefend_List[i]->UpgradeSpirit();
                                break;
                                }
                            }
                            else if(CloseCombatDefend_List[i]->ReturnIdentity()=="ZhuGeZhan")
                            {
                                if(ShuMorale>=600)
                                {
                                ShuMorale=ShuMorale-600;
                                CloseCombatDefend_List[i]->UpgradeSpirit();
                                break;
                                }
                            }
                            else if(CloseCombatDefend_List[i]->ReturnIdentity()=="HanShen")
                            {
                                if(ShuMorale>=300)
                                {
                                ShuMorale=ShuMorale-300;
                                CloseCombatDefend_List[i]->UpgradeSpirit();
                                break;
                                }
                            }
                            else if(CloseCombatDefend_List[i]->ReturnIdentity()=="GuanXingZhangBao")
                            {
                                if(ShuMorale>=400)
                                {
                                ShuMorale=ShuMorale-400;
                                CloseCombatDefend_List[i]->UpgradeSpirit();
                                break;
                                }
                            }
                        }
                    }
                }
                break;
            }
            ++it;
        }
        }
        else if(Flag=="BlackTortoiseScence")
        {
            auto it=BlackTortoiseScenceTower_List.begin();
            while(it!=BlackTortoiseScenceTower_List.end())
            {
                if(WhetherWillRespond()&&it->inArea(MousePressCoordinate)&&it->existence())
                {
                    for(int i=0;i<CloseCombatDefend_List.size();i++)
                    {
                        QPoint point=CloseCombatDefend_List[i]->Coordiante();
                        if(point==it->tower_centercoordinate())
                        {
                            if(CloseCombatDefend_List[i]->ReturnLevel()==1)
                            {
                                if(CloseCombatDefend_List[i]->ReturnIdentity()=="LiuShen")
                                {
                                    if(ShuMorale>=500)
                                    {
                                    ShuMorale=ShuMorale-500;
                                    CloseCombatDefend_List[i]->UpgradeSpirit();
                                    break;
                                    }
                                }
                                else if(CloseCombatDefend_List[i]->ReturnIdentity()=="ZhuGeZhan")
                                {
                                    if(ShuMorale>=600)
                                    {
                                    ShuMorale=ShuMorale-600;
                                    CloseCombatDefend_List[i]->UpgradeSpirit();
                                    break;
                                    }
                                }
                                else if(CloseCombatDefend_List[i]->ReturnIdentity()=="HanShen")
                                {
                                    if(ShuMorale>=300)
                                    {
                                    ShuMorale=ShuMorale-300;
                                    CloseCombatDefend_List[i]->UpgradeSpirit();
                                    break;
                                    }
                                }
                                else if(CloseCombatDefend_List[i]->ReturnIdentity()=="GuanXingZhangBao")
                                {
                                    if(ShuMorale>=400)
                                    {
                                    ShuMorale=ShuMorale-400;
                                    CloseCombatDefend_List[i]->UpgradeSpirit();
                                    break;
                                    }
                                }
                            }
                        }
                    }
                    break;
                }
                ++it;
            }
        }
        else if(Flag=="VermilionBirdScence")
        {
            auto it=VermilionBirdScenceTower_List.begin();
            while(it!=VermilionBirdScenceTower_List.end())
            {
                if(WhetherWillRespond()&&it->inArea(MousePressCoordinate)&&it->existence())
                {
                    for(int i=0;i<CloseCombatDefend_List.size();i++)
                    {
                        QPoint point=CloseCombatDefend_List[i]->Coordiante();
                        if(point==it->tower_centercoordinate())
                        {
                            if(CloseCombatDefend_List[i]->ReturnLevel()==1)
                            {
                                if(CloseCombatDefend_List[i]->ReturnIdentity()=="LiuShen")
                                {
                                    if(ShuMorale>=500)
                                    {
                                    ShuMorale=ShuMorale-500;
                                    CloseCombatDefend_List[i]->UpgradeSpirit();
                                    break;
                                    }
                                }
                                else if(CloseCombatDefend_List[i]->ReturnIdentity()=="ZhuGeZhan")
                                {
                                    if(ShuMorale>=600)
                                    {
                                    ShuMorale=ShuMorale-600;
                                    CloseCombatDefend_List[i]->UpgradeSpirit();
                                    break;
                                    }
                                }
                                else if(CloseCombatDefend_List[i]->ReturnIdentity()=="HanShen")
                                {
                                    if(ShuMorale>=300)
                                    {
                                    ShuMorale=ShuMorale-300;
                                    CloseCombatDefend_List[i]->UpgradeSpirit();
                                    break;
                                    }
                                }
                                else if(CloseCombatDefend_List[i]->ReturnIdentity()=="GuanXingZhangBao")
                                {
                                    if(ShuMorale>=400)
                                    {
                                    ShuMorale=ShuMorale-400;
                                    CloseCombatDefend_List[i]->UpgradeSpirit();
                                    break;
                                    }
                                }
                            }
                        }
                    }
                    break;
                }
                ++it;
            }

        }
        else if(Flag=="WhiteTigerScence")
        {
            auto it=WhiteTigerScenceTower_List.begin();
            while(it!=WhiteTigerScenceTower_List.end())
            {
                if(WhetherWillRespond()&&it->inArea(MousePressCoordinate)&&it->existence())
                {
                    for(int i=0;i<CloseCombatDefend_List.size();i++)
                    {
                        QPoint point=CloseCombatDefend_List[i]->Coordiante();
                        if(point==it->tower_centercoordinate())
                        {
                            if(CloseCombatDefend_List[i]->ReturnLevel()==1)
                            {
                                if(CloseCombatDefend_List[i]->ReturnIdentity()=="LiuShen")
                                {
                                    if(ShuMorale>=500)
                                    {
                                    ShuMorale=ShuMorale-500;
                                    CloseCombatDefend_List[i]->UpgradeSpirit();
                                    break;
                                    }
                                }
                                else if(CloseCombatDefend_List[i]->ReturnIdentity()=="ZhuGeZhan")
                                {
                                    if(ShuMorale>=600)
                                    {
                                    ShuMorale=ShuMorale-600;
                                    CloseCombatDefend_List[i]->UpgradeSpirit();
                                    break;
                                    }
                                }
                                else if(CloseCombatDefend_List[i]->ReturnIdentity()=="HanShen")
                                {
                                    if(ShuMorale>=300)
                                    {
                                    ShuMorale=ShuMorale-300;
                                    CloseCombatDefend_List[i]->UpgradeSpirit();
                                    break;
                                    }
                                }
                                else if(CloseCombatDefend_List[i]->ReturnIdentity()=="GuanXingZhangBao")
                                {
                                    if(ShuMorale>=400)
                                    {
                                    ShuMorale=ShuMorale-400;
                                    CloseCombatDefend_List[i]->UpgradeSpirit();
                                    break;
                                    }
                                }
                            }
                        }
                    }
                    break;
                }
                ++it;
            }

        }
}

//载入蜀军塔信息
void DifferentScence::LoadTowerCoordinate()
{
    if(Flag=="AzureDragonScence")
    {
        QPoint pos[13] =
        {
            QPoint(260, 20),
            QPoint(260, 250),
            QPoint(620,20),
            QPoint(620,250),
            QPoint(960,20),
            QPoint(960,250),
            QPoint(1250,150),
            QPoint(1250,500),
            QPoint(180,630),
            QPoint(620,630),
            QPoint(960,630),
            QPoint(620,900),
            QPoint(960,900)
//            QPoint(1340,630),
//            QPoint(1340,900)

        };
        for (int i = 0; i < 13; ++i)
            AzureDragonScenceTower_List.push_back(pos[i]);
    }
    else if(Flag=="BlackTortoiseScence")
    {
        QPoint pos[12] =
        {
            QPoint(210,800),
            QPoint(520,800),
            QPoint(210,500),
            QPoint(520,500),
            QPoint(210,260),
            QPoint(360,110),
            QPoint(620,110),
            QPoint(880,110),
            QPoint(1140,110),
//            QPoint(1330,800),
            QPoint(1330,500),
            QPoint(1330,260),
            QPoint(1000,500)
//            QPoint(1000,800)

        };
        for (int i = 0; i < 12; ++i)
            BlackTortoiseScenceTower_List.push_back(pos[i]);

    }
    else if(Flag=="VermilionBirdScence")
    {
        QPoint pos[17] =
        {
            QPoint(90,50),
            QPoint(305,50),
            QPoint(520,50),
            QPoint(90,340),
            QPoint(305,340),
            QPoint(90,580),
            QPoint(305,580),
            QPoint(90,880),
            QPoint(305,880),
            QPoint(650,330),
            QPoint(650,640),
            QPoint(900,330),
            QPoint(900,640),
            QPoint(1000,190),
            QPoint(1220,190),
            QPoint(1160,640),
//            QPoint(1400,640),
            QPoint(1300,330)
        };
        for (int i = 0; i < 17; ++i)
            VermilionBirdScenceTower_List.push_back(pos[i]);


    }
    else if(Flag=="WhiteTigerScence")
    {
        QPoint pos[16] =
        {
            QPoint(60,70),
            QPoint(340,70),
            QPoint(620,70),
            QPoint(60,350),
            QPoint(340,350),
            QPoint(60,560),
            QPoint(340,560),
            QPoint(60,860),
            QPoint(340,860),
            QPoint(620,860),
            QPoint(820,320),
            QPoint(1150,320),
            QPoint(820,600),
            QPoint(1150,600),
            QPoint(1480,320),
//            QPoint(1500,800),
//            QPoint(1210,800),
            QPoint(1500,600)
        };
        for (int i = 0; i < 16; ++i)
            WhiteTigerScenceTower_List.push_back(pos[i]);

    }


}
//载入魏军屯田点信息
void DifferentScence::LoadRoutePoint()
{
    if(Flag=="AzureDragonScence")
    {
        QPoint pos[6]=
        {
            QPoint(10,150),
            QPoint(1100,150),
            QPoint(1100,475),
            QPoint(300,475),
            QPoint(300,780),
            QPoint(1600,780)
        };

            RoutePoint *routepoint1=new RoutePoint(pos[0]);
            RoutePoint *routepoint2=new RoutePoint(pos[1]);
            RoutePoint *routepoint3=new RoutePoint(pos[2]);
            RoutePoint *routepoint4=new RoutePoint(pos[3]);
            RoutePoint *routepoint5=new RoutePoint(pos[4]);
            RoutePoint *routepoint6=new RoutePoint(pos[5]);
            routepoint1->SetNextRoutePoint(routepoint2);
            routepoint2->SetNextRoutePoint(routepoint3);
            routepoint3->SetNextRoutePoint(routepoint4);
            routepoint4->SetNextRoutePoint(routepoint5);
            routepoint5->SetNextRoutePoint(routepoint6);
            routepoint6->ChangPicture(200,100);
            AzureDragonScenceRoutePoint_List.push_back(routepoint1);
            AzureDragonScenceRoutePoint_List.push_back(routepoint2);
            AzureDragonScenceRoutePoint_List.push_back(routepoint3);
            AzureDragonScenceRoutePoint_List.push_back(routepoint4);
            AzureDragonScenceRoutePoint_List.push_back(routepoint5);
            AzureDragonScenceRoutePoint_List.push_back(routepoint6);

    }
    else if(Flag=="BlackTortoiseScence")
    {
        QPoint pos[4]=
        {
            QPoint(350,930),
            QPoint(350,250),
            QPoint(1160,250),
            QPoint(1160,1000)
        };
        RoutePoint *routepoint1=new RoutePoint(pos[0]);
        RoutePoint *routepoint2=new RoutePoint(pos[1]);
        RoutePoint *routepoint3=new RoutePoint(pos[2]);
        RoutePoint *routepoint4=new RoutePoint(pos[3]);
        routepoint1->SetNextRoutePoint(routepoint2);
        routepoint2->SetNextRoutePoint(routepoint3);
        routepoint3->SetNextRoutePoint(routepoint4);
        routepoint4->ChangPicture(59,250);
        BlackTortoiseScenceRoutePoint_List.push_back(routepoint1);
        BlackTortoiseScenceRoutePoint_List.push_back(routepoint2);
        BlackTortoiseScenceRoutePoint_List.push_back(routepoint3);
        BlackTortoiseScenceRoutePoint_List.push_back(routepoint4);
    }
    else if(Flag=="VermilionBirdScence")
    {    QPoint pos[8]=
        {
            QPoint(5,180),
            QPoint(5,720),
            QPoint(510,180),
            QPoint(510,720),
            QPoint(510,480),
            QPoint(1100,480),
            QPoint(1100,5),
            QPoint(1600,480)
        };
        RoutePoint *routepoint1=new RoutePoint(pos[0]);
        RoutePoint *routepoint2=new RoutePoint(pos[1]);
        RoutePoint *routepoint3=new RoutePoint(pos[2]);
        RoutePoint *routepoint4=new RoutePoint(pos[3]);
        RoutePoint *routepoint5=new RoutePoint(pos[4]);
        RoutePoint *routepoint6=new RoutePoint(pos[5]);
        RoutePoint *routepoint7=new RoutePoint(pos[6]);
        RoutePoint *routepoint8=new RoutePoint(pos[7]);
        routepoint1->SetNextRoutePoint(routepoint3);
        routepoint3->SetNextRoutePoint(routepoint5);
        routepoint5->SetNextRoutePoint(routepoint6);
        routepoint2->SetNextRoutePoint(routepoint4);
        routepoint4->SetNextRoutePoint(routepoint5);
        routepoint6->SetNextRoutePoint(routepoint8);
        routepoint7->SetNextRoutePoint(routepoint6);
        routepoint8->ChangPicture(200,120);
        VermilionBirdScenceRoutePoint_List.push_back(routepoint1);
        VermilionBirdScenceRoutePoint_List.push_back(routepoint2);
        VermilionBirdScenceRoutePoint_List.push_back(routepoint3);
        VermilionBirdScenceRoutePoint_List.push_back(routepoint4);
        VermilionBirdScenceRoutePoint_List.push_back(routepoint5);
        VermilionBirdScenceRoutePoint_List.push_back(routepoint6);
        VermilionBirdScenceRoutePoint_List.push_back(routepoint7);
        VermilionBirdScenceRoutePoint_List.push_back(routepoint8);

    }
    else if(Flag=="WhiteTigerScence")
    {    QPoint pos[8]=
        {
            QPoint(5,200),
            QPoint(5,700),
            QPoint(630,200),
            QPoint(630,700),
            QPoint(630,470),
            QPoint(1340,470),
            QPoint(1340,1000)
        };
        RoutePoint *routepoint1=new RoutePoint(pos[0]);
        RoutePoint *routepoint2=new RoutePoint(pos[1]);
        RoutePoint *routepoint3=new RoutePoint(pos[2]);
        RoutePoint *routepoint4=new RoutePoint(pos[3]);
        RoutePoint *routepoint5=new RoutePoint(pos[4]);
        RoutePoint *routepoint6=new RoutePoint(pos[5]);
        RoutePoint *routepoint7=new RoutePoint(pos[6]);
        routepoint1->SetNextRoutePoint(routepoint3);
        routepoint2->SetNextRoutePoint(routepoint4);
        routepoint3->SetNextRoutePoint(routepoint5);
        routepoint4->SetNextRoutePoint(routepoint5);
        routepoint5->SetNextRoutePoint(routepoint6);
        routepoint6->SetNextRoutePoint(routepoint7);
        routepoint7->ChangPicture(45,220);
        WhiteTigerScenceRoutePoint_List.push_back(routepoint1);
        WhiteTigerScenceRoutePoint_List.push_back(routepoint2);
        WhiteTigerScenceRoutePoint_List.push_back(routepoint3);
        WhiteTigerScenceRoutePoint_List.push_back(routepoint4);
        WhiteTigerScenceRoutePoint_List.push_back(routepoint5);
        WhiteTigerScenceRoutePoint_List.push_back(routepoint6);
        WhiteTigerScenceRoutePoint_List.push_back(routepoint7);
    }
}
//蜀国的先烈是否会响应召唤
bool DifferentScence::WhetherWillRespond() const
{
    if(ShuMorale>=100)
    {
        return true;
    }
    else
    {
        return false;
    }
}
void DifferentScence::ForceWarLose()
{
    WarLose=true;
}

//魏军进攻成都
void DifferentScence::AttackChengdu(int damage)
{
    srand(int(time(0)));
    int judge=rand()%3+1;
    if(judge==1)
    {
        GetDamage1->play();
    }
    else if(judge==2)
    {
        GetDamage2->play();
    }
    else if(judge==3)
    {
        GetDamage3->play();
    }
    ChengDuCitizenry=ChengDuCitizenry-damage;
    if(ChengDuCitizenry<=0)
    {
        ForceWarLose();
    }
}
//载入魏军批数
bool DifferentScence::LoadBatch()
{
    srand(time(0));
    if(WeiSodier_Batch>=Batch+1)
    {
        return false;
    }
    if(Flag=="AzureDragonScence")
    {
        sleep(10000);//每轮开始前留给玩家10s时间准备
        RoutePoint *StartRoutePoint=AzureDragonScenceRoutePoint_List[0];
        if(WeiSodier_Batch<Batch)
        {
            int Interval=2000;
            int Number=9+WeiSodier_Batch;
        for(int i=0;i<Number;i++)
        {
            WeiSodier *weiSodier=new WeiSodier(*StartRoutePoint,this);
            weiSodier->ChangeWeiSodier(1);
            for(int j=0;j<Cout;j++)
            {
                weiSodier->StrengthWeiSodier();
            }
            WeiSodier_List.push_back(weiSodier);
            QTimer::singleShot(Interval*i,weiSodier,SLOT(OrderActive()));
        }
        }
        else
        {
            int Interval=2000;
            int Number=9+WeiSodier_Batch;
        for(int i=0;i<Number;i++)
        {
            WeiSodier *weiSodier=new WeiSodier(*StartRoutePoint,this);
            if(i==Number-1)
            {
                weiSodier->ChangeWeiSodier(2);
                for(int j=0;j<Cout;j++)
                {
                    weiSodier->StrengthWeiSodier();
                }
                WeiSodier_List.push_back(weiSodier);
                QTimer::singleShot(Interval*i,weiSodier,SLOT(OrderActive()));
            }
            else if(i==Number-2)
            {
                weiSodier->ChangeWeiSodier(3);
                for(int j=0;j<Cout;j++)
                {
                    weiSodier->StrengthWeiSodier();
                }
                WeiSodier_List.push_back(weiSodier);
                QTimer::singleShot(Interval*i,weiSodier,SLOT(OrderActive()));

            }
            else
            {
                weiSodier->ChangeWeiSodier(1);
                for(int j=0;j<Cout;j++)
                {
                    weiSodier->StrengthWeiSodier();
                }
                WeiSodier_List.push_back(weiSodier);
                QTimer::singleShot(Interval*i,weiSodier,SLOT(OrderActive()));

            }
        }

        }
    return  true;
    }
    else if(Flag=="BlackTortoiseScence")
    {
        sleep(10000);//每轮开始前留给玩家10s时间准备
        RoutePoint *StartRoutePoint=BlackTortoiseScenceRoutePoint_List[0];
        if(WeiSodier_Batch<Batch)
        {
            int Interval=2000;
            int Number=8+WeiSodier_Batch;
        for(int i=0;i<Number;i++)
        {
            WeiSodier *weiSodier=new WeiSodier(*StartRoutePoint,this);
            weiSodier->ChangeWeiSodier(1);
            for(int j=0;j<Cout;j++)
            {
                weiSodier->StrengthWeiSodier();
            }
            WeiSodier_List.push_back(weiSodier);
            QTimer::singleShot(Interval*i,weiSodier,SLOT(OrderActive()));
        }
        }
        else
        {
            int Interval=2000;
            int Number=8+WeiSodier_Batch;
        for(int i=0;i<Number;i++)
        {
            WeiSodier *weiSodier=new WeiSodier(*StartRoutePoint,this);
            if(i==Number-1)
            {
                weiSodier->ChangeWeiSodier(2);
                for(int j=0;j<Cout;j++)
                {
                    weiSodier->StrengthWeiSodier();
                }
                WeiSodier_List.push_back(weiSodier);
                QTimer::singleShot(Interval*i,weiSodier,SLOT(OrderActive()));
            }
            else if(i==Number-2)
            {
                weiSodier->ChangeWeiSodier(3);
                for(int j=0;j<Cout;j++)
                {
                    weiSodier->StrengthWeiSodier();
                }
                WeiSodier_List.push_back(weiSodier);
                QTimer::singleShot(Interval*i,weiSodier,SLOT(OrderActive()));

            }
            else if(i==Number-2)
            {
                weiSodier->ChangeWeiSodier(3);
                for(int j=0;j<Cout;j++)
                {
                    weiSodier->StrengthWeiSodier();
                }
                WeiSodier_List.push_back(weiSodier);
                QTimer::singleShot(Interval*i,weiSodier,SLOT(OrderActive()));
            }
            else
            {
                weiSodier->ChangeWeiSodier(1);
                for(int j=0;j<Cout;j++)
                {
                    weiSodier->StrengthWeiSodier();
                }
                WeiSodier_List.push_back(weiSodier);
                QTimer::singleShot(Interval*i,weiSodier,SLOT(OrderActive()));

            }
        }

        }
    return  true;
    }
    else if(Flag=="VermilionBirdScence")
    {
        sleep(10000);//每轮开始前留给玩家10s时间准备
        int standard=Batch/2;
        RoutePoint *StartRoutePoint=VermilionBirdScenceRoutePoint_List[0];
        RoutePoint *StartRoutePoint2=VermilionBirdScenceRoutePoint_List[1];
        RoutePoint *StartRoutePoint3=VermilionBirdScenceRoutePoint_List[6];
        if(WeiSodier_Batch>standard)
        {
            if(WeiSodier_Batch==Batch)
            {
            int Interval=2000;
            int Number=5+WeiSodier_Batch;
        for(int i=0;i<Number;i++)
        {
            WeiSodier *weiSodier3=new WeiSodier(*StartRoutePoint3,this);
            if(i==Number-1)
            {
                weiSodier3->ChangeWeiSodier(3);
                for(int j=0;j<Cout;j++)
                {
                    weiSodier3->StrengthWeiSodier();
                }
                WeiSodier_List.push_back(weiSodier3);
                QTimer::singleShot(Interval*i,weiSodier3,SLOT(OrderActive()));
            }
            else
            {
                weiSodier3->ChangeWeiSodier(1);
                for(int j=0;j<Cout;j++)
                {
                    weiSodier3->StrengthWeiSodier();
                }
                WeiSodier_List.push_back(weiSodier3);
                QTimer::singleShot(Interval*i,weiSodier3,SLOT(OrderActive()));
            }
        }
            }
            else
            {
                int Interval=2000;
                int Number=5+WeiSodier_Batch;
            for(int i=0;i<Number;i++)
            {
                WeiSodier *weiSodier=new WeiSodier(*StartRoutePoint3,this);
                weiSodier->ChangeWeiSodier(1);
                for(int j=0;j<Cout;j++)
                {
                    weiSodier->StrengthWeiSodier();
                }
                WeiSodier_List.push_back(weiSodier);
                QTimer::singleShot(Interval*i,weiSodier,SLOT(OrderActive()));

            }
            }
        }
        if(WeiSodier_Batch<Batch)
        {
            int Interval=2000;
            int Number=5+WeiSodier_Batch;
        for(int i=0;i<Number;i++)
        {
            WeiSodier *weiSodier=new WeiSodier(*StartRoutePoint,this);
            WeiSodier *weiSodier2=new WeiSodier(*StartRoutePoint2,this);
            weiSodier->ChangeWeiSodier(1);
            weiSodier2->ChangeWeiSodier(1);
            for(int j=0;j<Cout;j++)
            {
                weiSodier->StrengthWeiSodier();
                weiSodier2->StrengthWeiSodier();
            }
            WeiSodier_List.push_back(weiSodier);
            WeiSodier_List.push_back(weiSodier2);
            QTimer::singleShot(Interval*i,weiSodier,SLOT(OrderActive()));
            QTimer::singleShot(Interval*i,weiSodier2,SLOT(OrderActive()));
        }
        }
        else
        {
            int Interval=2000;
            int Number=5+WeiSodier_Batch;
        for(int i=0;i<Number;i++)
        {
            WeiSodier *weiSodier=new WeiSodier(*StartRoutePoint,this);
            WeiSodier *weiSodier2=new WeiSodier(*StartRoutePoint2,this);
            if(i==Number-1)
            {
                weiSodier->ChangeWeiSodier(2);
                weiSodier2->ChangeWeiSodier(2);
                for(int j=0;j<Cout;j++)
                {
                    weiSodier->StrengthWeiSodier();
                    weiSodier2->StrengthWeiSodier();
                }
                WeiSodier_List.push_back(weiSodier);
                WeiSodier_List.push_back(weiSodier2);
                QTimer::singleShot(Interval*i,weiSodier,SLOT(OrderActive()));
                QTimer::singleShot(Interval*i,weiSodier2,SLOT(OrderActive()));
            }
            else
            {
                weiSodier->ChangeWeiSodier(1);
                weiSodier2->ChangeWeiSodier(1);
                for(int j=0;j<Cout;j++)
                {
                    weiSodier->StrengthWeiSodier();
                    weiSodier2->StrengthWeiSodier();
                }
                WeiSodier_List.push_back(weiSodier);
                WeiSodier_List.push_back(weiSodier2);
                QTimer::singleShot(Interval*i,weiSodier,SLOT(OrderActive()));
                QTimer::singleShot(Interval*i,weiSodier2,SLOT(OrderActive()));

            }
        }

        }
    return  true;
    }
    else if(Flag=="WhiteTigerScence")
    {
        sleep(10000);//每轮开始前留给玩家10s时间准备
        RoutePoint *StartRoutePoint=WhiteTigerScenceRoutePoint_List[0];
        RoutePoint *StartRoutePoint2=WhiteTigerScenceRoutePoint_List[1];
        if(WeiSodier_Batch<Batch)
        {
            int Interval=2000;
            int Number=5+WeiSodier_Batch;
        for(int i=0;i<Number;i++)
        {
            WeiSodier *weiSodier=new WeiSodier(*StartRoutePoint,this);
            weiSodier->ChangeWeiSodier(1);
            for(int j=0;j<Cout;j++)
            {
                weiSodier->StrengthWeiSodier();
            }
            WeiSodier_List.push_back(weiSodier);
            QTimer::singleShot(Interval*i,weiSodier,SLOT(OrderActive()));
            WeiSodier *weiSodier2=new WeiSodier(*StartRoutePoint2,this);
            weiSodier2->ChangeWeiSodier(1);
            for(int j=0;j<Cout;j++)
            {
                weiSodier2->StrengthWeiSodier();
            }
            WeiSodier_List.push_back(weiSodier2);
            QTimer::singleShot(Interval*i,weiSodier2,SLOT(OrderActive()));
        }
        }
        else
        {
            int Interval=2000;
            int Number=5+WeiSodier_Batch;
        for(int i=0;i<Number;i++)
        {
            WeiSodier *weiSodier=new WeiSodier(*StartRoutePoint,this);
            WeiSodier *weiSodier2=new WeiSodier(*StartRoutePoint2,this);
            if(i==Number-1)
            {
                weiSodier->ChangeWeiSodier(2);
                weiSodier2->ChangeWeiSodier(3);
                for(int j=0;j<Cout;j++)
                {
                    weiSodier->StrengthWeiSodier();
                    weiSodier2->StrengthWeiSodier();
                }
                WeiSodier_List.push_back(weiSodier);
                WeiSodier_List.push_back(weiSodier2);
                QTimer::singleShot(Interval*i,weiSodier,SLOT(OrderActive()));
                QTimer::singleShot(Interval*i,weiSodier2,SLOT(OrderActive()));
            }
            else
            {
                weiSodier->ChangeWeiSodier(1);
                weiSodier2->ChangeWeiSodier(1);
                for(int j=0;j<Cout;j++)
                {
                    weiSodier->StrengthWeiSodier();
                    weiSodier2->StrengthWeiSodier();
                }
                WeiSodier_List.push_back(weiSodier);
                WeiSodier_List.push_back(weiSodier2);
                QTimer::singleShot(Interval*i,weiSodier,SLOT(OrderActive()));
                QTimer::singleShot(Interval*i,weiSodier2,SLOT(OrderActive()));

            }
        }

        }
    return  true;
    }
    return true;
}

//移除魏军
void DifferentScence::destroyWeiSodier(WeiSodier *weiSodier)
{
   Q_ASSERT(weiSodier);
    WeiSodier_List.removeOne(weiSodier);
    delete weiSodier;
    if(WeiSodier_List.empty())
    {
        ++WeiSodier_Batch;
        if(!LoadBatch())
        {
            WarWin=true;
        }
    }

}
//增添特效
void DifferentScence::AddEfficacy(Efficacy *efficacy)
{
    Q_ASSERT(efficacy);
    Efficacy_List.push_back(efficacy);
}

//移除特效
void DifferentScence::destroyEfficacy(Efficacy *efficacy)
{
    Q_ASSERT(efficacy);
    Efficacy_List.removeOne(efficacy);
    delete efficacy;
}
//增添风
void DifferentScence::AddWind(Wind *wind)
{
    Q_ASSERT(wind);
    Wind_List.push_back(wind);
}
//移除风
void DifferentScence::destroyWind(Wind *wind)
{
    Q_ASSERT(wind);
    Wind_List.removeOne(wind);
    delete wind;
}
//更新地图模拟帧数
void DifferentScence::RenewMap()
{
    foreach (WeiSodier *weiSodier,WeiSodier_List)
    {
        weiSodier->march();
    }
    foreach (CloseCombatDefend *closeCombatDefend,CloseCombatDefend_List)
    {
        closeCombatDefend->CheckWeiSodierInRange();
    }
    update();
}
//返回魏军管理信息
QList<WeiSodier *> DifferentScence::WeiSodier_list()
{
    return WeiSodier_List;
}
//战争开始
void DifferentScence::WarBegin()
{
LoadBatch();
}
//击杀魏军后，增加蜀军士气，可以召唤更多的蜀国英烈
void DifferentScence::AddMorale(int Morale)
{
    ShuMorale=ShuMorale+Morale;
    update();
}
//画出魏军批数
void DifferentScence::DrawBatch(QPainter *Painter)
{
    QFont Font("宋体",15,QFont::Bold,true);
    Painter->setFont(Font);
    Painter->setPen(Qt::red);
    Painter->drawText(QRect(1350,5,300,300), QString("魏军批数:%1").arg(WeiSodier_Batch));
    if(IsEndless==true)
    {
        Painter->drawText(QRect(1530,5,300,300), QString("/∞"));
    }
    else
    {
    Painter->drawText(QRect(1530,5,300,300), QString("/%1").arg(Batch));
    }
}
//画出成都民心
void DifferentScence::DrawChengDuCitizenry(QPainter *Painter)
{
    QFont Font("宋体",15,QFont::Bold,true);
    Painter->setFont(Font);
    Painter->setPen(Qt::red);
    Painter->drawText(QRect(1350,60,300,300), QString("成都民心:%1").arg(ChengDuCitizenry));
}
//画出蜀军士气
void DifferentScence::DrawShuMorale(QPainter *Painter)
{
    QFont Font("宋体",15,QFont::Bold,true);
    Painter->setFont(Font);
    Painter->setPen(Qt::red);
    Painter->drawText(QRect(1350,110,300,300), QString("蜀军士气:%1").arg(ShuMorale));
}
//槽函数
void DifferentScence::mouseClick()
{
    singleClicked=true;
}
//返回背景音乐
QSound* DifferentScence::ReturnScenceSound()
{
    return ScenceSound;
}
//返回增强魏军能力的计时器
QTimer* DifferentScence::ReturnWeiTimer()
{
    return WeiSodier_Timer;
}
//返回增强蜀军能力的计时器
QTimer* DifferentScence::ReturnLiuTimer()
{
    return Liu_Timer;
}
//返回在场刘备数目
int DifferentScence::ReturnCoutLiuBei()
{
    return CoutLiuBei-CoutLiuBeiRecord;
}
//返回在场刘谌数目
int DifferentScence::ReturnCoutLiuShen()
{
    return CoutLiuShen-CoutLiuShenRecord;
}
//增加总批数
void DifferentScence::AddBatch()
{
    Batch++;
}
//增加当前批数
void DifferentScence::AddCurrentBatch()
{
    int Standard=WeiSodier_Batch+1;
    if(Standard>Batch)
        return;
    else
    {
        WeiSodier_Batch=WeiSodier_Batch+1;
    }
}
//减少总批数
void DifferentScence::DecreaseBatch()
{
    int Standard=Batch-1;
    if(Standard<WeiSodier_Batch||Standard<0)
        return;
    else
    {
        Batch=Batch-1;
    }
}
//减少当前批数
void DifferentScence::DecreaseCurrentBatch()
{
    int Standard=WeiSodier_Batch-1;
    if(Standard<1)
    {
        return;
    }
    else
    {
        WeiSodier_Batch=WeiSodier_Batch-1;
    }
}
//变为无尽模式
void DifferentScence::Endless()
{
    Batch=999999999;
    IsEndless=true;
}
//强制转化类型
void DifferentScence::ChangeKind(QString kind)
{
    Defend_Kind=kind;
}

