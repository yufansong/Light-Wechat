#ifndef FILEDISPLAY_H
#define FILEDISPLAY_H

#include <QDialog>
#include <QStringList>
#include <QString>
#include <QListView>
#include <QStandardItemModel>
#include <QModelIndex>
#include <QStandardItem>
#include <QLinearGradient>
#include <QBrush>
#include <QDebug>
#include <QDir>
#include <QColor>
#include <QModelIndex>
#include <QMessageBox>
#include <QGraphicsDropShadowEffect>
#include <QFileDialog>
#include <QPushButton>
#include <QTcpSocket>
#include "message.h"
#include <QTime>
#include <QBitmap>
#include <QPainter>
#include "mylabel.h"
#include <QTextCodec>
#include <QKeyEvent>
#include <QTime>

#define MAX_USER_NUM 200
#define MAX_CHAT_SIZE 1000
#define LENGTH_MESSAGE 1024
#define LENGTH_FILE_MESSAGE 976
#define DELAY_TIME 200

QString GBK2UTF8(const QString &inStr);
QString UTF82GBK(const QString &inStr);
void delay(unsigned int msec);

namespace Ui {
class FileDisplay;
}

class FileDisplay : public QDialog
{
    Q_OBJECT

public:
    explicit FileDisplay(QWidget *parent = 0);//path表示工作的文件夹
    ~FileDisplay();

    //返回类中strName变量
    QString getName() const;

    //下一页和最小化
    QPushButton *next;
    QPushButton *min;

    QPushButton startChangePassword;

    //我这个用户的密码
    QString password;

    //使用的套接字
    QTcpSocket clientSock;

    //设置显示内容
    void setContent(QString myName,QString myPassword,QStringList userName,bool*online,int number,QStringList*message,QStringList*sendName,bool file[MAX_USER_NUM][MAX_CHAT_SIZE],int messageNum,bool changePassword,QString _ip,QString _port);

    //发送更改密码报文
    void newPassword(QString newpassword);

    bool hasExit;

private slots:

    void on_listView_clicked(const QModelIndex &index);

    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void ClientReadData();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    //断开
    void ClientBreak();

private:
    Ui::FileDisplay *ui;

    //总用户数目，包含了群聊用户
    int userNum;

    //所有的用户的在线情况，包含了群聊用户
    bool isOnline[MAX_USER_NUM];

    //项目显示的文本
    QStringList strList;

    //当前用户是否有新消息接收
    bool newMessage[MAX_USER_NUM];

    //每个人其他人的聊天记录
    QStringList chatMessageList[MAX_USER_NUM];

    //每个人其他人的聊天记录发送人
    QStringList chatMessageSendName[MAX_USER_NUM];

    //每条聊天记录是否是文件形式
    bool isFile[MAX_USER_NUM][MAX_CHAT_SIZE];

    //初始状态的index
    int currentIndex;

    //我这个用户的名字
    QString name;

    //listView显示的item表
    QStandardItemModel*standardItemModel;

    //message listView显示的item表
    QStandardItemModel*standardItemModelMessage;

    //当前是否正在接收文件
    bool isReceiveFile;

    //当前累计接收的文件名称
    QString fileMessage;

    //当前接收的文件名称
    QString receiveFileName;

    //可浏览的历史记录条数
    int scanMessageNum;

    //强制更改密码
    bool haveToChangePassword;

    //ip地址
    QString ip;

    //端口号
    QString port;

    //读取一个桢
    int getMessage(char*message);

    //阻塞方式读取一个桢
    int _getMessage(char*message);

    bool disConnect;

    //键盘响应
    //void keyPressEvent( QKeyEvent *k );
};

#endif // FILEDISPLAY_H
