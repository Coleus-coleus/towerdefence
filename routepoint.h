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
    void ChangPicture(int x,int y);//改变转折点图片，(用于标出成都(即基地))
private:
        QPoint My_Coordinate;//当前屯田点坐标
        QPixmap My_Picture;
        RoutePoint *My_NextRoutePoint;//下一个屯田点坐标
        bool IsLast;//判断是不是最后一个屯田点
        //修正坐标
        int FixX;
        int FixY;

};

#endif // ROUTEPOINT_H
