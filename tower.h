#ifndef TOWER_H
#define TOWER_H
#include <QPoint>
#include <QPixmap>
#include <QSize>
#include <QPainter>

class Tower
{
public:
    Tower(QPoint coordinate,const QPixmap &picture=QPixmap(":/logo/logo.png"));//构造函数
    void tower_exist(bool existence =true);//表明该塔已有塔防
    void  draw(QPainter *painter) const;//载入图片
    bool existence() const;//返回该塔是否有塔防
    bool inArea(const QPoint &coordinate) const;//判断点击是否在塔的区域内
    const QPoint tower_centercoordinate() const;//找出塔的中心点位置
private:
    QPoint  tower_coordinate;//塔的位置
    QPixmap tower_picture;//塔的图片
    bool    tower_existence;//是否有塔
    static const QSize tower_size;//塔的大小

};

#endif // TOWER_H
