#include "head.h"
using namespace std;

//打印当前时间以及字符串,传进内容不要加尾零
void print_to_log(const char *s)
{
	int fd = open(LOGFILE, O_RDWR | O_CREAT | O_APPEND);
	char *s_time;
	int length = strlen(s);
	s_time = (char *)malloc((length + 2) * sizeof(char));
	time_t t;
	time(&t);
	strncpy(s_time, s, length);
	s_time[length] = '\n';
	s_time[length + 1] = '\0';
	//printf("%s", s_time);
	write(fd, ctime(&t), 25);
	write(fd, s_time, length + 1);
	free(s_time);
	close(fd);
}
//将type转换为网络序
void Message::hton_t()
{
	int t = htonl(type);
	memcpy((void *)&type, (void *)&t, 4);
}

//将type转为主机序结果返回，type不改变
Type Message::ntoh_t()
{
	int t = ntohl(type);
	Type s;
	memcpy((void *)&s, (void *)&t, 4);
	return s;
}

//获取包的类型
Type Message::getType()
{
	Type t=ntoh_t();
	return t;
}

//根据用户名和密码信息设置报文内容,空余位置填尾零
//假设不会出错，范围均在控制之内
bool Message::setUserNamePassword(char*userName, char*password)
{
	strcpy(s1, userName);
	strcpy(s2, password);
	type = LOGIN;
	hton_t();
	return true;
}

//获取用户名S1和密码S2
bool Message::getUserNamePassword(char*userName, char*password)
{
	strcpy(userName, s1);
	strcpy(password, s2);
	return true;
}

//设置ACK
bool Message::setAck(const char* sendUserName, const char* receiveUserName)
{
	type = ACK;
	hton_t();
	strcpy(s1, sendUserName);
	strcpy(s2, receiveUserName);
	return true;
}

//设置为NAK
bool Message::setNak()
{
	type = NAK;
	hton_t();
	return true;
}

//设置为NAK
bool Message::setClientExit()
{
	type = CLIENT_EXIT;
	hton_t();
	return true;
}

//踢掉别人
bool Message::setReplace()
{
	type = REPLACE;
	hton_t();
	return true;
}

//没踢掉别人
bool Message::setNotReplace()
{
	type = NOT_REPLACE;
	hton_t();
	return true;
}

//设置总人数
bool Message::setTotalUserNum(int num)
{
	type = TOTAL_USER_NUM;
	hton_t();
	number = num;
	number = htonl(number);
	return true;
}

//获取总人数
bool Message::getTotalUserNum(int &num)
{
	number = ntohl(number);
	num = number;
	return true;
}

//用户配置（可看消息数量）
bool Message::setScanMessageNum(int num)
{
	number = num;
	number = htonl(number);
	type = MSG_NUM;
	hton_t();
	return true;
}

//读配置
bool Message::getScanMessageNum(int &num)
{
	number = ntohl(number);
	num = number;
	return true;
}

//设置用户状态S->C
bool Message::setUserState(char*userName, bool isOnline)
{
	type = NAME_MSG;
	hton_t();
	strcpy(s1, userName);
	number = isOnline ? 1 : 0;
	number = htonl(number);
	return true;
}

//获取用户状态
bool Message::getUserState(char*userName, bool&isOnline)
{
	strcpy(userName, s1);
	number = ntohl(number);
	isOnline = number == 1 ? true : false;
	return true;
}

//设置一条消息记录,S1发送方，S2接收方，number消息类型，S3具体消息
//假设均含尾零
bool Message::setPassChatMsg(char*sendUserName, char*getUserName, bool isFile, char*message)
{
	type = PASS_CHAT_MSG;
	hton_t();
	strcpy(s1, sendUserName);
	strcpy(s2, getUserName);
	strcpy(s3, message);
	number = isFile ? 1 : 0;
	number = htonl(number);
	return true;
}

//从报文解析后内=容取得消息各部分
bool Message::getPassChatMsg(char*sendUserName, char*getUserName, bool&isFile, char*message)
{
	number = ntohl(number);
	isFile = number == 1 ? true : false;
	strcpy(sendUserName, s1);
	strcpy(getUserName, s2);
	strcpy(message, s3);
	return true;
}

//通知客户端改密码
bool Message::setChangePassword()
{
	type = CHANGE_PASSWORD;
	hton_t();
	return true;
}

//通知客户端不改密码
bool Message::setNotChangePassword()
{
	type = NOT_CHANGE_PASSWORD;
	hton_t();
	return true;
}

//更改密码时发的包
bool Message::setPassword(char* password)
{
	type = PASSWORD;
	hton_t();
	strcpy(s2, password);
	return true;
}

//接收更改的密码
bool Message::getPassword(char* password)
{
	strcpy(password, s2);
	return true;
}

//发当前消息
bool Message::setMsg(char*sendName, char*receiveName, char*message)
{
	type = MESSAGE;
	hton_t();
	strcpy(s1, sendName);
	strcpy(s2, receiveName);
	strcpy(s3, message);
	return true;
}

//接收消息并解析
bool Message::getMsg(char*sendName, char*receiveName, char*message)
{
	strcpy(sendName, s1);
	strcpy(receiveName, s2);
	strcpy(message, s3);
	return true;
}

//接收ACK消息并解析
bool Message::getAck(char *sendName, char *receiveName)
{
	strcpy(sendName, s1);
	strcpy(receiveName, s2);
	return true;
}

//传文件消息
bool Message::setFileName(char*sendName, char*receiveName, char*filename)
{
	type = FILE_NAME;
	hton_t();
	strcpy(s1, sendName);
	strcpy(s2, receiveName);
	strcpy(s3, filename);
	return true;
}

//获取文件消息，得到文件名
bool Message::getFileName(char*sendName, char*receiveName, char*filename)
{
	strcpy(sendName, s1);
	strcpy(receiveName, s2);
	strcpy(filename, s3);
	return true;
}

//设置用户状态改变
bool Message::setUserStateChange(char *userName, bool isOnline)
{
	type = USER_STATE_CHANGE;
	hton_t();
	number = isOnline ? 1 : 0;
	number = htonl(number);
	strcpy(s1, userName);
	return true;
}

//获取用户改变状态包
bool Message::getUserStateChange(char*userName, bool &isOnline)
{
	strcpy(userName, s1);
	number = ntohl(number);
	isOnline = number == 1 ? true : false;
	return true;
}

bool Message::getFileMsg(char *sendName, char *receiveName)
{
	strcpy(sendName, s1);
	strcpy(receiveName, s2);
	return true;
}

//强制退出包
bool Message::setForceExit()
{
	type = FORCE_EXIT;
	hton_t();
	return true;
}