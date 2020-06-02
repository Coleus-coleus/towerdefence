#ifndef WIDGET_H
#define WIDGET_H
#include <QList>
#include <QWidget>
#include "tower.h"
#include "choosescence.h"

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

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
