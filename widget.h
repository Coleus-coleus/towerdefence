#ifndef WIDGET_H
#define WIDGET_H
#include <QList>
#include <QWidget>
#include "tower.h"
#include "choosescence.h"
#include <QSound>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    //重写paintEvent事件
    void paintEvent(QPaintEvent *);
    //选关场景
    Choosescence *choosescence=NULL;
    QSound *StartSound;//开始音效

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
