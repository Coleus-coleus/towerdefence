#include "mybutton.h"
#include <QPushButton>
#include <QPixmap>
#include <QDebug>
Mybutton::Mybutton(QString pathway)
{
    this->mypathway=pathway;
    QPixmap pix;
    bool ret=pix.load(pathway);
    if(!ret)
    {
       qDebug()<<"图片加载失败";
       return;
    }
       //设置图片大小
       this->setFixedSize(pix.width(),pix.height());
       //设置不规则图片样式
       //设置图标
       this->setIcon(pix);
       //设置图标大小
       this->setIconSize(QSize(325,325));
    this->setFlat(true);
}
