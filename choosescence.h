#ifndef CHOOSESCENCE_H
#define CHOOSESCENCE_H
#include "differentscence.h"
#include <QWidget>
#include <QPainter>
#include <QSound>
class Choosescence : public QWidget
{
    Q_OBJECT
public:
    explicit Choosescence(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);//重写画图函数
    DifferentScence *differentScence=NULL;//设置关卡
    QSound *ChooseSound;//选关音乐



signals:
    //自定义信号，告诉主场景,点击了返回
    void Choosescenceback();

public slots:
};

#endif // CHOOSESCENCE_H
