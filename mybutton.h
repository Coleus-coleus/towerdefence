#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QPushButton>

class Mybutton : public QPushButton
{
    Q_OBJECT
public:
    //构造函数
    Mybutton(QString pathway);
    //成员路径
    QString mypathway;
signals:

public slots:
};

#endif // MYBUTTON_H
