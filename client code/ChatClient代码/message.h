/*#ifndef MESSAGE_H
#define MESSAGE_H

#include <QString>

typedef enum Type
{
    LOGIN,              		//登陆用户名和密码
    ACK,                		//yes
    NAK,                		//no
    TOTAL_USER_NUM,    			//总用户人数
    NAME_MSG,           		//用户名称以及是否在线
    PASS_CHAT_MSG,      		//一条聊天记录
    CHANGE_PASSWORD,    		//更改密码
    NOT_CHANGE_PASSWORD,		//不更改密码
    MESSAGE,            		//消息
    PASSWORD,           		//密码
    FILE_NAME,         			//文件名称包
    FILE_MSG,           		//文件信息包
    CLIENT_EXIT,        		//客户端退出
    FORCE_EXIT,         		//客户端前置被登出
    USER_STATE_CHANGE,  		//其他用户信息改变
    MSG_NUM,            		//配置信息中可查看的聊天记录条数
    REPLACE,					//顶掉别人
    NOT_REPLACE					//没有顶掉别人
}Type;

class Message
{
public:
    Message();

private:
    Type type;
    char s1[20];
    char s2[20];
    int number;
    char s3[976];

public:
    //获取包的类型
    Type getType();

    //构造用户名密码包
    bool setUserNamePassword(QString userName,QString password);

    //构造确认包
    bool setAck(QString sendUserName,QString receiveUserName);

    //解析用户可浏览条数配置信息包
    bool getScanMessageNum(int &num);

    //解析总用户数包
    bool getTotalUserNum(int &num);

    //解析用户名和在线信息包
    bool getUserState(QString userName,bool&isOnline);

    //解析聊天记录包
    bool getPassChatMsg(QString sendName,QString receiveName,bool&isFile,QString msg);

    //构造聊天信息包
    bool setMsg(QString sendName,QString receiveName,QString msg);

    //构造文件名称包
    bool setFileName(QString sendName,QString receiveName,QString fileName);

    //构造文件信息包，这个msg的长度最大为976
    bool setFileMsg(QString sendName,QString receiveName,QString msg);

    //解析用户状态变化包
    bool getUserStateChange(QString userName,bool&isOnline);

    //解析聊天信息包
    bool getMsg(QString sendName,QString receiveName,QString msg);

    //解析文件名称包
    bool getFileName(QString sendName,QString receiveName,QString fileName);

    //解析文件内容包
    bool getFileMsg(QString sendName,QString receiveName,QString msg);

    //构造密码包
    bool setPassword(QString password);

    //构造用户端退出
    bool setClientExit();
};

#endif // MESSAGE_H

//可浏览信息条数尚未完成
*/

#ifndef MESSAGE_H
#define MESSAGE_H

#include <QString>
#include <QtEndian>
#include <QDebug>

#define S1_MAX_LENGTH 20
#define S2_MAX_LENGTH 20
#define MSG_MAX_LENGTH 976
#define MESSAGE_LENGTH 1024
void QstringToChar(QString s1, char *s2, bool is_file=false);
void CharToQstring(QString &s1, char *s2, int length = 0, bool is_file = false);
typedef enum Type
{
    LOGIN,                  //登录请求,C->S
    ACK,                    //确认，双方均可发送
    NAK,                    //No
    TOTAL_USER_NUM,         //总人数S->C
    NAME_MSG,               //用户信息S->C
    PASS_CHAT_MSG,          //历史信息S->C
    CHANGE_PASSWORD,        //改密码通知S->C
    NOT_CHANGE_PASSWORD,    //不改密码通知S->C
    MESSAGE,                //实时消息传输C->S,S->C
    PASSWORD,               //新的密码 C->S
    FILE_NAME,              //传文件消息C->S
    FILE_MSG,               //传文件内容C->S
    CLIENT_EXIT,            //客户端登出C->S
    FORCE_EXIT,             //强制登出S->C
    USER_STATE_CHANGE,      //有其他用户登入或下线
    MSG_NUM,                //消息条数（配置信息，用户设置可读消息数）
    REPLACE,				//顶掉别人
    NOT_REPLACE				//没有顶掉别人
} Type;

class Message
{
    private:
        Type type;//枚举类型
        char s1[S1_MAX_LENGTH];
        char s2[S2_MAX_LENGTH];
        int number;
        char s3[MSG_MAX_LENGTH];
    public:
        void hton_t();
        Type ntoh_t();
        Type getType();
        bool setUserNamePassword(QString userName,QString password);
        bool setAck(QString sendUserName,QString receiveUserName);
        bool getScanMessageNum(int &num);
        bool getTotalUserNum(int&num);
        bool getUserState(QString &userName,bool &isOnline);
        bool getPassChatMsg(QString &sendUserName,QString &getUserName,bool &isFile,QString &message);
        bool setMsg(QString sendName,QString receiveName,QString message);
        bool getMsg(QString &sendName,QString &receiveName,QString &message);
        bool setFileName(QString sendName,QString receiveName,QString filename);
        bool getFileName(QString &sendName,QString &receiveName,QString &filename);
        bool setFileMsg(QString sendName,QString receiveName,int length,const char *message);
        bool getFileMsg(QString &sendName,QString &receiveName,int &length,char *message);
        //bool setFileMsg(QString sendName,QString receiveName,QString message);
        //bool getFileMsg(QString &sendName,QString &receiveName,QString &message);
        bool getUserStateChange(QString &userName,bool &isOnline);
        bool setPassword(QString password);
        bool setClientExit();
};

#endif // MESSAGE_H
