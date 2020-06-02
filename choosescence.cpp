#include "choosescence.h"
#include <QIcon>
#include <QPushButton>
#include "mybutton.h"
#include "differentscence.h"

Choosescence::Choosescence(QWidget *parent) : QWidget(parent)
{
    setWindowIcon(QIcon(":/logo/logo.png"));
    this->setFixedSize(1600,1000);
    setWindowTitle("蜀汉悲歌");
    //设置返回按钮
    Mybutton *backbutton=new Mybutton(":/button/backbutton");
    backbutton->setParent(this);
    backbutton->move(1400,600);
    //返回按钮的实现
    connect(backbutton,&Mybutton::clicked,[=]()
    {
        emit this->Choosescenceback();
    });
    //创建选关按钮
    QString scencelogo[4]=
    {":/logo/scence_logo/Azure Dragon.png",
     ":/logo/scence_logo/Black Tortoise.png",
     ":/logo/scence_logo/Vermilion Bird.png",
     ":/logo/scence_logo/White Tiger.png"
    };
    Mybutton *scencebutton[4]=
    {new Mybutton(scencelogo[0]),
     new Mybutton(scencelogo[1]),
     new Mybutton(scencelogo[2]),
     new Mybutton(scencelogo[3]),
    };
    for(int i=0;i<4;i++)
    {
        scencebutton[i]->setParent(this);
        scencebutton[i]->setFlat(true);
        scencebutton[i]->setFixedSize(300,325);
    }
    scencebutton[0]->move(800,50);
    scencebutton[1]->move(800,450);
    scencebutton[2]->move(266,50);
    scencebutton[3]->move(266,450);
    differentScence=new DifferentScence;//实例化关卡
    //转入青龙关
    connect(scencebutton[0],&Mybutton::clicked,[=]()
    {
    this->hide();
    differentScence->ChangeScence("AzureDragonScence");
    differentScence->show();
    });
    //转入玄武关
    connect(scencebutton[1],&Mybutton::clicked,[=]()
    {
    this->hide();
    differentScence->ChangeScence("BlackTortoiseScence");
    differentScence->show();
    });
    //转入朱雀关
    connect(scencebutton[2],&Mybutton::clicked,[=]()
    {
    this->hide();
    differentScence->ChangeScence("VermilionBirdScence");
    differentScence->show();
    });
    //转入白虎关
    connect(scencebutton[3],&Mybutton::clicked,[=]()
    {
    this->hide();
    differentScence->ChangeScence("WhiteTigerScence");
    differentScence->show();
    });

}
void Choosescence::paintEvent(QPaintEvent *)
{
    //加载选关背景
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/background/choosescence.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}
