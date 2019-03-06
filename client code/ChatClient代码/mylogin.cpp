#include "mylogin.h"
#include "ui_mylogin.h"

MyLogin::MyLogin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MyLogin)
{
    ui->setupUi(this);

    endApp = this->ui->pushButton;

    connectSuccess = false;
    loginSuccessFlag = false;

    //设置圆角
    QBitmap bmp(this->size());
    bmp.fill();
    QPainter p(&bmp);
    p.setPen(Qt::NoPen);
    p.setBrush(Qt::black);
    p.drawRoundedRect(bmp.rect(),20,20);
    setMask(bmp);

    ui->pushButton->  setStyleSheet(
                //正常状态样式
                "QPushButton{"
                "background-color:rgba(216,216,216,100);"//背景色（也可以设置图片）
                "border-style:outset;"                  //边框样式（inset/outset）
                "border-width:4px;"                     //边框宽度像素
                "border-radius:10px;"                   //边框圆角半径像素
                "border-color:rgba(255,255,255,200);"    //边框颜色
                "font:bold 10px;"                       //字体，字体大小
                "color:rgba(0,0,0,200);"                //字体颜色
                "padding:6px;"                          //填衬
                "font: 75 12pt 微软雅黑;"
                "}"
                //鼠标悬浮样式
                "QPushButton:hover{"
                "background-color:rgba(190,190,190,100);"//背景色（也可以设置图片）
                "border-style:outset;"                  //边框样式（inset/outset）
                "border-width:6px;"                     //边框宽度像素
                "border-radius:10px;"                   //边框圆角半径像素
                "border-color:rgba(255,255,255,200);"    //边框颜色
                "font:bold 10px;"                       //字体，字体大小
                "color:rgba(0,0,0,200);"                //字体颜色
                "padding:6px;"                          //填衬
                "font: 75 12pt 微软雅黑;"
                "}"
                //鼠标按下样式
                "QPushButton:pressed{"
                "background-color:rgba(255,255,255,100);"//背景色（也可以设置图片）
                "border-style:outset;"                  //边框样式（inset/outset）
                "border-width:6px;"                     //边框宽度像素
                "border-radius:10px;"                   //边框圆角半径像素
                "border-color:rgba(255,255,255,200);"    //边框颜色
                "font:bold 10px;"                       //字体，字体大小
                "color:rgba(0,0,0,200);"                //字体颜色
                "padding:6px;"                          //填衬
                "font: 75 12pt 微软雅黑;"
                "}"
                );
    ui->pushButton_2->  setStyleSheet(
                //正常状态样式
                "QPushButton{"
                "background-color:rgba(216,216,216,100);"//背景色（也可以设置图片）
                "border-style:outset;"                  //边框样式（inset/outset）
                "border-width:4px;"                     //边框宽度像素
                "border-radius:10px;"                   //边框圆角半径像素
                "border-color:rgba(255,255,255,200);"    //边框颜色
                "font:bold 10px;"                       //字体，字体大小
                "color:rgba(0,0,0,200);"                //字体颜色
                "padding:6px;"                          //填衬
                "font: 75 12pt 微软雅黑;"
                "}"
                //鼠标悬浮样式
                "QPushButton:hover{"
                "background-color:rgba(190,190,190,100);"//背景色（也可以设置图片）
                "border-style:outset;"                  //边框样式（inset/outset）
                "border-width:6px;"                     //边框宽度像素
                "border-radius:10px;"                   //边框圆角半径像素
                "border-color:rgba(255,255,255,200);"    //边框颜色
                "font:bold 10px;"                       //字体，字体大小
                "color:rgba(0,0,0,200);"                //字体颜色
                "padding:6px;"                          //填衬
                "font: 75 12pt 微软雅黑;"
                "}"
                //鼠标按下样式
                "QPushButton:pressed{"
                "background-color:rgba(255,255,255,100);"//背景色（也可以设置图片）
                "border-style:outset;"                  //边框样式（inset/outset）
                "border-width:6px;"                     //边框宽度像素
                "border-radius:10px;"                   //边框圆角半径像素
                "border-color:rgba(255,255,255,200);"    //边框颜色
                "font:bold 10px;"                       //字体，字体大小
                "color:rgba(0,0,0,200);"                //字体颜色
                "padding:6px;"                          //填衬
                "font: 75 12pt 微软雅黑;"
                "}"
                );
}

MyLogin::~MyLogin()
{
    delete ui;
}

void MyLogin::on_pushButton_2_clicked()
{
    this->ip = ui->lineEdit->text();
    this->port = ui->lineEdit_2->text();
    userName = ui->lineEdit_3->text();
    password = ui->lineEdit_4->text();

    if(ip.isEmpty() || port.isEmpty())
    {
        //提示相应信息
        MyLabel *mylabel = new MyLabel(this,"请输入ip和port");
        mylabel->toastr();
        return;
    }

    if(userName.isEmpty() || password.isEmpty())
    {
        //提示用户名或密码为空
        MyLabel *mylabel = new MyLabel(this,"请输入用户名和密码");
        mylabel->toastr();
        return;
    }

    //获取端口号
    quint16 portNetwork = port.toUInt();

    //连接至服务器
    clientSock->connectToHost(ip,portNetwork);
    if(!clientSock->waitForConnected(3000))
    {
        //提示相应信息
        MyLabel *mylabel = new MyLabel(this,"连接服务器失败");
        mylabel->toastr();
        return;
    }
    /*else //连接成功
    {
        //提示相应信息
        MyLabel *mylabel = new MyLabel(this,"连接服务器成功");
        mylabel->toastr();
    }*/

    connectSuccess = true;

    qDebug()<<"连接成功";

    /**********************************与服务器进行相应信息的交互******************************************/
    //发送用户名和密码
    Message message;

    message.setUserNamePassword(userName,password);
    clientSock->write((char*)&message,LENGTH_MESSAGE);
    if(!clientSock->waitForBytesWritten())
    {
        //提示发送失败
        MyLabel *mylabel = new MyLabel(this,"发送用户名和密码失败");
        mylabel->toastr();
        clientSock->close();
        return;
    }

    if(getMessage((char*)&message) < 0)
    {
        //提示相应信息
        MyLabel *mylabel = new MyLabel(this,"连接服务器失败");
        mylabel->toastr();
        return;
    }

    if(message.getType() == NAK)
    {
        //提示登陆失败
        MyLabel *mylabel = new MyLabel(this,"账号或密码错误");
        mylabel->toastr();

        clientSock->close();
        return;
    }

    qDebug()<<"ack success";

    //读取是否强制登出
    if(getMessage((char*)&message) < 0)
    {
        //提示信息
        MyLabel *mylabel = new MyLabel(this,"读取强制退出信息失败");
        mylabel->toastr();

        clientSock->close();
        return;
    }

    //提示某用户被迫下线
    if(message.getType() == REPLACE)
        replace = true;
    else
        replace = false;

    //qDebug()<<"message.getType()="<<message.getType();
    //qDebug()<<"REPLACE="<<REPLACE;
    //qDebug()<<"message.getTyep==REPLACE"<<(message.getType()==REPLACE);
    //qDebug()<<"replace="<<replace;

    //qDebug()<<"强制退出接收完毕"<<message.getType();

    //读取可浏览多少条历史记录
    if(getMessage((char*)&message) < 0)
    {
        //提示登陆失败
        MyLabel *mylabel = new MyLabel(this,"读取历史记录条数失败");
        mylabel->toastr();

        clientSock->close();
        return;
    }
    message.getScanMessageNum(scanMessageNum);

    qDebug()<<"可浏览信息条数"<<scanMessageNum;

    //读取总人数
    if(getMessage((char*)&message) < 0)
    {
        //提示登陆失败
        MyLabel *mylabel = new MyLabel(this,"读取总人数失败");
        mylabel->toastr();

        clientSock->close();
        return;
    }
    message.getTotalUserNum(userNum);

    qDebug()<<"总人数"<<userNum;

    QString sendName,receiveName,msg;
    bool online;
    bool onlineFirst = false;
    //接收每个用户的聊天记录信息
    for(int i = 0;i<userNum;i++)
    {
        if(getMessage((char*)&message) < 0)
        {
            //提示登陆失败
            MyLabel *mylabel = new MyLabel(this,"读取用户名称及在线状态失败");
            mylabel->toastr();

            clientSock->close();
            return;
        }
        message.getUserState(sendName,online);

        qDebug()<<"桢名称："<<sendName<<"桢在线情况:"<<online;

        if(i == 0)
            nameList.append("[群聊]");
        else
        {
            nameList.append(sendName);
            isOnline[i] = online;
            if(online)
                onlineFirst = true;
        }

        qDebug()<<"用户"<<i<<nameList[i]<<' '<<isOnline[i];

        for(int j = 0;;j++)
        {
            if(getMessage((char*)&message) < 0)
            {
                //提示登陆失败
                MyLabel *mylabel = new MyLabel(this,"读取聊天记录失败");
                mylabel->toastr();

                clientSock->close();
                return;
            }
            //聊天记录接收完毕
            if(message.getType() == ACK)
                break;
            message.getPassChatMsg(sendName,receiveName,isFile[i][j],msg);
            chatMessageList[i].append(msg);
            chatMessageSendName[i].append(sendName);
            //qDebug()<<"聊天记录"<<j<<chatMessageSendName[i]<<' '<<chatMessageList[i]<<isFile[i][j];
        }

    }
    //群聊用户的在线情况
    isOnline[0] = onlineFirst;

    qDebug()<<"开始接收更改密码";

    if(getMessage((char*)&message) < 0)
    {
        //提示登陆失败
        MyLabel *mylabel = new MyLabel(this,"读取是否更改密码失败");
        mylabel->toastr();

        clientSock->close();
        return;
    }
    if(message.getType() == CHANGE_PASSWORD)
        haveToChangePassword = true;
    else
        haveToChangePassword = false;
    /****************************服务器交互信息结束*************************************************/

    loginSuccessFlag = true;
    loginSuccess.clicked();
}

/*
int MyLogin::getMessage(char*message)
{
    int length = 0;
    int num;
    for(;;)
    {
        //等待时间很短，这样可以更快响应服务器发送信息
        clientSock->waitForReadyRead(1);
        num = clientSock->read(message + length,LENGTH_MESSAGE - length);
        qDebug()<<length;
        if(num < 0)
        {
            //提示read错误
            MyLabel *mylabel = new MyLabel(this,"getMessage错误");
            mylabel->toastr();
            qDebug()<<"num="<<num;
            return -1;
        }
        else if(num == 0)
            continue;
        else if(num + length < LENGTH_MESSAGE)
        {
            length += num;
        }
        else
            break;
    }
    return num + length;
}*/

int MyLogin::getMessage(char*message)
{
    int num;
    for(;;)
    {
        //等待时间很短，这样可以更快响应服务器发送信息
        clientSock->waitForReadyRead(10);
        num = clientSock->read(message,LENGTH_MESSAGE);
        if(num < 0)
        {
            //提示read错误
            MyLabel *mylabel = new MyLabel(this,"getMessage错误");
            mylabel->toastr();
            qDebug()<<"num="<<num;
            return -1;
        }
        else if(num == 0)
            continue;
        else if(num < LENGTH_MESSAGE)
        {
            return -1;
        }
        else
            break;
    }
    return num;
}


//设置套接字
void MyLogin::setSocket(QTcpSocket *socket)
{
    clientSock = socket;
}
