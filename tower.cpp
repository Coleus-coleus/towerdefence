#include "tower.h"
#include <QPoint>
#include <QPixmap>
#include <QSize>
#include <QPainter>
#include <QDebug>
//固定塔的大小为30*30
const QSize Tower::tower_size(100,100);
//构造塔函数的实现
Tower::Tower(QPoint coordinate, const QPixmap &picture)
    :tower_coordinate(coordinate),tower_existence(false),tower_picture(picture)
{    QSize tower_pix(100,100);
     tower_picture=tower_picture.scaled(tower_pix,Qt::KeepAspectRatio);
}
//找出塔的中心点位置
const QPoint Tower::tower_centercoordinate() const
{
    QPoint temp(tower_coordinate.x()+tower_size.width()/2,tower_coordinate.y()+tower_size.height()/2);
    return temp;
}
//判断点击是否在塔的区域内
bool Tower::inArea(const QPoint &coordinate) const
{
    bool flag1=coordinate.x()>tower_coordinate.x()&&coordinate.x()<(tower_coordinate.x()+tower_size.width());
    bool flag2=coordinate.y()>tower_coordinate.y()&&coordinate.y()<(tower_coordinate.y()+tower_size.height());
    return flag1&&flag2;
}
bool Tower::existence() const
{
    return tower_existence;
}
void Tower::tower_exist(bool existence)
{
    tower_existence=existence;
}
//贴上贴图
void Tower::draw(QPainter *painter) const
{
    painter->drawPixmap(tower_coordinate.x(),tower_coordinate.y(),tower_picture);
}
