#include "widget.h"
#include "ui_widget.h"
#include "choosescence.h"
#include "mybutton.h"
#include <QPainter>
#include <QList>
#include <QPixmap>
#include <QDebug>
#include <QPushButton>
#include <QTimer>
#include <QSound>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //设置图标
    setWindowIcon(QIcon(":/logo/logo.png"));
    //设置标题
    setWindowTitle("蜀汉悲歌");
    //开始按钮
    choosescence=new Choosescence;//实例化，选择关卡场景
    StartSound=new QSound(":/Music/BeginMusic.wav",this);//开始音乐
    StartSound->play();
    StartSound->setLoops(10000000);
    connect(ui->startbutton,&QPushButton::clicked,[=]()
    {
    QTimer::singleShot(500,this,[=]()//延迟进入关卡
    {
        StartSound->stop();
        this->hide();//隐藏自身
        choosescence->show();//显示选关场景
        choosescence->ChooseSound->play();
    });
    });
    //返回按钮
    //监听返回按钮的信号
    connect(choosescence,&Choosescence::Choosescenceback,this,[=](){
        QTimer::singleShot(500,this,[=]()
        {
            choosescence->ChooseSound->stop();
            choosescence->hide();//选关场景的隐藏
            this->show();//显示选关场景
            StartSound->play();
        });
    });
}

void Widget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/background/startbackground.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}

Widget::~Widget()
{
    delete ui;
}
