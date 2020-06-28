#ifndef ENDSCENCE_H
#define ENDSCENCE_H

#include <QWidget>
#include <QWidget>
#include <QPainter>
#include <QSound>
class EndScence : public QWidget
{
    Q_OBJECT
public:
    explicit EndScence(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);//重写画图函数
    QSound *EndSound;//结束音乐
    void EndFlag(QString string);//传入战争胜利或者失败的信号
    QSound* ReturnEndMusic();//返回背景音乐
    void ChangSound();//改变音乐
private:
    QString Endflag;//结局信号


signals:

public slots:
};

#endif // ENDSCENCE_H
