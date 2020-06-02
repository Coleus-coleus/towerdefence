#include "closecombatdefend.h"
#include "differentscence.h"
#include <QPixmap>
#include <QPainter>
#include <QPoint>
#include <QSize>
#include "tower.h"
CloseCombatDefend::CloseCombatDefend(QPoint coordinate,DifferentScence* scence,const QPixmap &picture)
    :CloseCombatDefend_damage(100),
     CloseCombatDefend_radius(50),
     CloseCombatDefend_frequency(1000),
     CloseCombatDefend_coordinate(coordinate),
     CloseCombatDefend_picture(picture),
     setScence(scence)
{

}
void CloseCombatDefend::draw(QPainter *painter) const//载入近战塔防图片
{
   painter->save();
   painter->setPen(Qt::white);
   painter->drawEllipse(CloseCombatDefend_coordinate,CloseCombatDefend_radius,CloseCombatDefend_radius);
   static const QPoint offsetPoint(-50,-50);
   painter->translate(CloseCombatDefend_coordinate);
   painter->drawPixmap(offsetPoint,CloseCombatDefend_picture);
   painter->restore();

}
