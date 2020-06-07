#ifndef ROUTEPOINT_H
#define ROUTEPOINT_H
#include <QPoint>
#include <QPainter>
#include <QPixmap>

class RoutePoint
{
public:
    RoutePoint(QPoint Point,const QPixmap &Picture=QPixmap(":/RoutePoint/StoreField.png"));//构造函数
    void SetNextRoutePoint(RoutePoint *NextRoutePoint);//设置下一个屯田点的坐标
    RoutePoint* NextRoutePoint() const;//返回下一个屯田点的坐标
    const QPoint Coordinate() const;//当前坐标
    void draw(QPainter *painter) const;//载入屯田点图片
    void SetCoordinate(QPoint Coordinate);//设置当前坐标
private:
        QPoint My_Coordinate;//当前屯田点坐标
        QPixmap My_Picture;
        RoutePoint *My_NextRoutePoint;//下一个屯田点坐标

};

#endif // ROUTEPOINT_H
