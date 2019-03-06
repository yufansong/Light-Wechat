#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QPushButton>
#include <QTcpSocket>
#include "message.h"
#include <QMessageBox>
#include <QBitmap>
#include <QPainter>
#include "mylabel.h"

#define LENGTH_MESSAGE 1024
#define MAX_USER_NUM 200

namespace Ui {
class MyLogin;
}

class MyLogin : public QDialog
{
    Q_OBJECT

public:
    explicit MyLogin(QWidget *parent = 0);
    ~MyLogin();

    QPushButton loginSuccess;
    QPushButton *endApp;

    void setSocket(QTcpSocket *socket);

private slots:
    void on_pushButton_2_clicked();

private:
    Ui::MyLogin *ui;

public:
    //连接服务器的ip地址和port
    QString ip;
    QString port;

    //标志服务器是否连接成功和是否登陆成功
    bool connectSuccess;
    bool loginSuccessFlag;

    //登陆的用户名和密码
    QString userName;
    QString password;

    //可浏览的历史记录条数
    int scanMessageNum;

    //所有的用户数目，不包含自己
    int userNum;

    //所有的用户的在线情况，包含了群聊用户
    bool isOnline[MAX_USER_NUM];

    //每个用户名
    QStringList nameList;

    //每个人其他人的聊天记录
    QStringList chatMessageList[MAX_USER_NUM];

    //每个人其他人的聊天记录发送人
    QStringList chatMessageSendName[MAX_USER_NUM];

    //每条聊天记录是否是文件形式
    bool isFile[MAX_USER_NUM][1000];

    //是否需要强制改密码
    bool haveToChangePassword;

    //是否使其他人强制登出
    bool replace;

    QTcpSocket *clientSock;

    int getMessage(char*message);
};

#endif // LOGIN_H
