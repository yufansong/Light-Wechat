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
#include <iostream> // cin,cout��
#include <iomanip>  // setw��
#include <mysql.h>  // mysql����
#include <stdbool.h>
#include <string>
#include <stdio.h>
#include <time.h>

/*------------------�궨��-----------------------*/
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


/*------------------�ṹ�嶨��-----------------------*/
struct Client
{
    int connect_fd;
    int state;
    char username[MAXNUM_UserName];
};

enum Type
{
    LOGIN,               //��¼����,C->S
    ACK,                 //ȷ�ϣ�˫�����ɷ���
    NAK,                 //No
    TOTAL_USER_NUM,      //������S->C
    NAME_MSG,            //�û���ϢS->C
    PASS_CHAT_MSG,       //��ʷ��ϢS->C
    CHANGE_PASSWORD,     //������֪ͨS->C
    NOT_CHANGE_PASSWORD, //��������֪ͨS->C
    MESSAGE,             //ʵʱ��Ϣ����C->S,S->C
    PASSWORD,            //�µ����� C->S
    FILE_NAME,           //���ļ���ϢC->S
    FILE_MSG,            //���ļ�����C->S
    CLIENT_EXIT,         //�ͻ��˵ǳ�C->S
    FORCE_EXIT,          //ǿ�Ƶǳ�S->C
    USER_STATE_CHANGE,   //�������û����������
    MSG_NUM,             //��Ϣ������������Ϣ���û����ÿɶ���Ϣ����
    REPLACE,             //��������
    NOT_REPLACE //û�ж�������
};


class Message{
private:
    Type type; //ö������
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
���sendName��receiveName��ͬ���ʾsendName����ȫ�����Ϣ
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
    void print_result(); //�Լ������ú������ɺ���
    ///////////////////

    void insert_user();
    void encode(const char *password, char *code);
    bool getUserNum(int &number);                                                             //ȡ���û�������
    int  getUserName(char **namelist, bool *isOnline); //��ȡȫ���û����ơ��Ƿ����ߡ��������Ϣ����
    bool getCanlogin(char *name, char *password, bool &canlogin, bool &isFirstLogin);         //��ȡĳ�û��Ƿ�ɵ�½�Լ��Ƿ��ǵ�һ�ε�½
    int  getMessage(char *name1, char *name2, char **MessageList,bool *flag,bool *isFile); //��ȡ������֮�䷢��������Ϣ
    bool setPassword(char *name, char *password);                                             //����ĳ�û�������
    bool setUserState(char *name, bool login);                                //��ȡ�û��ĵ�½״̬
    bool addMessage(char *SendName, char *ReceiveName, char *message, bool type);             //��������¼��Ϣ
    bool setFirstLogin(char *username, bool login);                                           //�����û����״ε�½״̬
    int  getscanMessageNumber(char *name, int &scanMessageNumber);
};

/*------------------ȫ�ֱ�������-----------------------*/
// extern int state[MAXNUM_CLIENT];//�����static���������ļ����ӱ�������
// extern int connet_fdbuf[MAXNUM_CLIENT];
extern Client client[MAXNUM_CLIENT];
//Լ��state[i]��ֵ˵�����£�����ֵΪ0��
//0����i��������δ����
//1����i�����ӽ��ܵ�½�˻�����
//2����i�����ӵ�½�ɹ����������ļ�
//3����i�������״ε�½���޸�����
//4����i�����ӿͻ��˷���Ϣ������
//5����i������ת���ļ�
//6����i�������˳�
extern MyDB mydb;
/*------------------������������-----------------------*/
int tcp_connect(int x, int socket_fd, fd_set *p_allfd, int &maxfd);
int tcp_disconnet(int x, fd_set *p_allfd);
int login(Message *p_msg, int x, fd_set *p_allset);
int Send_to_Client(int x, Message *p_msg, const char *TypeStr);   //�޸Ķ�д
int Read_from_Client(int x, Message *p_msg, const char *TypeStr); //�޸Ķ�д
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
int Transmit_to_Client(int x, char *sendUserName, char *getUserName, Message *p_msg); //ת����Ϣ
int transmit_msg(int x, Message *p_msg, bool isFile);
int transmit_file(int x, Message *p_msg);
int send_ChangeState(int x,const bool isOnline);
void print_to_log(const char *s);
/*------------------���Ժ�������-----------------------*/
void test(); //���Թ��ܺ���

// #endif