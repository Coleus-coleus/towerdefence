#ifndef ROUTEPOINT_H
#define ROUTEPOINT_H
#include <QPoint>
#include <QPainter>

class RoutePoint
{
public:
    RoutePoint(QPoint Point);//构造函数
    void SetNextRoutePoint(RoutePoint *NextRoutePoint);//设置下一个屯田点的坐标
    RoutePoint* NextRoutePoint() const;//返回下一个屯田点的坐标
    const QPoint Coordinate() const;//当前坐标
    void draw(QPainter *painter) const;//载入屯田点图片
private:
        QPoint My_Coordinate;//当前屯田点坐标
        RoutePoint *My_NextRoutePoint;//下一个屯田点坐标

};

#endif // ROUTEPOINT_H
