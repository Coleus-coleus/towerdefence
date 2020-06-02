#ifndef CHOOSESCENCE_H
#define CHOOSESCENCE_H
#include "differentscence.h"
#include <QWidget>
#include <QPainter>

class Choosescence : public QWidget
{
    Q_OBJECT
public:
    explicit Choosescence(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);
    DifferentScence *differentScence=NULL;//设置关卡


signals:
    //自定义信号，告诉主场景,点击了返回
    void Choosescenceback();

public slots:
};

#endif // CHOOSESCENCE_H
