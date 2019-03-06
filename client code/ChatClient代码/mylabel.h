#ifndef MYLABEL_H_
#define MYLABEL_H_

#include <QObject>
#include <QLabel>

#define DEFULT_TOAST_STYLE "\
QLabel{\
    color:#FFFFFF;\
    font:18px;\
    font-weight:500;\
    background-color:rgb(98,92,82,90);\
    padding:3px;\
    border-radius:2;\
}\
"

//自动消失的提示框
class MyLabel : public QLabel
{
    Q_OBJECT
public:
    explicit MyLabel(QWidget *parent,
                   const QString &message = QString(),
                   int w = 200,
                   int h = 50,
                   const QString &style = DEFULT_TOAST_STYLE);
    void toastr();

private:
    /*
     * setShadow 设置窗体阴影效果
     * w 窗体指针
     * blurRadius 阴影清晰度，越小越清晰
     * dx x方向阴影位置和偏移量，正值在右方，值越大偏移越大
     * dy y方向阴影位置和偏移量，正值在下方，值越大偏移越大
     */
    void setShadow(QWidget *w, qreal blurRadius=10, qreal dx=5, qreal dy=5);

private slots:
    void animationFinished();
    void delSelf();

private:
    int startx;
    int starty;
    int endy;
};

#endif // MYLABEL_H
