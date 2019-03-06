#include "chatdialog.h"

ChatDialog::ChatDialog(QWidget *parent)
{
    Q_UNUSED(parent);
    iRotateVal=0;
    isAnimating=false;
    setAttribute(Qt::WA_TranslucentBackground, true);
    setWindowFlags(Qt::FramelessWindowHint /*| Qt::WindowStaysOnTopHint*/);

    //最小化图标
    mSysTrayIcon = new QSystemTrayIcon(this);
    QIcon icon = QIcon("images/chat.ico");
    mSysTrayIcon->setIcon(icon);
    mSysTrayIcon->setToolTip(QObject::trUtf8("畅聊"));
    //给QSystemTrayIcon添加槽函数
    connect(mSysTrayIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason)));

    // 设置页面大小
    this->setFixedSize(1000,800);

    //加入登陆界面
    login = new MyLogin();
    QObject::connect(&login->loginSuccess,SIGNAL(clicked()),this,SLOT(nextPage()));
    QObject::connect(login->endApp,SIGNAL(clicked()),this,SLOT(end()));
    login->setStyleSheet("background-color:rgb(240,240,240)");
    this->addWidget(login);

    //加入聊天界面
    filedisplay = new FileDisplay;
    QObject::connect(filedisplay->next,SIGNAL(clicked()),this,SLOT(end()));
    QObject::connect(&filedisplay->startChangePassword,SIGNAL(clicked()),this,SLOT(changePassword()));
    QObject::connect(filedisplay->min,SIGNAL(clicked()),this,SLOT(minWindow()));
    filedisplay->setStyleSheet("background-color:rgb(240,240,240)");
    this->addWidget(filedisplay);

    login->setSocket(&filedisplay->clientSock);

    //加入改密界面
    newpassword = new NewPassword();
    QObject::connect(&newpassword->endPassword,SIGNAL(clicked()),this,SLOT(changePasswordEnd()));
    newpassword->setStyleSheet("background-color:rgb(240,240,240)");
    this->addWidget(newpassword);

    //当前不处于拖动状态
    m_draging = false;
}

ChatDialog::~ChatDialog()
{
    delete login;
    delete filedisplay;
    delete newpassword;
    delete mSysTrayIcon;
}

//画图
void ChatDialog::paintEvent(QPaintEvent *event)
{
    if(isAnimating)
    {
        if(iRotateVal > 90)
        {
            QPixmap pixmap(widget(nextIndex)->size());
            widget(nextIndex)->render(&pixmap);
            QPainter painter(this);

            QTransform transform;
            transform.translate(width()/2, 0);
            transform.rotate(iRotateVal+180,Qt::YAxis);
            painter.setTransform(transform);
            painter.drawPixmap(-1*width()/2,0,pixmap);
        } else {
            QPixmap pixmap(currentWidget()->size());
            currentWidget()->render(&pixmap);
            QPainter painter(this);

            QTransform transform;
            transform.translate(width()/2, 0);
            transform.rotate(iRotateVal,Qt::YAxis);
            painter.setTransform(transform);
            painter.drawPixmap(-1*width()/2,0,pixmap);
        }
    } else {
        QWidget::paintEvent(event);
    }
}

//下一页
void ChatDialog::nextPage()
{
    //如果当前处于登陆界面，那么根据登陆界面得到的信息对聊天界面作出相应更改
    if(currentIndex() == 0)
    {
        /***************将服务器取得的信息传入聊天界面类进行显示************************************/
        filedisplay->setContent(login->userName,
                                login->password,
                                login->nameList,
                                login->isOnline,
                                login->userNum,
                                login->chatMessageList,
                                login->chatMessageSendName,
                                login->isFile,
                                login->scanMessageNum,
                                login->haveToChangePassword,
                                login->ip,
                                login->port
                                );
        /********************************传入聊天界面类结束************************************/

        /*
        QStringList list,message[5],messageName[5];
        bool online[5];
        int scanMessageNum = 100;
        bool file[5][1000];
        login->haveToChangePassword = true;
        for(int i = 0;i<5;i++)
        {
            list.append("用户"+QString::number(i));
            //if(i % 2)
                online[i] = false;
            //else
            //    online[i] = true;

            for(int j = 0;j<10;j++)
            {
                message[i].append("message"+QString::number(j));
                messageName[i].append("user"+QString::number(j));
                if(j % 2)
                    file[i][j] = true;
                else
                    file[i][j] = false;
            }
        }
        online[0] = true;
        filedisplay->setContent(login->userName,
                                login->password,
                                list,online,
                                5,
                                message,
                                messageName,
                                file,
                                scanMessageNum,
                                login->haveToChangePassword
                                );
        */
        if(login->haveToChangePassword)
        {
            //qDebug()<<"replace = "<<login->replace;
            if(login->replace)
            {
                MyLabel *mylabel = new MyLabel(this,"该账号原登陆强制下线");
                mylabel->toastr();
                delay(2000);
                //qDebug()<<"强制退出";
            }
            newpassword->pushButtonCancel->setEnabled(false);
            newpassword->setPasswordPre(filedisplay->password);
            rotate(2);
        }
        else
        {
            //qDebug()<<"replace = "<<login->replace;
            if(login->replace)
            {
                MyLabel *mylabel = new MyLabel(this,"该账号原登陆强制下线");
                mylabel->toastr();
                delay(2000);
                //qDebug()<<"强制退出";
            }
            rotate(1);
        }
    }
}

//关闭
void ChatDialog::end()
{
    if(currentIndex() == 0)
    {
    }
    else if(currentIndex() == 1 && !filedisplay->hasExit)
    {
        /**************************临死之前发送一个包给服务器*****************************/
        Message message;
        message.setClientExit();
        filedisplay->clientSock.write((char*)&message,LENGTH_MESSAGE);
        if(!filedisplay->clientSock.waitForBytesWritten())
        {
            //提示相应信息
            MyLabel *mylabel = new MyLabel(this,"发送结束包失败");
            mylabel->toastr();
        }
        else
        {
            qDebug()<<"发送结束包成功";
        }
        /****************************发送临死包结束**************************************/
    }
    close();
}

//跳转
void ChatDialog::rotate(int index)
{

    if(isAnimating) return;
    nextIndex = index;
    int offsetx=frameRect().width();
    int offsety=frameRect().height();
    widget(index)->setGeometry ( 0,  0, offsetx, offsety );
    QPropertyAnimation *animnow = new QPropertyAnimation(this,"rotateVal");
    animnow->setDuration(500);
    animnow->setEasingCurve(QEasingCurve::Linear);
    animnow->setStartValue(0);
    animnow->setEndValue(180);
    connect(animnow,SIGNAL(valueChanged(QVariant)),this,SLOT(valChanged(QVariant)));
    connect(animnow,SIGNAL(finished()),this,SLOT(animDone()));
    currentWidget()->hide();
    isAnimating = true;
    animnow->start();

}

//跳转角度
float ChatDialog::rotateVal()
{
    return iRotateVal;
}

//设置跳转角度
void ChatDialog::setRotateVal(float fl)
{
    iRotateVal = fl;
}

//角度改变
void ChatDialog::valChanged(QVariant)
{
    repaint();
}

//结束
void ChatDialog::animDone()
{
    iRotateVal=0;
    isAnimating=false;
    widget(nextIndex)->show();
    widget(nextIndex)->raise();;
    setCurrentWidget(widget(nextIndex));
    repaint();
}

//进入更改密码界面
void ChatDialog::changePassword()
{
    newpassword->setPasswordPre(filedisplay->password);
    rotate(2);
}

//更改密码结束
void ChatDialog::changePasswordEnd()
{
    if(newpassword->password != "")
        filedisplay->newPassword(newpassword->password);
    if(login->haveToChangePassword)
        newpassword->pushButtonCancel->setEnabled(true);
    rotate(1);
}

//鼠标可拖动
void ChatDialog::mousePressEvent(QMouseEvent *event)
{
    m_draging = true;
    if(event->buttons() & Qt::LeftButton)//只响应鼠标左键
    {
        m_startPostion = event->globalPos();
        m_framPostion = frameGeometry().topLeft();
    }
    QWidget::mousePressEvent(event);//调用父类函数保持原按键行为
}

void ChatDialog::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        //offset 偏移位置
        QPoint offset = event->globalPos() - m_startPostion;
        move(m_framPostion + offset);
    }
    QWidget::mouseMoveEvent(event);//调用父类函数保持原按键行为
}

void ChatDialog::mouseReleaseEvent(QMouseEvent *event)
{
    m_draging = false;
    QWidget::mouseReleaseEvent(event);
}

//响应点击托盘图标事件
void ChatDialog::on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason reason)
{
    switch(reason)
    {
        case QSystemTrayIcon::Trigger:
            //单击托盘图标
            break;
        case QSystemTrayIcon::DoubleClick:
            //双击托盘图标
            //双击后显示主程序窗口
            this->show();
            mSysTrayIcon->hide();
            break;
        default:
            break;
    }
}

//最小化
void ChatDialog::minWindow()
{
    this->hide();
    mSysTrayIcon->show();
}
