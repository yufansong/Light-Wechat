#include "filedisplay.h"
#include "ui_filedisplay.h"

FileDisplay::FileDisplay(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FileDisplay)
{
    ui->setupUi(this);

    next = ui->pushButton_5;
    min = ui->pushButton_6;

    //申请空间
    standardItemModel = new QStandardItemModel(this);
    standardItemModelMessage = new QStandardItemModel(this);

    isReceiveFile = false;
    fileMessage.clear();
    receiveFileName.clear();
    disConnect = true;

    //设置圆角
    QBitmap bmp(this->size());
    bmp.fill();
    QPainter p(&bmp);
    p.setPen(Qt::NoPen);
    p.setBrush(Qt::black);
    p.drawRoundedRect(bmp.rect(),20,20);
    setMask(bmp);

    ui->listView->  setStyleSheet(
                    //更改主界面格式
                    "QListView{"
                    "background-color:rgba(255,255,255,200);"//背景色（也可以设置图片）
                    "border-style:outset;"                  //边框样式（inset/outset）
                    "border-width:10px;"                     //边框宽度像素
                    //"border-radius:10px;"                   //边框圆角半径像素
                    "border-color:rgba(255,255,255,200);"    //边框颜色
                    "font:bold 10px;"                       //字体，字体大小
                    "color:rgba(0,0,0,100);"                //字体颜色
                    "padding:6px;"                          //填衬
                    "font: 75 12pt 微软雅黑;"
                    "}"
                    );

    ui->listView_2->  setStyleSheet(
                    //更改主界面格式
                    "QListView{"
                    "background-color:rgba(255,255,255,200);"//背景色（也可以设置图片）
                    "border-style:outset;"                  //边框样式（inset/outset）
                    "border-width:10px;"                     //边框宽度像素
                    //"border-radius:10px;"                   //边框圆角半径像素
                    "border-color:rgba(248,248,248,200);"    //边框颜色
                    "font:bold 10px;"                       //字体，字体大小
                    "color:rgba(0,0,0,100);"                //字体颜色
                    "padding:6px;"                          //填衬
                    "font: 75 12pt 微软雅黑;"
                    "}"
                    );

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

    ui->pushButton_4->  setStyleSheet(
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
                "color:rgba(0,0,0,100);"                //字体颜色
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
                "color:rgba(0,0,0,100);"                //字体颜色
                "padding:6px;"                          //填衬
                "font: 75 12pt 微软雅黑;"
                "}"
                );

    ui->pushButton_2->  setStyleSheet(
                //鼠标悬浮样式
                "QPushButton:hover{"
                "background-color:rgba(150,150,150,100);"//背景色（也可以设置图片）
                "border-style:outset;"                  //边框样式（inset/outset）
                "}"
                //鼠标按下样式
                "QPushButton:pressed{"
                "background-color:rgba(240,240,240,100);"//背景色（也可以设置图片）
                "border-style:outset;"                  //边框样式（inset/outset）
                "}"
                );
    ui->pushButton_3->  setStyleSheet(
                //鼠标悬浮样式
                "QPushButton:hover{"
                "background-color:rgba(150,150,150,100);"//背景色（也可以设置图片）
                "border-style:outset;"                  //边框样式（inset/outset）
                "}"
                //鼠标按下样式
                "QPushButton:pressed{"
                "background-color:rgba(240,240,240,100);"//背景色（也可以设置图片）
                "border-style:outset;"                  //边框样式（inset/outset）
                "}"
                );
    ui->pushButton_5->  setStyleSheet(
                //鼠标悬浮样式
                "QPushButton:hover{"
                "background-color:rgba(150,150,150,100);"//背景色（也可以设置图片）
                "border-style:outset;"                  //边框样式（inset/outset）
                "}"
                //鼠标按下样式
                "QPushButton:pressed{"
                "background-color:rgba(240,240,240,100);"//背景色（也可以设置图片）
                "border-style:outset;"                  //边框样式（inset/outset）
                "}"
                );
    ui->pushButton_6->  setStyleSheet(
                //鼠标悬浮样式
                "QPushButton:hover{"
                "background-color:rgba(150,150,150,100);"//背景色（也可以设置图片）
                "border-style:outset;"                  //边框样式（inset/outset）
                "}"
                //鼠标按下样式
                "QPushButton:pressed{"
                "background-color:rgba(240,240,240,100);"//背景色（也可以设置图片）
                "border-style:outset;"                  //边框样式（inset/outset）
                "}"
                );
}

FileDisplay::~FileDisplay()
{
    //这里应该释放掉standardItemModel以及其中的众多item,这里其中的item好像没有释放，日后还要注意学习相关部分
    delete standardItemModel;
    delete standardItemModelMessage;
    delete ui;
}

void FileDisplay::setContent(QString myName,
                             QString myPassword,
                             QStringList userName,
                             bool*online,int number,
                             QStringList*message,
                             QStringList*sendName,
                             bool file[MAX_USER_NUM][MAX_CHAT_SIZE],
                             int messageNum,
                             bool changePassword,
                             QString _ip,
                             QString _port)
{
    //初始信息记录
    userNum = number;
    name = myName;
    password = myPassword;
    scanMessageNum = messageNum;
    haveToChangePassword = changePassword;
    ip = _ip;
    port = _port;

    ui->label_2->setText(name+"(在线)");
    ui->label_3->setText("可看记录数:" + QString::number(scanMessageNum));

    //关联clientSock的readyRead信号
    connect(&clientSock, SIGNAL(readyRead()), this, SLOT(ClientReadData()));
    connect(&clientSock, SIGNAL(disconnected()), this, SLOT(ClientBreak()));

    //初始状态所有用户都没有收到新消息
    //读入所有用户姓名
    strList.clear();
    for(int i = 0;i<userNum;i++)
    {
        isOnline[i] = online[i];
        strList.append(userName[i]);
        newMessage[i] = false;
    }

    //读入所有的聊天记录
    for(int i = 0;i<number;i++)
    {
        chatMessageList[i].clear();
        chatMessageSendName[i].clear();
        for(int j = 0;j<message[i].size();j++)
        {
            chatMessageList[i].append(message[i][j]);
            chatMessageSendName[i].append(sendName[i][j]);
            isFile[i][j] = file[i][j];
        }
    }

    //设置index为0
    currentIndex = 0;

    //将要显示的内容放入表中
    for(int i = 0;i<strList.size();i++)
    {
        QStandardItem *item;
        if(isOnline[i])
            item = new QStandardItem(QIcon("images/online.png"),strList[i]);
        else
            item = new QStandardItem(QIcon("images/notonline.png"),strList[i]);
        if(i % 2 == 1)
        {
            QLinearGradient linearGrad(QPointF(0, 0), QPointF(200, 200));
            linearGrad.setColorAt(0, QColor(250,250,250));
            linearGrad.setColorAt(1, QColor(235,235,235));
            QBrush brush(linearGrad);
            item->setBackground(brush);
        }
        standardItemModel->appendRow(item);
    }
    ui->listView->setIconSize(QSize(40,40));
    ui->listView->setGridSize(QSize(45,45));
    ui->listView->setLayoutDirection(Qt::LeftToRight);

    //设置内容
    ui->listView->setModel(standardItemModel);

    standardItemModelMessage->clear();
    //将要显示的内容放入表中
    for(int i = 0;i<chatMessageList[currentIndex].size();i++)
    {
        QStandardItem *item;
        if(isFile[currentIndex][i])
            item = new QStandardItem(QIcon("images/open.ico"),chatMessageSendName[currentIndex][i] + ":" + chatMessageList[currentIndex][i]);
        else
            item = new QStandardItem(chatMessageSendName[currentIndex][i] + ":" + chatMessageList[currentIndex][i]);
        if(i % 2 == 1)
        {
            QLinearGradient linearGrad(QPointF(0, 0), QPointF(200, 200));
            linearGrad.setColorAt(0, QColor(250,250,250));
            linearGrad.setColorAt(1, QColor(235,235,235));
            QBrush brush(linearGrad);
            item->setBackground(brush);
        }
        standardItemModelMessage->appendRow(item);
    }
    ui->listView_2->setGridSize(QSize(45,45));
    ui->listView_2->setLayoutDirection(Qt::LeftToRight);

    //设置内容
    ui->listView_2->setModel(standardItemModelMessage);

    //初始显示第一个用户的聊天信息
    ui->label->setText(strList[currentIndex]);

    disConnect = false;
    hasExit = false;
}

//点击了某个选项
void FileDisplay::on_listView_clicked(const QModelIndex &index)
{
    if(currentIndex == index.row())
        return;
    currentIndex = index.row();

    standardItemModelMessage->clear();
    //将要显示的内容放入表中
    for(int i = 0;i<chatMessageList[currentIndex].size();i++)
    {
        QStandardItem *item;
        if(isFile[currentIndex][i])
            item = new QStandardItem(QIcon("images/open.ico"),chatMessageSendName[currentIndex][i] + ":" + chatMessageList[currentIndex][i]);
        else
            item = new QStandardItem(chatMessageSendName[currentIndex][i] + ":" + chatMessageList[currentIndex][i]);
        if(i % 2 == 1)
        {
            QLinearGradient linearGrad(QPointF(0, 0), QPointF(200, 200));
            linearGrad.setColorAt(0, QColor(250,250,250));
            linearGrad.setColorAt(1, QColor(235,235,235));
            QBrush brush(linearGrad);
            item->setBackground(brush);
        }
        standardItemModelMessage->appendRow(item);
    }

    //如果之前该用户有新消息，那么要更改这个用户的头像
    if(newMessage[currentIndex])
    {
        newMessage[currentIndex] = false;
        QStandardItem *item = standardItemModel->item(currentIndex);
        if(!isOnline[currentIndex])
            item->setIcon(QIcon("images/notonline.png"));
        else
            item->setIcon(QIcon("images/online.png"));
    }

    ui->label->setText(strList[currentIndex]);
}

//点击了发送按钮
void FileDisplay::on_pushButton_clicked()
{
    if(ui->textEdit->toPlainText().isEmpty())
    {
        //提示无法发送空信息
        MyLabel *mylabel = new MyLabel(this,"无法发送空信息");
        mylabel->toastr();
        return;
    }

    if(!isOnline[currentIndex])
    {
        //提示该用户已经下线
        MyLabel *mylabel = new MyLabel(this,"该用户已经下线");
        mylabel->toastr();
        return;
    }

    QString str = ui->textEdit->toPlainText();

    /***************************向服务器发送一条信息******************************/
    //通过tcp发送str消息
    Message message;
    if(currentIndex == 0)
        message.setMsg(name,name,str);
    else
        message.setMsg(name,strList[currentIndex],str);

    clientSock.write((char*)&message,LENGTH_MESSAGE);
    if(!clientSock.waitForBytesWritten())
    {
        //提示发送失败
        MyLabel *mylabel = new MyLabel(this,"发送信息失败");
        mylabel->toastr();
        return;
    }
    /***************************向服务器发送一条信息结束******************************/

    chatMessageSendName[currentIndex].append(name);
    chatMessageList[currentIndex].append(str);

    int length = chatMessageList[currentIndex].size();
    isFile[currentIndex][length - 1] = false;

    QStandardItem *item;
    item = new QStandardItem(chatMessageSendName[currentIndex][length-1] + ":" + chatMessageList[currentIndex][length-1]);
    if((length - 1) % 2 == 1)
    {
        QLinearGradient linearGrad(QPointF(0, 0), QPointF(200, 200));
        linearGrad.setColorAt(0, QColor(250,250,250));
        linearGrad.setColorAt(1, QColor(235,235,235));
        QBrush brush(linearGrad);
        item->setBackground(brush);
    }
    standardItemModelMessage->appendRow(item);

    //发送完成之后清空文本内容
    ui->textEdit->clear();
}

//点击了打开文件按钮
void FileDisplay::on_pushButton_4_clicked()
{
    if(!isOnline[currentIndex])
    {
        //提示该用户已经下线
        MyLabel *mylabel = new MyLabel(this,"该用户已经下线");
        mylabel->toastr();
        return;
    }

    if(currentIndex == 0)
    {
        //提示无法群发文件
        MyLabel *mylabel = new MyLabel(this,"无法群发文件");
        mylabel->toastr();
        return;
    }

    QFileDialog dialog(this);
    dialog.exec();
    dialog.setWindowTitle("请选择发送的文件");

    QStringList fileList;
    fileList = dialog.selectedFiles();

    if(fileList.size())
    {
        //将打开文件的内容读入TextEdit中
        QFile file(fileList[0]);
        file.open(QIODevice::ReadOnly/*|QIODevice::Text*/);

        //这里没有通过QTextStream方式读文件，因为这种方式导致中文乱码，因此这里直接用了file的readAll函数
        /*
        QByteArray array = file.readAll();
        QString str(array);
        file.close();
        */

        /** *********************向服务器发送一个文件**************************************/
        //通过tcp发送该文件
        Message message;
        QString filename = fileList[0].section('/',-1,-1);
        message.setFileName(name,strList[currentIndex],filename);
        clientSock.write((char*)&message,LENGTH_MESSAGE);
        if(!clientSock.waitForBytesWritten())
        {
            //提示传输失败
            MyLabel *mylabel = new MyLabel(this,"发送文件名称失败");
            mylabel->toastr();
            return;
        }
        qDebug()<<"文件名发送完成";

        int i = 0;
        //如果文件为空则不会发文件内容包
        char msg[LENGTH_MESSAGE];
        int num;
        for(;;)
        {
            num = file.read(msg,LENGTH_FILE_MESSAGE);
            if(num <= 0)
                break;
            qDebug()<<"sendNum="<<num;
            message.setFileMsg(name,strList[currentIndex],num,msg);
            clientSock.write((char*)&message,LENGTH_MESSAGE);
            if(!clientSock.waitForBytesWritten())
            {
                //提示传输失败
                MyLabel *mylabel = new MyLabel(this,"发送文件内容失败");
                mylabel->toastr();
                return;
            }
            qDebug()<<"发送"<<i++<<"次文件包";
            delay(DELAY_TIME);
        }
        file.close();
        qDebug()<<"发送文件内容完毕";
        delay(DELAY_TIME);

        //发送ACK包
        message.setAck(name,strList[currentIndex]);
        clientSock.write((char*)&message,LENGTH_MESSAGE);
        if(!clientSock.waitForBytesWritten())
        {
            //提示传输失败
            MyLabel *mylabel = new MyLabel(this,"发送确认包失败");
            mylabel->toastr();
            return;
        }
        //发送ACK包结束
        /*
        //下面传输文件内容
        QString fileMessage;
        //至少传输一次，就算是空文件也传输一次
        for(int start = 0;;)
        {
            fileMessage = str.mid(start,LENGTH_FILE_MESSAGE);

            qDebug()<<"name="<<name;
            qDebug()<<"strList[currentIndex]="<<strList[currentIndex];
            qDebug()<<"fileMessage="<<fileMessage;

            message.setFileMsg(name,strList[currentIndex],fileMessage);
            clientSock.write((char*)&message,LENGTH_MESSAGE);
            if(!clientSock.waitForBytesWritten())
            {
                //提示传输失败
                MyLabel *mylabel = new MyLabel(this,"发送文件内容失败");
                mylabel->toastr();
                return;
            }
            start+=LENGTH_FILE_MESSAGE;
            if(start >= str.size())
                break;
            qDebug()<<"传输完成一个文件包";
        }

        qDebug()<<"传输文件内容结束";
        message.setAck(name,strList[currentIndex]);
        clientSock.write((char*)&message,LENGTH_MESSAGE);
        if(!clientSock.waitForBytesWritten())
        {
            //提示传输失败
            MyLabel *mylabel = new MyLabel(this,"发送确认包失败");
            mylabel->toastr();
            return;
        }

        qDebug()<<"发送ACK结束";
        */
        /*********************向服务器发送文件结束**************************************/

        //向聊天记录中加入这一条
        chatMessageSendName[currentIndex].append(name);
        chatMessageList[currentIndex].append(fileList[0].section('/',-1,-1));

        int length = chatMessageList[currentIndex].size();
        isFile[currentIndex][length - 1] = true;

        QStandardItem *item;
        item = new QStandardItem(QIcon("images/open.ico"),chatMessageSendName[currentIndex][length - 1] + ":" + chatMessageList[currentIndex][length - 1]);
        if((length - 1) % 2 == 1)
        {
            QLinearGradient linearGrad(QPointF(0, 0), QPointF(200, 200));
            linearGrad.setColorAt(0, QColor(250,250,250));
            linearGrad.setColorAt(1, QColor(235,235,235));
            QBrush brush(linearGrad);
            item->setBackground(brush);
        }
        standardItemModelMessage->appendRow(item);
    }
    qDebug()<<"发送文件结束";
}

//接收到了信息
void FileDisplay::ClientReadData()
{
    //如果当前处于断开状态，那么不理睬
    if(disConnect)
        return;

    //如果正在接收文件，不理睬
    if(isReceiveFile)
        return;

    //提示相应信息
    //MyLabel *mylabel = new MyLabel(this,"收到了信息");
    //mylabel->toastr();

    /**************************受到一条服务器信息************************************/
    Message message;
    getMessage((char*)&message);

    Type type = message.getType();
    //qDebug()<<"type="<<type;
    if(type == FORCE_EXIT)
    {
        //提示相应信息
        MyLabel *mylabel = new MyLabel(this,"您被强制退出");
        mylabel->toastr();
        clientSock.disconnectFromHost();
        hasExit = true;
        //这里应该稍微等待
        delay(2000);
        next->clicked();
    }
    else if(type == USER_STATE_CHANGE)
    {
        QString str;
        bool online;
        message.getUserStateChange(str,online);
        int i = 0;
        for(;i<strList.size();i++)
            if(strList[i] == str)
            {
                isOnline[i] = online;
                break;
            }
        if(i == strList.size())
        {
            //提示没有这个用户
            MyLabel *mylabel = new MyLabel(this,"不存在的用户");
            mylabel->toastr();
            return;
        }

        QStandardItem *item;
        //只有在原来没有新消息的情况下才更改头像
        if(!newMessage[i])
        {
            item = standardItemModel->item(i);
            if(!online)
                item->setIcon(QIcon("images/notonline.png"));
            else
                item->setIcon(QIcon("images/online.png"));
        }

        if(!online)
        {
            int j = 0;
            for(;j<userNum;j++)
                if(isOnline[j])
                    break;
            //如果所有人均不在线，那么0号用户（群聊也不在线）
            if(j >= userNum)
                isOnline[0] = false;

            //只有原来没有新消息才改变头像
            if(!newMessage[0])
            {
                item = standardItemModel->item(0);
                item->setIcon(QIcon("images/notonline.png"));
            }
        }
        else if(!isOnline[0])   //如果有人上线并且原来群聊下线，那么群聊上线
        {
            isOnline[0] = true;

            //只有原来没有新消息才改变头像
            if(!newMessage[0])
            {
                item = standardItemModel->item(0);
                item->setIcon(QIcon("images/online.png"));
            }
        }
    }
    else if(type == MESSAGE)
    {
        QString name1,name2,text;
        message.getMsg(name1,name2,text);
        int i = 0,length = 0;

        qDebug()<<"聊天信息包开始";
        for(int i = 0;i<1024;i+=4)
            qDebug()<<*(int*)(((char*)&message) + i);
        qDebug()<<"聊天信息包结束";

        qDebug()<<"收到messag"<<text;

        //如果这条消息是自己发的，就不管了
        if(name1 == name)
            return;

        //是否为群发
        if(name1 == name2)
        {
            chatMessageList[0].append(text);
            chatMessageSendName[0].append(name1);
            length = chatMessageList[0].size();
            isFile[0][length - 1] = false;
            i = 0;
        }
        else
        {
            for(i = 1;i<strList.size();i++)
                if(strList[i] == name1)
                {
                    chatMessageList[i].append(text);
                    chatMessageSendName[i].append(name1);
                    length = chatMessageList[i].size();
                    isFile[i][length - 1] = false;
                    break;
                }
        }
        if(i == strList.size())
        {
            //提示没有这个用户
            MyLabel *mylabel = new MyLabel(this,"不存在的用户");
            mylabel->toastr();
            return;
        }

        //如果说就是当前的界面
        if(i == currentIndex)
        {
            QStandardItem *item;
            item = new QStandardItem(chatMessageSendName[currentIndex][length-1] + ":" + chatMessageList[currentIndex][length-1]);
            if((length - 1) % 2 == 1)
            {
                QLinearGradient linearGrad(QPointF(0, 0), QPointF(200, 200));
                linearGrad.setColorAt(0, QColor(250,250,250));
                linearGrad.setColorAt(1, QColor(235,235,235));
                QBrush brush(linearGrad);
                item->setBackground(brush);
            }
            standardItemModelMessage->appendRow(item);
        }
        //如果不是当前用户界面，那么需要更改对应那个用户的头像提示有新消息产生
        else if(!newMessage[i])
        {
            newMessage[i] = true;
            QStandardItem *item = standardItemModel->item(i);
            item->setIcon(QIcon("images/message.png"));
        }
    }
    else if(type == FILE_NAME)
    {
        QString name1,name2;
        int length,i;
        message.getFileName(name1,name2,receiveFileName);
        for(i = 1;i<strList.size();i++)
            if(strList[i] == name1)
            {
                chatMessageList[i].append(receiveFileName);
                chatMessageSendName[i].append(name1);
                length = chatMessageList[i].size();
                isFile[i][length - 1] = true;
                break;
            }
        if(i == strList.size())
        {
            //提示没有这个用户
            MyLabel *mylabel = new MyLabel(this,"不存在的用户");
            mylabel->toastr();
            return;
        }

        //创建这个文件，如果有则清空
        QFile file(receiveFileName);
        file.open(QIODevice::WriteOnly|QIODevice::Text);
        file.close();

        isReceiveFile = true;
        //接下来要接收若干包

        //如果当前显示的好友就是他的话，直接加上这一项
        if(i == currentIndex)
        {
            QStandardItem *item;
            item = new QStandardItem(QIcon("images/open.ico"),chatMessageSendName[currentIndex][length - 1] + ":" + chatMessageList[currentIndex][length - 1]);
            if((length - 1) % 2 == 1)
            {
                QLinearGradient linearGrad(QPointF(0, 0), QPointF(200, 200));
                linearGrad.setColorAt(0, QColor(250,250,250));
                linearGrad.setColorAt(1, QColor(235,235,235));
                QBrush brush(linearGrad);
                item->setBackground(brush);
            }
            standardItemModelMessage->appendRow(item);
        }
        //如果不是当前用户界面，那么需要更改对应那个用户的头像提示有新消息产生
        else if(!newMessage[i])
        {
            newMessage[i] = true;
            QStandardItem *item = standardItemModel->item(i);
            item->setIcon(QIcon("images/message.png"));
        }

        char msg[LENGTH_MESSAGE];
        int num;
        //循环接收消息
        for(;;)
        {
            _getMessage((char*)&message);
            if(message.getType()==ACK)
                break;
            message.getFileMsg(name1,name2,num,msg);
            qDebug()<<"num="<<num;
            QFile file(receiveFileName);
            file.open(QIODevice::WriteOnly/*|QIODevice::Text*/|QIODevice::Append);
            file.write(msg,num);
            file.close();
        }
        isReceiveFile = false;
        receiveFileName.clear();
        fileMessage.clear();
    }
    else if(type == FILE_MSG)
    {
        if(!isReceiveFile)
        {
            qDebug()<<"不在接受文件状态接收了文件包";
            MyLabel *mylabel = new MyLabel(this,"不在接收文件状态接收了文件包");
            mylabel->toastr();
            return;
        }
        char msg[LENGTH_MESSAGE];
        int num;
        QString name1,name2;
        message.getFileMsg(name1,name2,num,msg);
        qDebug()<<"num="<<num;
        QFile file(receiveFileName);
        file.open(QIODevice::WriteOnly/*|QIODevice::Text*/|QIODevice::Append);
        file.write(msg,num);
        file.close();
    }
    else if(type == ACK)
    {
        //文件内容写入文件
        qDebug()<<"收到ACK";
        qDebug()<<"文件名称为"<<receiveFileName;
        /*QFile file(receiveFileName);
        file.open(QIODevice::WriteOnly|QIODevice::Text);
        char *str = new char[fileMessage.size() + 1];
        QstringToChar(fileMessage,str);
        file.write(str,fileMessage.size());
        file.close();
        */
        //接收文件完毕
        isReceiveFile = false;
        receiveFileName.clear();
        fileMessage.clear();

        qDebug()<<"文件接收完毕";
    }
    else
    {
        //提示不是想要接受的类型
        MyLabel *mylabel = new MyLabel(this,"收到了意料之外的包");
        mylabel->toastr();
        return;
    }
    /***************************************服务器信息处理结束********************************/
}

//读取一个桢
int FileDisplay::getMessage(char*message)
{
    int num;
    for(;;)
    {
        //clientSock.waitForReadyRead(300000);
        num = clientSock.read(message,LENGTH_MESSAGE);
        if(num < 0)
        {
            //提示read错误
            MyLabel *mylabel = new MyLabel(this,"getMessage失败");
            mylabel->toastr();
            qDebug()<<"num="<<num;
            next->clicked();
        }
        else if(num == 0)
        {
            qDebug()<<"num="<<num;
            continue;
        }
        else if(num < LENGTH_MESSAGE)
        {
            //提示接受的长度过短
            MyLabel *mylabel = new MyLabel(this,"接收的桢长度过短");
            mylabel->toastr();
            qDebug()<<"num="<<num;
            next->clicked();
        }
        else
            break;
    }
    return num;
}

//阻塞方式读取一个桢
int FileDisplay::_getMessage(char*message)
{
    int num;
    for(;;)
    {
        //等待时间很短，这样可以更快响应服务器发送信息
        clientSock.waitForReadyRead(10);
        num = clientSock.read(message,LENGTH_MESSAGE);
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

//点击更改密码
void FileDisplay::on_pushButton_3_clicked()
{
    startChangePassword.clicked();
}

//点击更换皮肤
void FileDisplay::on_pushButton_2_clicked()
{
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    QString num1 = QString::number(qrand() % 256);
    QString num2 = QString::number(qrand() % 256);
    QString num3 = QString::number(qrand() % 256);
    this->setStyleSheet("background-color:rgb(" + num1 + "," + num2 + "," + num3 + ")");
}

//发送更改密码报文
void FileDisplay::newPassword(QString newpassword)
{
    /**********************向服务器发送新密码*******************************/
    Message message;
    message.setPassword(newpassword);
    clientSock.write((char*)&message,LENGTH_MESSAGE);
    if(!clientSock.waitForBytesWritten())
    {
        //发送更改密码信息失败
        MyLabel *mylabel = new MyLabel(this,"发送密码信息失败");
        mylabel->toastr();
        return;
    }
    password = newpassword;
    /****************************向服务器发送密码结束************************/
}

//gbk转utf8
QString GBK2UTF8(const QString &inStr)
{
    QTextCodec *gbk = QTextCodec::codecForName("GB18030");

    QString g2u = gbk->toUnicode(gbk->fromUnicode(inStr));			  // gbk  convert utf8
    return g2u;
}

//utf8转gbk
QString UTF82GBK(const QString &inStr)
{
    QTextCodec *gbk = QTextCodec::codecForName("GB18030");

    QString utf2gbk = gbk->toUnicode(inStr.toLocal8Bit());
    return utf2gbk;
}

//延迟毫秒
void delay(unsigned int msec)
{
    QTime _Timer = QTime::currentTime().addMSecs(msec);

    while( QTime::currentTime() < _Timer )

    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

//断开连接
void FileDisplay::ClientBreak()
{
    disConnect = true;
    ui->label_2->setText(name+"(断开)");
    this->ui->pushButton->setEnabled(false);
    this->ui->pushButton_2->setEnabled(false);
    this->ui->pushButton_3->setEnabled(false);
    this->ui->pushButton_4->setEnabled(false);
    /*qDebug()<<"server退出";

    disconnect(&clientSock);

    //获取端口号
    quint16 portNetwork = port.toUInt();
    for(;;)
    {
        qDebug()<<"重连";
        for(int i = 0;i<userNum;i++)
        {
            chatMessageList[i].clear();
            chatMessageSendName[i].clear();
        }
        strList.clear();

        //连接至服务器
        clientSock.connectToHost(ip,portNetwork);

        //每四秒重连
        if(!clientSock.waitForConnected(4000))
        {
            //提示相应信息
            MyLabel *mylabel = new MyLabel(this,"再次连接服务器失败");
            mylabel->toastr();
            continue;
        }

        delay(2000);
        */
        /**********************************与服务器进行相应信息的交互******************************************/
        //发送用户名和密码
        /*Message message;
        message.setUserNamePassword(name,password);

        clientSock.write((char*)&message,LENGTH_MESSAGE);
        if(!clientSock.waitForBytesWritten())
        {
            //提示发送失败
            MyLabel *mylabel = new MyLabel(this,"发送用户名和密码失败");
            mylabel->toastr();
            clientSock.close();
            continue;
        }

        qDebug()<<"连接成功";

        if(getMessage((char*)&message) < 0 || message.getType() == NAK)
        {
            //提示登陆失败
            MyLabel *mylabel = new MyLabel(this,"账号或密码错误");
            mylabel->toastr();

            clientSock.close();
            continue;
        }

        qDebug()<<"ack success";

        //读取是否强制登出
        if(getMessage((char*)&message) < 0)
        {
            //提示信息
            MyLabel *mylabel = new MyLabel(this,"读取信息失败");
            mylabel->toastr();

            clientSock.close();
            continue;
        }

        //读取可浏览多少条历史记录
        if(getMessage((char*)&message) < 0)
        {
            //提示登陆失败
            MyLabel *mylabel = new MyLabel(this,"读取历史记录条数失败");
            mylabel->toastr();

            clientSock.close();
            continue;
        }
        message.getScanMessageNum(scanMessageNum);

        //读取总人数
        if(getMessage((char*)&message) < 0)
        {
            //提示登陆失败
            MyLabel *mylabel = new MyLabel(this,"读取总人数失败");
            mylabel->toastr();

            clientSock.close();
            continue;
        }
        message.getTotalUserNum(userNum);

        QString sendName,receiveName,msg;
        bool online;
        bool onlineFirst = false;
        bool end = false;
        //接收每个用户的聊天记录信息
        for(int i = 0;i<userNum;i++)
        {
            if(getMessage((char*)&message) < 0)
            {
                //提示登陆失败
                MyLabel *mylabel = new MyLabel(this,"读取用户名称及在线状态失败");
                mylabel->toastr();

                clientSock.close();
                end = true;
                break;
            }
            message.getUserState(sendName,online);


            if(i == 0)
                strList.append("[群聊]");
            else
            {
                strList.append(sendName);
                isOnline[i] = online;
                if(online)
                    onlineFirst = true;
            }

            bool inlineEnd = false;
            for(int j = 0;;j++)
            {
                if(getMessage((char*)&message) < 0)
                {
                    //提示登陆失败
                    MyLabel *mylabel = new MyLabel(this,"读取聊天记录失败");
                    mylabel->toastr();

                    clientSock.close();
                    inlineEnd = true;
                    break;
                }
                //聊天记录接收完毕
                if(message.getType() == ACK)
                    break;
                message.getPassChatMsg(sendName,receiveName,isFile[i][j],msg);
                chatMessageList[i].append(msg);
                chatMessageSendName[i].append(sendName);
            }
            if(inlineEnd)
            {
                end = true;
                break;
            }
        }
        if(end)
            continue;
        //群聊用户的在线情况
        isOnline[0] = onlineFirst;

        if(getMessage((char*)&message) < 0)
        {
            //提示登陆失败
            MyLabel *mylabel = new MyLabel(this,"读取是否更改密码失败");
            mylabel->toastr();

            clientSock.close();
            continue;
        }

        qDebug()<<"重连成功";
        break;
    }

    connect(&clientSock, SIGNAL(readyRead()), this, SLOT(ClientReadData()));
    connect(&clientSock, SIGNAL(disconnected()), this, SLOT(ClientBreak()));

    ui->label_2->setText(name+"(在线)");
    ui->label_3->setText("可看记录数:" + QString::number(scanMessageNum));

    standardItemModel->clear();
    standardItemModelMessage->clear();

    //将要显示的内容放入表中
    for(int i = 0;i<strList.size();i++)
    {
        QStandardItem *item;
        if(isOnline[i])
            item = new QStandardItem(QIcon("images/online.png"),strList[i]);
        else
            item = new QStandardItem(QIcon("images/notonline.png"),strList[i]);
        if(i % 2 == 1)
        {
            QLinearGradient linearGrad(QPointF(0, 0), QPointF(200, 200));
            linearGrad.setColorAt(0, QColor(250,250,250));
            linearGrad.setColorAt(1, QColor(235,235,235));
            QBrush brush(linearGrad);
            item->setBackground(brush);
        }
        standardItemModel->appendRow(item);
    }
    ui->listView->setIconSize(QSize(40,40));
    ui->listView->setGridSize(QSize(45,45));
    ui->listView->setLayoutDirection(Qt::LeftToRight);

    //设置内容
    ui->listView->setModel(standardItemModel);

    //将要显示的内容放入表中
    for(int i = 0;i<chatMessageList[currentIndex].size();i++)
    {
        QStandardItem *item;
        if(isFile[currentIndex][i])
            item = new QStandardItem(QIcon("images/open.ico"),chatMessageSendName[currentIndex][i] + ":" + chatMessageList[currentIndex][i]);
        else
            item = new QStandardItem(chatMessageSendName[currentIndex][i] + ":" + chatMessageList[currentIndex][i]);
        if(i % 2 == 1)
        {
            QLinearGradient linearGrad(QPointF(0, 0), QPointF(200, 200));
            linearGrad.setColorAt(0, QColor(250,250,250));
            linearGrad.setColorAt(1, QColor(235,235,235));
            QBrush brush(linearGrad);
            item->setBackground(brush);
        }
        standardItemModelMessage->appendRow(item);
    }
    ui->listView_2->setGridSize(QSize(45,45));
    ui->listView_2->setLayoutDirection(Qt::LeftToRight);

    //设置内容
    ui->listView_2->setModel(standardItemModelMessage);

    //初始显示第一个用户的聊天信息
    ui->label->setText(strList[currentIndex]);

    this->setDisabled(true);

    disConnect = false;*/
}

//点击键盘
/*void FileDisplay::keyPressEvent(QKeyEvent *k)
{
    if(state!=NOT_COMPLETED&&(k->key() == Qt::Key_A||k->key() == Qt::Key_D||k->key() == Qt::Key_W||k->key() == Qt::Key_S))
    {
        state = NOT_COMPLETED;
        ui->label_state->setText("未开始");
        ui->label_num_step->setText(" ");
        ui->label_num_search->setText(" ");
        ui->stepDisplay->clear();
    }

    switch(k->key())
    {
    case(Qt::Key_A):
        if(initial.y_location>0)
        {
            UiChange(initial.chess,initial.x_location,initial.y_location,initial.x_location,initial.y_location-1);
            ChessChange(2);
            QString str;
            for(int i = 0;i<CHESS_SIZE;i++)
                for(int j = 0;j<CHESS_SIZE;j++)
                    str.push_back(char(initial.chess[i][j] + '0'));
            ui->start_chess->setText(str);
            ui->start_chess->setStyleSheet("QLineEdit{font: 75 12pt Arial}");
        }
        break;
    case(Qt::Key_D):
        if(initial.y_location<2)
        {
            UiChange(initial.chess,initial.x_location,initial.y_location,initial.x_location,initial.y_location+1);
            ChessChange(3);
            QString str;
            for(int i = 0;i<CHESS_SIZE;i++)
                for(int j = 0;j<CHESS_SIZE;j++)
                    str.push_back(char(initial.chess[i][j] + '0'));
            ui->start_chess->setText(str);
            ui->start_chess->setStyleSheet("QLineEdit{font: 75 12pt Arial}");
        }
        break;
    case(Qt::Key_W):
        if(initial.x_location>0)
        {
            UiChange(initial.chess,initial.x_location,initial.y_location,initial.x_location-1,initial.y_location);
            ChessChange(0);
            QString str;
            for(int i = 0;i<CHESS_SIZE;i++)
                for(int j = 0;j<CHESS_SIZE;j++)
                    str.push_back(char(initial.chess[i][j] + '0'));
            ui->start_chess->setText(str);
            ui->start_chess->setStyleSheet("QLineEdit{font: 75 12pt Arial}");
        }
        break;
    case(Qt::Key_S):
        if(initial.x_location<2)
        {

            UiChange(initial.chess,initial.x_location,initial.y_location,initial.x_location+1,initial.y_location);
            ChessChange(1);
            QString str;
            for(int i = 0;i<CHESS_SIZE;i++)
                for(int j = 0;j<CHESS_SIZE;j++)
                    str.push_back(char(initial.chess[i][j] + '0'));
            ui->start_chess->setStyleSheet("QLineEdit{font: 75 12pt Arial}");
        }
        break;
    }

    processing = false;
}*/
