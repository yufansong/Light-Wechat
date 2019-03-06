#define _CRT_SECURE_NO_WARNINGS
#include"head.h"
using namespace std;

/*-------------------���ݿ⺯������-------------------*/
/*
user
(
	userName varchar(20) primary key,
	password varchar(50) not null,
	scanMessageNum integer,
	online tinyint(1),
	isFirstLogin tinyint(1)
)


information
(
	messageID integer primary key,
	sendName varchar(20),
	receiveName varchar(20),
	message varchar(970),
	isFile tinyint(1)
)


*/


void MyDB::print_result()
{
	string sqlstr = "select * from information where sendName='ZhangSan';";

	mysql_query(mysql, sqlstr.c_str());   //���ɹ�����ֵΪ0
	result = mysql_store_result(mysql);

	cout << "select return " << (int)mysql_num_rows(result) << " records" << endl;
	
	// ѭ����ȡ�������������ļ�¼
	//1�����ص���˳����selectָ������˳����ͬ����row[0]��ʼ
	//2���������ݿ�����ʲô���ͣ�C�ж��������ַ��������д�������б�Ҫ����Ҫ�Լ�����ת��
	//3�������Լ�����Ҫ��֯�����ʽ



	while ((row = mysql_fetch_row(result)) != NULL) 
	{
		cout << setiosflags(ios::left);             //��������
		cout << "messageID��" << setw(5) << row[0];     //���12λ�������
		cout << "sendName��" << setw(12) << row[1];     //    8
		cout << "receiveName��" << setw(12) << row[2];     //    4
		cout << "message��" << setw(20) << row[3];     //    4
		cout << "isFile��" << setw(4) << row[4];     //    4
		cout << endl;
	}



	//row = mysql_fetch_row(result);

	
	/*
	cout << setiosflags(ios::left);             //��������
	cout << "userName��" << setw(12) << row[0];     //���12λ�������
	cout << "password��" << setw(15) << row[1];     //    8
	cout << "scanMessageNum��" << setw(4) << row[2];     //    4
	cout << "online��" << setw(4) << row[3];     //    4
	cout << "isFirstLogin��" << setw(4) << row[4];     //    4
	cout << endl;
	*/
}

MyDB::MyDB()
{
	if ((mysql = mysql_init(NULL)) == NULL)
	{
		cout << "mysql_init failed" << endl;
		exit(-1);
	}

	/*
	string sqlstr1 = "create database db1651459;";

	cout <<"mysql:"<< mysql_query(mysql, sqlstr1.c_str()) << endl;
	if (mysql_query(mysql, sqlstr1.c_str()))
	{
		cout << "create database fail��������" << endl;
		exit(-1);
	}


	*/


	/* �������ݿ⣬ʧ�ܷ���NULL
	1��mysqldû����
	2��û��ָ�����Ƶ����ݿ���� */
	if (mysql_real_connect(mysql, "localhost", "u1651459", "u1651459", "db1651459", 0, NULL, 0) == NULL)
	{
		cout << "mysql_real_connect failed(" << mysql_error(mysql) << ")" << endl;
		exit(-1);
	}

	/* �����ַ���������������ַ����룬��ʹ/etc/my.cnf������Ҳ���� */
	mysql_set_character_set(mysql, "utf8");

	string sqlstr1 = "select max(messageID) from information;";
	mysql_query(mysql, sqlstr1.c_str());
	result = mysql_store_result(mysql);
	row = mysql_fetch_row(result);

	message_num = atoi(row[0]);



}

MyDB::~MyDB()
{

	// �ͷ�result
	mysql_free_result(result);

	// �ر���������
	mysql_close(mysql);

}

void MyDB::encode(const char *password, char *code)
{
	//int len = strlen(pstr);//��ȡ����
	//for (int i = 0; i < len; i++)
	//*(pkey + i) = *(pstr + i) ^ i;


	int a[7] = { 4, 9, 6, 2, 8, 7, 3 };

	for (int i = 0, j = 0; password[j]; j++, i = (i + 1) % 7)
	{

		code[j] = password[j] + a[i];

		if (code[j] > 122)
			code[j] -= 90;
	}

}

void MyDB::insert_user()
{
	string sqlstr;
	char temp[50] = { 0 };
	char password[50];
	stpcpy(password, "123");
	encode(password, temp);

	sqlstr = "INSERT INTO user VALUES('ZhangSan','";
	sqlstr += temp;
	sqlstr += "',100,0,1);";

	mysql_query(mysql, sqlstr.c_str());   //���ɹ�����ֵΪ0

	sqlstr = "INSERT INTO user VALUES('LiSi','";
	sqlstr += temp;
	sqlstr += "',100,0,1);";

	mysql_query(mysql, sqlstr.c_str());   //���ɹ�����ֵΪ0

	sqlstr = "INSERT INTO user VALUES('WangWu','";
	sqlstr += temp;
	sqlstr += "',100,0,1);";

	mysql_query(mysql, sqlstr.c_str());   //���ɹ�����ֵΪ0

										  //print_result();

}

bool MyDB::getUserNum(int &number)            //ȡ���û�������
{
	if (mysql_query(mysql, "select * from user;"))
		return false;

	if ((result = mysql_store_result(mysql)) == NULL)
		return false;

	number = (int)mysql_num_rows(result);


	return true;
}

int MyDB::getscanMessageNumber(char *name, int &scanMessageNumber)
{
	string sqlstr;
	sqlstr = "select scanMessageNum from user where userName='";
	sqlstr += name;
	sqlstr += "';";

	mysql_query(mysql, sqlstr.c_str()); //���ɹ�����ֵΪ0

	result = mysql_store_result(mysql);

	row = mysql_fetch_row(result);

	int i, temp = 0;
	for (i = 0;; i++)
	{
		if (row[0][i] == 0)
			break;
	}

	for (int c = 0; c < i; c++)
	{
		temp = temp * 10 + row[0][c] - '0';
	}
	scanMessageNumber = temp;

	return 1;
}

int MyDB::getUserName(char **namelist, bool *isOnline) //��ȡȫ���û����ơ��Ƿ����ߡ��������Ϣ����
{
	if (mysql_query(mysql, "select * from user;"))
		return false;

	if ((result = mysql_store_result(mysql)) == NULL)
		return false;
	int j = 0;
	while ((row = mysql_fetch_row(result)) != NULL)
	{
		for (int i = 0;; i++)
		{
			namelist[j][i] = row[0][i];
			if (row[0][i] == 0)
				break;
		}
		//strcpy(namelist[j], row[0]);

		//namelist[j] = row[0];

		//cout << row[0] << ":" << row[3] << endl;
		if (strcmp(row[3], "1") == 0)
			isOnline[j] = true;
		else
			isOnline[j] = false;

		int i, temp = 0;
		for (i = 0;; i++)
		{
			if (row[2][i] == 0)
				break;
		}

		for (int c = 0; c < i; c++)
		{
			temp = temp * 10 + row[2][c] - '0';
		}
		j++;
	}

	return j;

}

bool MyDB::getCanlogin(char *name, char *password, bool &canlogin, bool &isFirstLogin)   //��ȡĳ�û��Ƿ�ɵ�½�Լ��Ƿ��ǵ�һ�ε�½
{
	string sqlstr = "select * from user where userName='";
	sqlstr += name;
	sqlstr += "';";

	char temp[50] = { 0 };
	encode(password, temp);

	if (mysql_query(mysql, sqlstr.c_str()))
		return false;

	if ((result = mysql_store_result(mysql)) == NULL)
		return false;

	if ((row = mysql_fetch_row(result)) == NULL)
		return false;

	if (strcmp(row[1], temp) == 0)
	{
		canlogin = true;
		setUserState(name, true);
	}
	else
	{
		canlogin = false;
		return false;
	}

	if (strcmp(row[4], "1") == 0)
		isFirstLogin = true;
	else
		isFirstLogin = false;

	return true;

}

bool MyDB::setPassword(char *name, char *password)           //����ĳ�û�������
{
	string sqlstr;

	char temp[50] = { 0 };
	encode(password, temp);

	sqlstr = "UPDATE user set password='";
	sqlstr += temp;
	sqlstr += "' where userName='";
	sqlstr += name;
	sqlstr += "';";

	if (mysql_query(mysql, sqlstr.c_str()) == 0)   //���ɹ�����ֵΪ0
	{

		string sqlstr = "select * from user where userName='";
		sqlstr += name;
		sqlstr += "' and password='";
		sqlstr += temp;
		sqlstr += "';";

		mysql_query(mysql, sqlstr.c_str());

		result = mysql_store_result(mysql);

		row = mysql_fetch_row(result);
		//const char temp[] = "1";
		if (strcmp(row[4], "1") == 0)   //���û�Ϊ��һ�ε�½���޸�����ɹ�����ʾ���û����ٵ�½��һ��
		{
			string sqlstr = "UPDATE user set isFirstLogin=0 where userName='";
			sqlstr += name;
			sqlstr += "';";

			mysql_query(mysql, sqlstr.c_str());
		}
	}

	return true;

}

int MyDB::getMessage(char *name1, char *name2, char **MessageList, bool *flag, bool *isFile) //��ȡ������֮�䷢��������Ϣ
{
	int i, num_use;
	getscanMessageNumber(name1, num_use);
	//printf("��ȡ�ɹ�scannum:%d\n", num_use);
	string sqlstr;
	if (strcmp(name1, name2))
	{
		sqlstr = "select * from information where (sendName='";
		sqlstr += name1;
		sqlstr += "' and receiveName='";
		sqlstr += name2;
		sqlstr += "') or (sendName='";
		sqlstr += name2;
		sqlstr += "' and receiveName='";
		sqlstr += name1;
		sqlstr += "') order by messageID desc;";
	}
	else
	{
		sqlstr = "select * from information where (sendName=receiveName) order by messageID desc;";
	}

	mysql_query(mysql, sqlstr.c_str()); //���ɹ�����ֵΪ0

	result = mysql_store_result(mysql);

	int number = (int)mysql_num_rows(result);
	if (number == 0)
		return number;

	int temp = number < num_use ? number : num_use;

	for (i = 0; i < num_use && ((row = mysql_fetch_row(result)) != NULL); i++)
	{
		for (int j = 0;; j++)
		{
			MessageList[temp - i - 1][j] = row[3][j];
			if (row[3][j] == 0)
				break;
		}

		if (strcmp(row[1], name1) == 0)
		{
			flag[temp - i - 1] = 1;
		}
		else
			flag[temp - i - 1] = 0;

		if (strcmp(row[4], "1") == 0)
		{
			isFile[temp - i - 1] = 1;
		}
		else
			isFile[temp - i - 1] = 0;

		//strcpy(MessageList[i], row[0]);
	}

	return i;
}

bool MyDB::setUserState(char *name, bool login)         //�����û��ĵ�½״̬
{
	string sqlstr;

	sqlstr = "select * from user where userName=";
	sqlstr += "'";
	sqlstr += name;
	sqlstr += "';";

	mysql_query(mysql, sqlstr.c_str());   //���ɹ�����ֵΪ0

	result = mysql_store_result(mysql);

	if ((int)mysql_num_rows(result) == 1)  //�û�����������ȷ
	{
		if (login == true)
		{
			sqlstr = "UPDATE user set online=1 where userName='";
			sqlstr += name;
			sqlstr += "';";
			mysql_query(mysql, sqlstr.c_str());   //���ɹ�����ֵΪ0
		}
		else
		{
			sqlstr = "UPDATE user set online=0 where userName='";
			sqlstr += name;
			sqlstr += "';";
			mysql_query(mysql, sqlstr.c_str());   //���ɹ�����ֵΪ0

		}
	}

	return true;

}

bool MyDB::addMessage(char *SendName, char *ReceiveName, char *message, bool type) //��������¼��Ϣ
{

	string sqlstr;

	char message_number[11];
	message_num++;
	sprintf(message_number, "%d", message_num);
	sqlstr = "INSERT INTO information VALUES";
	sqlstr += "(";

	/*for (int i = 0; i < 4; i++)
	{
		if (message_number[i] != '0')
			sqlstr += &message_number[i];
	}*/
	sqlstr+=message_number;
	sqlstr += ",'";
	sqlstr += SendName;
	sqlstr += "','";
	sqlstr += ReceiveName;
	sqlstr += "','";
	sqlstr += message;
	sqlstr += "',";

	if (type == true)
		sqlstr += "1";
	else
		sqlstr += "0";

	sqlstr += ");";

	mysql_query(mysql, sqlstr.c_str()); //���ɹ�����ֵΪ0

	return true;
}

bool MyDB::setFirstLogin(char *username, bool login)              //�����û����״ε�½״̬
{
	return true;
}

/*
int main()
{
	MyDB db;
	int a;
	int number;
	bool isonline, isfisrtlogin;
	bool isonlinelist[10];
	bool canlogin, firstlogin;
	char namelist[3][20];

	string namelist_str[100];
	string *namelist1 = namelist_str;
	//char namelist1[10][20];
	char **namelist_p;
	//namelist_p = &(namelist[0][0]);
	int scanmessagelist[10];
	int i;

	char name1[] = "ZhangSan";
	char name2[] = "LiSi";
	char password[] = "zhangsan123";
	char password_new[] = "zhangsan12345";
	string messagelist[100];

	//db.print_result();

	//cout << message[0] << endl;
	//db.print_result();

	/*
	cout << "����getusernum���û���������" << endl;
	db.getUserNum(number);
	cout << "user number:" << number << endl;

	cin >> a;

	cout << "����usernname���û���Ϣ����" << endl;
	char name11[20], name22[20], name33[20];
	char *name_l[100] = { name11 ,name22 ,name33 };
	int usernumber = db.getUserName(name_l, isonlinelist, scanmessagelist);
	for (i = 0; i < usernumber; i++)
	{
		cout << "name:" << name_l[i] << "    online:" << isonlinelist[i] << "     scanmessage:" << scanmessagelist[i] << endl;
	}
}

	cin >> a;

	cout << "����getCanlogin���Ƿ��ܵ�½�������Ƿ�Ϊ��һ�ε�½����" << endl;
	db.getCanlogin(name1, password_new, canlogin, firstlogin);
	if (canlogin == true)
		cout << name1 << "�ܵ�½";
	else
		cout << name1 << "���ܵ�½";
	if(firstlogin==true)
		cout <<  "��һ�ε�½";
	else
		cout <<  "���ǵ�һ�ε�½";
	cout << endl;

	cin >> a;

	cout << "����setPassword�������룩��" << endl;
	db.print_result();
	db.setPassword(name1, password_new);
	db.print_result();

	cin>>a;

	cout << "����sendmessage�������¼����" << endl;
	int count = db.getMessage(name1, name2, messagelist);
	for (int c = 0; c < count; c++)
		cout << messagelist[c] << endl;
	
	cin >> a;

	cout << "����setUserState��" << endl;
	db.print_result();
	bool login = false;
	db.setUserState(name1, password, login);
	db.print_result();

	cin >> a;

	cout << "���addMessage��" << endl;
	db.print_result();
	db.addMessage(name1, name2, "thank you", 0);
	db.print_result();


	return 0;

}
*/