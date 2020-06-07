#include "differentscence.h"
#include "closecombatdefend.h"
#include "tower.h"
#include "routepoint.h"
#include "weisodier.h"
#include <QPainter>
#include <QPixmap>
#include <QIcon>
#include <QPoint>
#include <QList>
#include <QDebug>
#include <QString>
#include <QTimer>
#include <QObject>
//构造函数的实现
DifferentScence::DifferentScence(QWidget *parent) :
    QWidget(parent),
    WeiSodier_Batch(0)
{
    setWindowIcon(QIcon(":/logo/logo.png"));
    this->setFixedSize(1600,1000);
    setWindowTitle("蜀汉悲歌");
    QTimer *timer=new QTimer(this);
    connect(timer,&QTimer::timeout,this,&DifferentScence::RenewMap);
    timer->start(30);
}
//传入选关信号
void DifferentScence::ChangeScence(QString flag)
{
    Flag=flag;
    LoadTowerCoordinate();
    LoadRoutePoint();
    LoadBatch();
}
//重写绘画事件(载入图片)
void DifferentScence::paintEvent(QPaintEvent *)
{
    //加载选关背景
    //青龙关
    if(Flag=="AzureDragonScence")
    {
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

    }
    //玄武关
    else if(Flag=="BlackTortoiseScence")
    {
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
    foreach(const RoutePoint &routePoint,BlackTortoiseScenceRoutePoint_List)
    {
    routePoint.draw(&painter);
    }
    }
    //朱雀关
    else if(Flag=="VermilionBirdScence")
    {
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
    foreach(const RoutePoint &routePoint,VermilionBirdScenceRoutePoint_List)
    {
    routePoint.draw(&painter);
    }
    }
    //白虎关
    else if(Flag=="WhiteTigerScence")
    {
    QPixmap pix;
    pix.load(":/background/White TigerScence.jpg");
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
    foreach(const RoutePoint &routePoint,WhiteTigerScenceRoutePoint_List)
    {
    routePoint.draw(&painter);
    }
    }
}
//重写鼠标点击事件(安装塔防)
void DifferentScence::mousePressEvent(QMouseEvent *event)
{
    if(Flag=="AzureDragonScence")
    {
        QPoint MousePressCoordinate=event->pos();
        auto it=AzureDragonScenceTower_List.begin();
        while(it!=AzureDragonScenceTower_List.end())
        {
            if(WhetherCanBuy()&&it->inArea(MousePressCoordinate)&&!it->existence())
            {
                it->tower_exist();
                it->tower_exist(true);
                CloseCombatDefend *closeCombatDefend=new CloseCombatDefend(it->tower_centercoordinate(),this);
                CloseCombatDefend_List.push_back(closeCombatDefend);
                update();
                break;
            }
            ++it;
        }
    }
    else if(Flag=="BlackTortoiseScence")
    {
        QPoint MousePressCoordinate=event->pos();
        auto it=BlackTortoiseScenceTower_List.begin();
        while(it!=BlackTortoiseScenceTower_List.end())
        {
            if(WhetherCanBuy()&&it->inArea(MousePressCoordinate)&&!it->existence())
            {
                it->tower_exist();
                it->tower_exist(true);
                CloseCombatDefend *closeCombatDefend=new CloseCombatDefend(it->tower_centercoordinate(),this);
                CloseCombatDefend_List.push_back(closeCombatDefend);
                update();
                break;
            }
            ++it;
        }
    }
    else if(Flag=="VermilionBirdScence")
    {
        QPoint MousePressCoordinate=event->pos();
        auto it=VermilionBirdScenceTower_List.begin();
        while(it!=VermilionBirdScenceTower_List.end())
        {
            if(WhetherCanBuy()&&it->inArea(MousePressCoordinate)&&!it->existence())
            {
                it->tower_exist();
                CloseCombatDefend *closeCombatDefend=new CloseCombatDefend(it->tower_centercoordinate(),this);
                CloseCombatDefend_List.push_back(closeCombatDefend);
                update();
                break;
            }
            ++it;
        }
    }
    else if(Flag=="WhiteTigerScence")
    {
        QPoint MousePressCoordinate=event->pos();
        auto it=WhiteTigerScenceTower_List.begin();
        while(it!=WhiteTigerScenceTower_List.end())
        {
            if(WhetherCanBuy()&&it->inArea(MousePressCoordinate)&&!it->existence())
            {
                it->tower_exist();
                CloseCombatDefend *closeCombatDefend=new CloseCombatDefend(it->tower_centercoordinate(),this);
                CloseCombatDefend_List.push_back(closeCombatDefend);
                update();
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
        QPoint pos[15] =
        {
            QPoint(260, 20),
            QPoint(260, 315),
            QPoint(620,20),
            QPoint(620,315),
            QPoint(960,20),
            QPoint(960,315),
            QPoint(1250,150),
            QPoint(1250,500),
            QPoint(180,630),
            QPoint(620,630),
            QPoint(960,630),
            QPoint(620,900),
            QPoint(960,900),
            QPoint(1340,630),
            QPoint(1340,900)

        };
        for (int i = 0; i < 15; ++i)
            AzureDragonScenceTower_List.push_back(pos[i]);
    }
    else if(Flag=="BlackTortoiseScence")
    {
        QPoint pos[14] =
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
            QPoint(1330,800),
            QPoint(1330,500),
            QPoint(1330,260),
            QPoint(1000,500),
            QPoint(1000,800)

        };
        for (int i = 0; i < 14; ++i)
            BlackTortoiseScenceTower_List.push_back(pos[i]);

    }
    else if(Flag=="VermilionBirdScence")
    {
        QPoint pos[18] =
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
            QPoint(1400,640),
            QPoint(1300,330)
        };
        for (int i = 0; i < 18; ++i)
            VermilionBirdScenceTower_List.push_back(pos[i]);


    }
    else if(Flag=="WhiteTigerScence")
    {
        QPoint pos[18] =
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
            QPoint(1500,800),
            QPoint(1210,800),
            QPoint(1500,600)
        };
        for (int i = 0; i < 18; ++i)
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
            QPoint(1510,780)
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
            QPoint(1160,930)
        };
        for(int i=0;i<4;++i)
        {
            RoutePoint point(pos[i]);
            BlackTortoiseScenceRoutePoint_List.push_back(point);
        }
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
            QPoint(1510,480)
        };
        for(int i=0;i<8;++i)
        {
            RoutePoint point(pos[i]);
            VermilionBirdScenceRoutePoint_List.push_back(point);
        }

    }
    else if(Flag=="WhiteTigerScence")
    {    QPoint pos[7]=
        {
            QPoint(5,200),
            QPoint(5,700),
            QPoint(630,200),
            QPoint(630,700),
            QPoint(630,470),
            QPoint(1340,470),
            QPoint(1340,930)
        };
        for(int i=0;i<7;++i)
        {
            RoutePoint point(pos[i]);
            WhiteTigerScenceRoutePoint_List.push_back(point);
        }

    }
}
//判断是否能购买塔防
bool DifferentScence::WhetherCanBuy() const
{
    return true;
}
//魏军进攻成都
void DifferentScence::AttackChengdu(int damage)
{
}
//载入魏军批数
bool DifferentScence::LoadBatch()
{
    if(Flag=="AzureDragonScence")
    {
    RoutePoint *StartRoutePoint=AzureDragonScenceRoutePoint_List[0];
//    QPoint Coordinate=AzureDragonScenceRoutePoint_List[0].Coordinate()+QPoint(-15,-30);
//    StartRoutePoint->SetCoordinate(Coordinate);
//    for(int i=0;i<7;i++)
//    {
        WeiSodier *weiSodier=new WeiSodier(*StartRoutePoint,this);
        WeiSodier_List.push_back(weiSodier);
//        weiSodier->march();
//            update();
//    }
    }
    else if(Flag=="BlackTortoiseScence")
    {

    }
    else if(Flag=="VermilionBirdScence")
    {

    }
    else if(Flag=="WhiteTigerScence")
    {

    }
}

//移除魏军
void DifferentScence::destroyWeiSodier(WeiSodier *weiSodier)
{
//   Q_ASSERT(weiSodier);
//    WeiSodier_List.removeOne(weiSodier);
//    delete weiSodier;
//    if(WeiSodier_List.empty())
//    {
//    }

}
//更新地图模拟帧数
void DifferentScence::RenewMap()
{
    foreach (WeiSodier *weiSodier,WeiSodier_List)
    {
        weiSodier->march();
        update();
    }
}
