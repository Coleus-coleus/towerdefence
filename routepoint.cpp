#include "routepoint.h"
#include <QPoint>
#include <QPainter>
#include <QPixmap>
#include <QSize>
//构造函数
RoutePoint::RoutePoint(QPoint Point,const QPixmap &Picture):
    My_Coordinate(Point),
    My_Picture(Picture),
    My_NextRoutePoint(NULL)
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
    painter->save();
    painter->drawPixmap(My_Coordinate.x(),My_Coordinate.y(),My_Picture);
    painter->restore();
}
void RoutePoint::SetCoordinate(QPoint Coordinate)
{
    My_Coordinate=Coordinate;
}

