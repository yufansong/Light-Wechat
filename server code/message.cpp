#include "head.h"
using namespace std;

//��ӡ��ǰʱ���Լ��ַ���,�������ݲ�Ҫ��β��
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
//��typeת��Ϊ������
void Message::hton_t()
{
	int t = htonl(type);
	memcpy((void *)&type, (void *)&t, 4);
}

//��typeתΪ�����������أ�type���ı�
Type Message::ntoh_t()
{
	int t = ntohl(type);
	Type s;
	memcpy((void *)&s, (void *)&t, 4);
	return s;
}

//��ȡ��������
Type Message::getType()
{
	Type t=ntoh_t();
	return t;
}

//�����û�����������Ϣ���ñ�������,����λ����β��
//���費�������Χ���ڿ���֮��
bool Message::setUserNamePassword(char*userName, char*password)
{
	strcpy(s1, userName);
	strcpy(s2, password);
	type = LOGIN;
	hton_t();
	return true;
}

//��ȡ�û���S1������S2
bool Message::getUserNamePassword(char*userName, char*password)
{
	strcpy(userName, s1);
	strcpy(password, s2);
	return true;
}

//����ACK
bool Message::setAck(const char* sendUserName, const char* receiveUserName)
{
	type = ACK;
	hton_t();
	strcpy(s1, sendUserName);
	strcpy(s2, receiveUserName);
	return true;
}

//����ΪNAK
bool Message::setNak()
{
	type = NAK;
	hton_t();
	return true;
}

//����ΪNAK
bool Message::setClientExit()
{
	type = CLIENT_EXIT;
	hton_t();
	return true;
}

//�ߵ�����
bool Message::setReplace()
{
	type = REPLACE;
	hton_t();
	return true;
}

//û�ߵ�����
bool Message::setNotReplace()
{
	type = NOT_REPLACE;
	hton_t();
	return true;
}

//����������
bool Message::setTotalUserNum(int num)
{
	type = TOTAL_USER_NUM;
	hton_t();
	number = num;
	number = htonl(number);
	return true;
}

//��ȡ������
bool Message::getTotalUserNum(int &num)
{
	number = ntohl(number);
	num = number;
	return true;
}

//�û����ã��ɿ���Ϣ������
bool Message::setScanMessageNum(int num)
{
	number = num;
	number = htonl(number);
	type = MSG_NUM;
	hton_t();
	return true;
}

//������
bool Message::getScanMessageNum(int &num)
{
	number = ntohl(number);
	num = number;
	return true;
}

//�����û�״̬S->C
bool Message::setUserState(char*userName, bool isOnline)
{
	type = NAME_MSG;
	hton_t();
	strcpy(s1, userName);
	number = isOnline ? 1 : 0;
	number = htonl(number);
	return true;
}

//��ȡ�û�״̬
bool Message::getUserState(char*userName, bool&isOnline)
{
	strcpy(userName, s1);
	number = ntohl(number);
	isOnline = number == 1 ? true : false;
	return true;
}

//����һ����Ϣ��¼,S1���ͷ���S2���շ���number��Ϣ���ͣ�S3������Ϣ
//�������β��
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

//�ӱ��Ľ�������=��ȡ����Ϣ������
bool Message::getPassChatMsg(char*sendUserName, char*getUserName, bool&isFile, char*message)
{
	number = ntohl(number);
	isFile = number == 1 ? true : false;
	strcpy(sendUserName, s1);
	strcpy(getUserName, s2);
	strcpy(message, s3);
	return true;
}

//֪ͨ�ͻ��˸�����
bool Message::setChangePassword()
{
	type = CHANGE_PASSWORD;
	hton_t();
	return true;
}

//֪ͨ�ͻ��˲�������
bool Message::setNotChangePassword()
{
	type = NOT_CHANGE_PASSWORD;
	hton_t();
	return true;
}

//��������ʱ���İ�
bool Message::setPassword(char* password)
{
	type = PASSWORD;
	hton_t();
	strcpy(s2, password);
	return true;
}

//���ո��ĵ�����
bool Message::getPassword(char* password)
{
	strcpy(password, s2);
	return true;
}

//����ǰ��Ϣ
bool Message::setMsg(char*sendName, char*receiveName, char*message)
{
	type = MESSAGE;
	hton_t();
	strcpy(s1, sendName);
	strcpy(s2, receiveName);
	strcpy(s3, message);
	return true;
}

//������Ϣ������
bool Message::getMsg(char*sendName, char*receiveName, char*message)
{
	strcpy(sendName, s1);
	strcpy(receiveName, s2);
	strcpy(message, s3);
	return true;
}

//����ACK��Ϣ������
bool Message::getAck(char *sendName, char *receiveName)
{
	strcpy(sendName, s1);
	strcpy(receiveName, s2);
	return true;
}

//���ļ���Ϣ
bool Message::setFileName(char*sendName, char*receiveName, char*filename)
{
	type = FILE_NAME;
	hton_t();
	strcpy(s1, sendName);
	strcpy(s2, receiveName);
	strcpy(s3, filename);
	return true;
}

//��ȡ�ļ���Ϣ���õ��ļ���
bool Message::getFileName(char*sendName, char*receiveName, char*filename)
{
	strcpy(sendName, s1);
	strcpy(receiveName, s2);
	strcpy(filename, s3);
	return true;
}

//�����û�״̬�ı�
bool Message::setUserStateChange(char *userName, bool isOnline)
{
	type = USER_STATE_CHANGE;
	hton_t();
	number = isOnline ? 1 : 0;
	number = htonl(number);
	strcpy(s1, userName);
	return true;
}

//��ȡ�û��ı�״̬��
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

//ǿ���˳���
bool Message::setForceExit()
{
	type = FORCE_EXIT;
	hton_t();
	return true;
}