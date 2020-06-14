#include "routepoint.h"
#include <QPoint>
#include <QPainter>
#include <QPixmap>
#include <QSize>
//构造函数
RoutePoint::RoutePoint(QPoint Point,const QPixmap &Picture):
    My_Coordinate(Point),
    My_Picture(Picture),
    My_NextRoutePoint(NULL),
    IsLast(false),
    FixX(0),
    FixY(0)
{
    //缩放图片
    QSize PictureSize(100,100);
    QPixmap SizePicture=My_Picture.scaled(PictureSize,Qt::KeepAspectRatio);
    My_Picture=SizePicture;
}
void RoutePoint::SetNextRoutePoint(RoutePoint *NextRoutePoint)
{
    My_NextRoutePoint=NextRoutePoint;
}
RoutePoint* RoutePoint::NextRoutePoint()const
{
    return My_NextRoutePoint;
}
const QPoint RoutePoint::Coordinate() const
{
    return My_Coordinate;
}
void RoutePoint::draw(QPainter *painter) const
{
    if(IsLast==false)
    {
        painter->save();
        painter->drawPixmap(My_Coordinate.x(),My_Coordinate.y(),My_Picture);
        painter->restore();
    }
    else
    {
        painter->save();
        painter->drawPixmap(My_Coordinate.x()-FixX,My_Coordinate.y()-FixY,My_Picture);
        painter->restore();

    }
}
void RoutePoint::SetCoordinate(QPoint Coordinate)
{
    My_Coordinate=Coordinate;
}
void RoutePoint::ChangPicture(int x,int y)
{
    FixX=x;
    FixY=y;
    My_Picture=QPixmap(":/LiuHan/ChengDu_LiuShan/ChengDu_LiuShan.png");//将图片改为刘禅的图片
    //缩放图片
    QSize PictureSize(300,300);
    QPixmap SizePicture=My_Picture.scaled(PictureSize,Qt::KeepAspectRatio);
    My_Picture=SizePicture;
    IsLast=true;
}

