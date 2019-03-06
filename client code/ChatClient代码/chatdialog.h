#ifndef CHATDIALOG_H
#define CHATDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QStackedWidget>
#include <QPainter>
#include <QPropertyAnimation>
#include <QDebug>
#include <QGraphicsDropShadowEffect>
#include "filedisplay.h"
#include "mylogin.h"
#include "newpassword.h"
#include "QBitmap"
#include <QMouseEvent>
#include <QPoint>
#include "mylabel.h"
#include <QSystemTrayIcon>

namespace Ui {
class ChatDialog;
}

class ChatDialog : public QStackedWidget
{
    Q_OBJECT
    Q_PROPERTY( float rotateVal READ rotateVal WRITE setRotateVal)
public:

    explicit ChatDialog(QWidget *parent = 0);

    //绘制事件
    void paintEvent(QPaintEvent *event);

    ~ChatDialog();

public slots:
    //下一页
    void nextPage();

    void changePassword();

    void changePasswordEnd();

    void end();

public:

    //跳转到索引页
    void rotate(int index);

    //旋转值
    float rotateVal();

    //设置旋转值
    void setRotateVal(float fl);

private slots:
    //旋转值改变了
    void valChanged(QVariant);

    //动画结束
    void animDone();

    //最小化窗口
    void minWindow();

    //响应点击托盘图标信号
    void on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason reason);

private:
    //旋转值
    float iRotateVal;

    //旋转动画中
    bool isAnimating;

    //下一个索引页
    int nextIndex;

    //登陆界面
    MyLogin *login;
    //聊天界面
    FileDisplay *filedisplay;
    //改密界面
    NewPassword *newpassword;

    bool m_draging;//当前是否处于拖动状态
    QPoint m_startPostion;//拖动前鼠标位置
    QPoint m_framPostion;//窗体的原始位置

    //鼠标可拖动
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    //最小化到托盘
    QSystemTrayIcon *mSysTrayIcon;
};

#endif // CHATDIALOG_H
