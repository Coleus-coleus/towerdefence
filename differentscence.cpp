#include "differentscence.h"
#include "closecombatdefend.h"
#include "tower.h"
#include "routepoint.h"
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
    connect(timer,SIGNAL(timeout()),this,SLOT(RenewMap()));
    timer->start(30);
}
//传入选关信号
void DifferentScence::ChangeScence(QString flag)
{
    Flag=flag;
}
//重写绘画事件(载入图片)
void DifferentScence::paintEvent(QPaintEvent *)
{
    //加载选关背景
    LoadTowerCoordinate();
    LoadRoutePoint();
    bool LoadBatch();//载入批数信息
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
    foreach(const RoutePoint &routePoint,AzureDragonScenceRoutePoint_List)
    {
        routePoint.draw(&painter);
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
    QPoint MousePressCoordinate=event->pos();
    if(Flag=="AzureDragonScence")
    {
        auto it=AzureDragonScenceTower_List.begin();
        while(it!=AzureDragonScenceTower_List.end())
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
    else if(Flag=="BlackTortoiseScence")
    {
        auto it=BlackTortoiseScenceTower_List.begin();
        while(it!=BlackTortoiseScenceTower_List.end())
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
    else if(Flag=="VermilionBirdScence")
    {
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
        QPoint pos[12] =
        {
            QPoint(350, 220),
            QPoint(750, 220),
            QPoint(1150, 220),
            QPoint(1550, 220),

            QPoint(100, 125),
            QPoint(195, 125),
            QPoint(280, 125),
            QPoint(370, 125),

            QPoint(80, 35),
            QPoint(170, 35),
            QPoint(260, 35),
            QPoint(350, 35)
        };
        for (int i = 0; i < 12; ++i)
            AzureDragonScenceTower_List.push_back(pos[i]);
    }
    else if(Flag=="BlackTortoiseScence")
    {
        QPoint pos[12] =
        {
            QPoint(350, 220),
            QPoint(750, 220),
            QPoint(1150, 220),
            QPoint(1550, 220),

            QPoint(100, 125),
            QPoint(195, 125),
            QPoint(280, 125),
            QPoint(370, 125),

            QPoint(80, 35),
            QPoint(170, 35),
            QPoint(260, 35),
            QPoint(350, 35)
        };
        for (int i = 0; i < 12; ++i)
            BlackTortoiseScenceTower_List.push_back(pos[i]);

    }
    else if(Flag=="VermilionBirdScence")
    {
        QPoint pos[12] =
        {
            QPoint(350, 220),
            QPoint(750, 220),
            QPoint(1150, 220),
            QPoint(1550, 220),

            QPoint(100, 125),
            QPoint(195, 125),
            QPoint(280, 125),
            QPoint(370, 125),

            QPoint(80, 35),
            QPoint(170, 35),
            QPoint(260, 35),
            QPoint(350, 35)
        };
        for (int i = 0; i < 12; ++i)
            VermilionBirdScenceTower_List.push_back(pos[i]);


    }
    else if(Flag=="WhiteTigerScence")
    {
        QPoint pos[12] =
        {
            QPoint(350, 220),
            QPoint(750, 220),
            QPoint(1150, 220),
            QPoint(1550, 220),

            QPoint(100, 125),
            QPoint(195, 125),
            QPoint(280, 125),
            QPoint(370, 125),

            QPoint(80, 35),
            QPoint(170, 35),
            QPoint(260, 35),
            QPoint(350, 35)
        };
        for (int i = 0; i < 12; ++i)
            WhiteTigerScenceTower_List.push_back(pos[i]);

    }


}
//载入魏军屯田点信息
void DifferentScence::LoadRoutePoint()
{
    if(Flag=="AzureDragonScence")
    {
        QPoint pos[4]=
        {
            QPoint(1140,205),
            QPoint(1146,525),
            QPoint(360,534),
            QPoint(361,823)
        };
        for(int i=0;i<4;++i)
        {
            RoutePoint point(pos[i]);
            AzureDragonScenceRoutePoint_List.push_back(point);
        }
    }
    else if(Flag=="BlackTortoiseScence")
    {
        QPoint pos[4]=
        {
            QPoint(1140,205),
            QPoint(1146,525),
            QPoint(360,534),
            QPoint(361,823)
        };
        for(int i=0;i<4;++i)
        {
            RoutePoint point(pos[i]);
            BlackTortoiseScenceRoutePoint_List.push_back(point);
        }
    }
    else if(Flag=="VermilionBirdScence")
    {    QPoint pos[4]=
        {
            QPoint(1140,205),
            QPoint(1146,525),
            QPoint(360,534),
            QPoint(361,823)
        };
        for(int i=0;i<4;++i)
        {
            RoutePoint point(pos[i]);
            VermilionBirdScenceRoutePoint_List.push_back(point);
        }

    }
    else if(Flag=="WhiteTigerScence")
    {    QPoint pos[4]=
        {
            QPoint(1140,205),
            QPoint(1146,525),
            QPoint(360,534),
            QPoint(361,823)
        };
        for(int i=0;i<4;++i)
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
    if(WeiSodier_Batch>=10)
        return false;
    RoutePoint StartRoutePoint=AzureDragonScenceRoutePoint_List.back();
    int WeiSodierStartDistance[]={100,200,300,400,500,600,700};
    for(int i=0;i<7;i++)
    {
        WeiSodier *weiSodier=new WeiSodier(StartRoutePoint,this);
        WeiSodier_List.push_back(weiSodier);
        QTimer::singleShot(WeiSodierStartDistance[i],weiSodier,SLOT(OrderActive()));
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
    }

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
