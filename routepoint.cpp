#include "routepoint.h"
#include <QPoint>

//RoutePoint::RoutePoint(QPoint Point):My_Coordinate(Point),My_NextRoutePoint(NULL)
//{
//}
RoutePoint::RoutePoint(QPoint Point)
{
    My_Coordinate=Point;
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
    painter->setPen(Qt::white);
    painter->drawEllipse(My_Coordinate,50,50);
    painter->restore();
}

