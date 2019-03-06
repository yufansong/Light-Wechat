#include "message.h"

//Qstring转char
void QstringToChar(QString  s1, char *s2, bool is_file)
{
    int len=s1.length();
    char* ptr;
    QByteArray ba;
    ba = s1.toUtf8();
    ptr = ba.data();
    len = ba.length();
    memcpy(s2,ptr,unsigned (len));//转换后ptr[0]为'\0'
    if(!is_file)
        s2[len]='\0';
}

//QString 转QString
//需要参数length代表长度，默认为0
//参数is_file为true时length有效，默认为false
void CharToQstring(QString  &s1, char *s2, int length, bool is_file)
{
    if(!is_file)//结尾必有尾零
    {
        QString  temp(s2);
        s1=temp;
    }
    else//中间可能尾零
    {
        int len_t, i=0;
        QString  s;
        while(i<length)
        {
            QString  temp(s2+i);
            len_t=temp.length();
            i+=len_t+1;
            s+='\0';
            s+=temp;
        }
        s1=s;
    }
}

//将type转换为网络序
void Message::hton_t()
{
    int t = qToBigEndian((qint32)type);
    memcpy((void *)&type, (void *)&t, 4);
}

//将type转为主机序
/*void Message::ntoh_t()
{
    int t = qFromBigEndian((qint32)type);
    memcpy((void *)&type, (void *)&t, 4);
}*/

//将type转为主机序
Type Message::ntoh_t()
{

    int t = qFromBigEndian((qint32)type);
    Type s;
    memcpy((void *)&s, (void *)&t, 4);
    return s;
}


//获取包的类型
/*Type Message::getType()
{
    ntoh_t();
    return type;
}*/

//获取包的类型
Type Message::getType()
{
    Type t;
    t=ntoh_t();
    return t;
}

//根据用户名和密码信息设置报文内容,空余位置填尾零
//假设不会出错，范围均在控制之内
bool Message::setUserNamePassword(QString userName,QString password)
{
    QstringToChar(userName,s1);
    QstringToChar(password,s2);
    type=LOGIN;
    hton_t();
    return true;
}

//设置ACK
bool Message::setAck(QString sendUserName,QString receiveUserName)
{
    type=ACK;
    hton_t();
    QstringToChar(sendUserName,s1);
    QstringToChar(receiveUserName,s2);
    return true;
}

//获取总人数
bool Message::getTotalUserNum(int &num)
{
    number=qFromBigEndian((qint32)number);
    num=number;
    return true;
}

//读配置
bool Message::getScanMessageNum(int &num)
{
    number=qFromBigEndian((qint32)number);
    num=number;
    return true;
}

//获取用户状态
bool Message::getUserState(QString &userName,bool&isOnline)
{
    CharToQstring(userName,s1);
    number=qFromBigEndian((qint32)number);
    isOnline=number==1?true:false;
    return true;
}

//从报文解析后内容取得消息各部分
bool Message::getPassChatMsg(QString &sendUserName,QString &getUserName,bool &isFile,QString &message)
{
    number=qFromBigEndian((qint32)number);
    isFile=number==1?true:false;
    CharToQstring(sendUserName,s1);
    CharToQstring(getUserName,s2);
    CharToQstring(message,s3);
    return true;
}

//更改密码时发的包
bool Message::setPassword(QString password)
{
    type=PASSWORD;
    hton_t();
    QstringToChar(password,s2);
    return true;
}

//发当前消息
bool Message::setMsg(QString sendName,QString receiveName,QString message)
{
    type=MESSAGE;
    hton_t();
    QstringToChar(sendName,s1);
    QstringToChar(receiveName,s2);
    QstringToChar(message,s3);
    return true;
}

//接收消息并解析
bool Message::getMsg(QString &sendName,QString &receiveName,QString &message)
{
    CharToQstring(sendName,s1);
    CharToQstring(receiveName,s2);
    CharToQstring(message,s3);
    return true;
}

//传文件消息
bool Message::setFileName(QString sendName,QString receiveName,QString filename)
{
    type=FILE_NAME;
    hton_t();
    QstringToChar(sendName,s1);
    QstringToChar(receiveName,s2);
    QstringToChar(filename,s3);

    qDebug()<<"setFileName 成功";
    return true;
}

//获取文件消息，得到文件名
bool Message::getFileName(QString &sendName,QString &receiveName,QString &filename)
{
    CharToQstring(sendName,s1);
    CharToQstring(receiveName,s2);
    CharToQstring(filename,s3);
    return true;
}

//发文件内容
/*bool Message::setFileMsg(QString sendName,QString receiveName,QString message)
{
    type=FILE_MSG;
    hton_t();
    QstringToChar(sendName,s1);
    QstringToChar(receiveName,s2);
    QstringToChar(message,s3,true);
    number=message.length();
    number=qFromBigEndian((qint32)number);
    return true;
}*/

//收取文件内容
/*bool Message::getFileMsg(QString &sendName,QString &receiveName,QString &message)
{
    number=qToBigEndian((qint32)number);
    CharToQstring(sendName,s1);
    CharToQstring(receiveName,s2);
    CharToQstring(message,s3,number,true);
    return true;
}*/

//发文件内容
bool Message::setFileMsg(QString sendName,QString receiveName,int length,const char *message)
{
    type=FILE_MSG;
    hton_t();
    QstringToChar(sendName,s1);
    QstringToChar(receiveName,s2);
    memcpy(s3,message,length);
    number=length;
    number=qToBigEndian(number);
    return true;
}

//收取文件内容
bool Message::getFileMsg(QString &sendName,QString &receiveName,int &length,char *message)
{
    number=qFromBigEndian(number);
    length=number;
    CharToQstring(sendName,s1);
    CharToQstring(receiveName,s2);
    memcpy(message,s3,length);
    return true;
}

/*
//发文件内容
bool Message::setFileMsg(QString sendName,QString receiveName,int length,const char *message)
{
    type=FILE_MSG;
    hton_t();
    QstringToChar(sendName,s1);
    QstringToChar(receiveName,s2);
    strncpy(s3,message,length);
    number=length;
    number=qToBigEndian(number);
    return true;
}

//收取文件内容
bool Message::getFileMsg(QString &sendName,QString &receiveName,int &length,char *message)
{
    number=qFromBigEndian(number);
    length=number;
    CharToQstring(sendName,s1);
    CharToQstring(receiveName,s2);
    strncpy(message,s3,length);
    return true;
}
*/

//获取用户改变状态包
bool Message::getUserStateChange(QString &userName,bool &isOnline)
{
    CharToQstring(userName,s1);
    number=qFromBigEndian((qint32)number);
    isOnline=number==1?true:false;
    return true;
}

//客户端退出包
bool Message::setClientExit()
{
    type=CLIENT_EXIT;
    hton_t();
    return true;
}
