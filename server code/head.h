// #ifndef HEAD
// #define HEAD
//cpp lib
#include <iostream>
#include <netinet/in.h> //LINUX C++
//c lib
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <signal.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream> // cin,cout等
#include <iomanip>  // setw等
#include <mysql.h>  // mysql特有
#include <stdbool.h>
#include <string>
#include <stdio.h>
#include <time.h>

/*------------------宏定义-----------------------*/
#define MAXNUM_CLIENT 10
#define MAXNUM_MSG 1024
#define MAXNUM_UserName 20
#define MAXNUM_PassWord 20
#define MAXNUM_ScanMessage 200
#define MAXNUM_ChatMsg 970

#define S1_MAX_LENGTH 20
#define S2_MAX_LENGTH 20
#define MSG_MAX_LENGTH 976
#define MESSAGE_LENGTH 1024

#define MAXNUM_LOGMSG 1024
#define LOGFILE "log.txt"


/*------------------结构体定义-----------------------*/
struct Client
{
    int connect_fd;
    int state;
    char username[MAXNUM_UserName];
};

enum Type
{
    LOGIN,               //登录请求,C->S
    ACK,                 //确认，双方均可发送
    NAK,                 //No
    TOTAL_USER_NUM,      //总人数S->C
    NAME_MSG,            //用户信息S->C
    PASS_CHAT_MSG,       //历史信息S->C
    CHANGE_PASSWORD,     //改密码通知S->C
    NOT_CHANGE_PASSWORD, //不改密码通知S->C
    MESSAGE,             //实时消息传输C->S,S->C
    PASSWORD,            //新的密码 C->S
    FILE_NAME,           //传文件消息C->S
    FILE_MSG,            //传文件内容C->S
    CLIENT_EXIT,         //客户端登出C->S
    FORCE_EXIT,          //强制登出S->C
    USER_STATE_CHANGE,   //有其他用户登入或下线
    MSG_NUM,             //消息条数（配置信息，用户设置可读消息数）
    REPLACE,             //顶掉别人
    NOT_REPLACE //没有顶掉别人
};


class Message{
private:
    Type type; //枚举类型
    char s1[S1_MAX_LENGTH];
    char s2[S2_MAX_LENGTH];
    int number;
    char s3[MSG_MAX_LENGTH];

public:
  Type ntoh_t();
  void hton_t();
  //Message();
  Type getType();
  bool setUserNamePassword(char *userName, char *password);
  bool getUserNamePassword(char *userName, char *password);
  bool setAck(const char *sendUserName, const char *receiveUserName);
  bool getAck(char *sendName, char *receiveName);
  bool setNak();
  bool setReplace();
  bool setNotReplace();
  bool setScanMessageNum(int num);
  bool getScanMessageNum(int &num);
  bool setTotalUserNum(int number);
  bool getTotalUserNum(int &number);
  bool setUserState(char *userName, bool isOnline);
  bool getUserState(char *userName, bool &isOnline);
  bool setPassChatMsg(char *sendUserName, char *getUserName, bool isFile, char *message);
  bool getPassChatMsg(char *sendUserName, char *getUserName, bool &isFile, char *message);
  bool setChangePassword();
  bool setNotChangePassword();
  bool setMsg(char *sendName, char *receiveName, char *message);
  bool getMsg(char *sendName, char *receiveName, char *message);
  bool getFileMsg(char *sendName, char *receiveName);
  bool setPassword(char *password);
  bool getPassword(char *password);
  bool setFileName(char *sendName, char *receiveName, char *filename);
  bool getFileName(char *sendName, char *receiveName, char *filename);
  bool setUserStateChange(char *userName, bool isOnline);
  bool getUserStateChange(char *userName, bool &isOnline);
  bool setClientExit();
//   bool setClientExit(char *username);
  bool getClientExit(char *username);
  bool setForceExit();
};

/*
user(
    userName(key number),
    password,
    scanMessageNum,
    online,
    isFirstLogin)

information(
    messageID(key number),
    sendName,
    receiveName,
    message,
    isFile)
如果sendName和receiveName相同则表示sendName发给全体的信息
*/
class MyDB
{
  protected:
    MYSQL *mysql;
    MYSQL_RES *result;
    MYSQL_ROW row;
    int message_num;

  public:
    MyDB();
    ~MyDB();

    ///////////////////
    void print_result(); //自己测试用函数，可忽略
    ///////////////////

    void insert_user();
    void encode(const char *password, char *code);
    bool getUserNum(int &number);                                                             //取得用户总人数
    int  getUserName(char **namelist, bool *isOnline); //获取全部用户名称、是否在线、可浏览信息条数
    bool getCanlogin(char *name, char *password, bool &canlogin, bool &isFirstLogin);         //获取某用户是否可登陆以及是否是第一次登陆
    int  getMessage(char *name1, char *name2, char **MessageList,bool *flag,bool *isFile); //获取两个人之间发的所有信息
    bool setPassword(char *name, char *password);                                             //更改某用户的密码
    bool setUserState(char *name, bool login);                                //获取用户的登陆状态
    bool addMessage(char *SendName, char *ReceiveName, char *message, bool type);             //添加聊天记录消息
    bool setFirstLogin(char *username, bool login);                                           //设置用户的首次登陆状态
    int  getscanMessageNumber(char *name, int &scanMessageNumber);
};

/*------------------全局变量定义-----------------------*/
// extern int state[MAXNUM_CLIENT];//必须加static，否则多个文件链接编译会出错
// extern int connet_fdbuf[MAXNUM_CLIENT];
extern Client client[MAXNUM_CLIENT];
//约定state[i]的值说明如下：（初值为0）
//0：第i个链接尚未建立
//1：第i个链接接受登陆账户密码
//2：第i个链接登陆成功后发送配置文件
//3：第i个链接首次登陆，修改密码
//4：第i个链接客户端发信息给他人
//5：第i个链接转发文件
//6：第i个链接退出
extern MyDB mydb;
/*------------------交互函数定义-----------------------*/
int tcp_connect(int x, int socket_fd, fd_set *p_allfd, int &maxfd);
int tcp_disconnet(int x, fd_set *p_allfd);
int login(Message *p_msg, int x, fd_set *p_allset);
int Send_to_Client(int x, Message *p_msg, const char *TypeStr);   //修改读写
int Read_from_Client(int x, Message *p_msg, const char *TypeStr); //修改读写
int send_ACK(int x);
int send_NAK(int x);
int send_config_friend(int x);
int change_password_first(int x,const bool isFirstLogin);
int change_password_not_first(int x, Message *p_msg);
int transmit_exit_normal(int x, const bool login);
int multi_login(int x, fd_set *p_allfd);
int transmit_ACK(int x,Message *p_msg);
int transmit_exit_force(int x);
int transmit_replace_someone(int x, const bool flag);
int Transmit_to_Client(int x, char *sendUserName, char *getUserName, Message *p_msg); //转发信息
int transmit_msg(int x, Message *p_msg, bool isFile);
int transmit_file(int x, Message *p_msg);
int send_ChangeState(int x,const bool isOnline);
void print_to_log(const char *s);
/*------------------测试函数定义-----------------------*/
void test(); //测试功能函数

// #endif