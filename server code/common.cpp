#include "head.h"
using namespace std;
Client client[MAXNUM_CLIENT];
MyDB mydb;
/*------------------测试函数定义-----------------------*/
void test()
{
    cout << "this is common.cpp\n";
    cout << client[0].state << endl;
    client[0].state = 1;
    cout << client[0].state << endl;
    return;
}
/*------------------交互函数定义-----------------------*/
int tcp_connect(int x, int socket_fd, fd_set *p_allfd, int &maxfd)
{
    if (-1 == (client[x].connect_fd = accept(socket_fd, (struct sockaddr *)NULL, NULL)))
    {
        printf("socket连接错误:%S(errno:%d)\n", strerror(errno), errno);

        char str_temp[MAXNUM_LOGMSG];
        sprintf(str_temp, "socket连接错误:%S(errno:%d)\n", strerror(errno), errno);
        print_to_log(str_temp);

        return -8;
    }
    int flag;
    if (-1 == (flag = fcntl(client[x].connect_fd, F_GETFL, 0)))
    {
        printf("%s(errno:%d)\n", strerror(errno), errno);

        char str_temp[MAXNUM_LOGMSG];
        sprintf(str_temp, "%s(errno:%d)\n", strerror(errno), errno);
        print_to_log(str_temp);

        return -4;
    }
    if (-1 == (fcntl(client[x].connect_fd, F_SETFL, flag | O_NONBLOCK)))
    {
        printf("%s(errno:%d)\n", strerror(errno), errno);

        char str_temp[MAXNUM_LOGMSG];
        sprintf(str_temp, "%s(errno:%d)\n", strerror(errno), errno);
        print_to_log(str_temp);

        return -5;
    }
    printf("client%d已连接\n", x);

    char str_temp[MAXNUM_LOGMSG];
    sprintf(str_temp, "client%d已连接\n", x);
    print_to_log(str_temp);

    FD_SET(client[x].connect_fd, p_allfd);
    maxfd = maxfd > client[x].connect_fd ? maxfd : client[x].connect_fd;
    client[x].state = 1;
    printf("connect_fd:%d,state:%d\n",client[x].connect_fd,client[x].state);

    return true;
}
int tcp_disconnet(int x, fd_set *p_allfd)
{
    close(client[x].connect_fd);
    FD_CLR(client[x].connect_fd, p_allfd);
    client[x].connect_fd = -1;
    client[x].state = -1;
    printf("client%d已中断连接\n", x);

    char str_temp[MAXNUM_LOGMSG];
    sprintf(str_temp, "client%d已中断连接\n", x);
    print_to_log(str_temp);

    return true;
}
int Send_to_Client(int x, Message *p_msg, const char *TypeStr) //修改读写
{
    fd_set wfd;
    FD_ZERO(&wfd);
    FD_SET(client[x].connect_fd, &wfd);
    
    int write_enable = 1;
    if(client[x].state >0)
    {
        printf("函数中select client[%d].state:%d阻塞开始\n",x,client[x].state);
        write_enable = select(client[x].connect_fd + 1, NULL, &wfd, NULL, NULL);
        printf("函数中select阻塞结束 write_enable:%d\n", write_enable);
    }
    else 
    {
        printf("未发送client%d\n",x);
    }
    

    char *str = (char *)(p_msg);
    int m=0;
    if (write_enable && FD_ISSET(client[x].connect_fd, &wfd))
    {
        m = write(client[x].connect_fd, str, MAXNUM_MSG);
        printf("client%d connet_fd:%d\n", x, client[x].connect_fd);
    }
    if (m > 0)
    {
        printf("已向client%d发送%s\n", x, TypeStr);

        char str_temp[MAXNUM_LOGMSG];
        sprintf(str_temp, "已向client%d发送%s\n", x, TypeStr);
        print_to_log(str_temp);

        return true;
    }
    else
    {
        printf("向client%d发送%s失败\n", x, TypeStr);

        char str_temp[MAXNUM_LOGMSG];
        sprintf(str_temp, "向client%d发送%s失败\n", x, TypeStr);
        print_to_log(str_temp);

        return false;
    }
}
int Read_from_Client(int x, Message *p_msg, const char *TypeStr) //修改读写
{
    fd_set rfd;
    FD_ZERO(&rfd);
    FD_SET(client[x].connect_fd, &rfd);
    printf("函数中select阻塞开始\n");
    int read_enable = select(client[x].connect_fd + 1, &rfd, NULL, NULL, NULL);
    printf("函数中select阻塞结束 read_enable:%d\n",read_enable);
    int n;
    if (read_enable > 0 && FD_ISSET(client[x].connect_fd, &rfd))
    {
        n = read(client[x].connect_fd, (char*)(p_msg), MAXNUM_MSG);
        if (n > 0)
            printf("read读取client %d %s成功 n:%d\n", x, TypeStr,n);
        else if (n == 0)
            return false; //表示连接已中断，通过返回值通知外面调用的地方
        else
        {
            printf("read读取client %d %s失败\n", x, TypeStr);
            printf("errno=%d(%s)\n", errno, strerror(errno));

            char str_temp[MAXNUM_LOGMSG];
            sprintf(str_temp, "read读取client %d %s失败\n", x, TypeStr);
            print_to_log(str_temp);

            return false;
        }
    }
    else
    {
        printf("select返回值为-1，read读取client %d %s失败\n", x, TypeStr);

        char str_temp[MAXNUM_LOGMSG];
        sprintf(str_temp, "select返回值为-1，read读取client %d %s失败\n", x, TypeStr);
        print_to_log(str_temp);

        exit(0);
    }
    return n;
}
int send_ACK(int x)
{
    Message msg;
    msg.setAck("server", "client");
    Send_to_Client(x, &msg, "ACK");
}
int send_NAK(int x)
{
    Message msg;
    msg.setNak();
    Send_to_Client(x, &msg, "NAK");
}
int send_config_friend(int x)
{
    if (client[x].state != 2)
        return false;
    int UserNum = 0;
/*------------------配置文件-------------------*/
    // char namelist[MAXNUM_CLIENT][MAXNUM_UserName];
    // bool isOnline[MAXNUM_CLIENT];
    printf("开始clinet%d发送配置文件\n",x);
    char **namelist = (char **)malloc(sizeof(char *) * MAXNUM_CLIENT);
    for(int i=0;i<MAXNUM_CLIENT;i++)
    {
        namelist[i] = (char *)malloc((sizeof(char *)) * MAXNUM_UserName);
    }
    bool isOnline[MAXNUM_CLIENT];
    int scanMessageNumber;
    printf("daabase\n");    
    mydb.getscanMessageNumber(client[x].username,scanMessageNumber);
    Message msg_config;
    msg_config.setScanMessageNum(scanMessageNumber);
    printf("scanMsgNum %d\n", scanMessageNumber);
    Send_to_Client(x, &msg_config, "MSG_NUM");

/*------------------总用户人数-------------------*/
    mydb.getUserNum(UserNum);
    printf("开始clinet%d发送总人数%d\n", x,UserNum);
    Message msg_num;
    msg_num.setTotalUserNum(UserNum);
    Send_to_Client(x, &msg_num, "TotalUsernumber");

    char str_temp[MAXNUM_LOGMSG];
    sprintf(str_temp, "开始clinet%d发送总人数%d\n", x, UserNum);
    print_to_log(str_temp);

/*------------------历史聊天记录-------------------*/
    /*
    先发配置信息
    然后发总人数
    每次循环先发一个包
    第一个循环的包是群聊的包
    一个用户名和用户名是否在线
    再发k个包，每个包是一个聊天记录
    发完再发ack
    */
    mydb.getUserName(namelist, isOnline);
    for (int i = 0; i < UserNum; i++)
        printf("namelist[%d]:%s isOnline:%d\n",i,namelist[i],isOnline[i]);

    for (int i = 0; i < UserNum+1; i++)//因为条过了一个
    {
        printf("\n");
        mydb.getscanMessageNumber(client[x].username, scanMessageNumber);
        //发状态姓名
        Message msg_online;
        //发信息
        char *name1, *name2;
        bool *p_isFile;
        bool *p_flag;
        name1 =(char *)malloc(sizeof(char)*MAXNUM_UserName);
        name2 = (char *)malloc(sizeof(char) * MAXNUM_UserName);
        p_isFile = (bool*)malloc(sizeof(bool) * MAXNUM_ScanMessage);
        p_flag = (bool *)malloc(sizeof(bool) * MAXNUM_ScanMessage);
        // char messageList[MAXNUM_ScanMessage][MAXNUM_ChatMsg];
        char **messageList = (char **)malloc(sizeof(char *) * MAXNUM_ScanMessage);
        for (int j = 0; j < MAXNUM_ScanMessage; j++)
        {
            messageList[j] = (char *)malloc((sizeof(char)) * MAXNUM_ChatMsg);
        }

        strcpy(name1, client[x].username);
        if (i == 0)
        {
            strcpy(name2,client[x].username);
            msg_online.setUserStateChange(name2, isOnline[i]);
            printf("用户:%s 是否在线%d\n",name2,isOnline[i]);
        }
        else if(!strcmp(client[x].username,namelist[i - 1]))
            continue;
        else
        {
            strcpy(name2, namelist[i - 1]);
            msg_online.setUserStateChange(name2, isOnline[i-1]);
            printf("用户:%s 是否在线%d\n", name2, isOnline[i-1]);
        }
        printf("循环:%d name1:%s,name2:%s\n",i,name1,name2);
        Send_to_Client(x,&msg_online,"name and online state");//必须在continue后面
        int length = mydb.getMessage(name1, name2, messageList,p_flag, p_isFile);//这里需要增加信息，来获取到底有多少信息
        //sleep(1);
        printf("length:%d\n",length);
        for(int j=0;j<length;j++)
        {
            printf("message[%d]:%s\n",j,messageList[j]);
        }
        printf("scannum:%d\n", scanMessageNumber);
        scanMessageNumber = length < scanMessageNumber ? length : scanMessageNumber;
        printf("past msg begin:scannum:%d\n", scanMessageNumber);
        for (int j = 0; j < scanMessageNumber; j++)
        {
            cout << "name:" << name1 << "name2" << name2<<"\n";
            cout << "msg:" << messageList[j] << "\n";
        }
        printf("past msg end:scannum:%d\n", scanMessageNumber);
        for (int j = 0; j < scanMessageNumber; j++)
        {
            Message msg_chat;
            if(p_flag[j] == 1)
                msg_chat.setPassChatMsg(name1, name2, p_isFile[j], messageList[j]); //这里的isFile怎么得到	
            else
                msg_chat.setPassChatMsg(name2, name1, p_isFile[j], messageList[j]); //这里的isFile怎么得到
            Send_to_Client(x,&msg_chat,"History Chat Message");
            printf("发送完一条消息\n");
        }
        printf("begin free\n");
        // free(name1);
        // free(name2);
        // for (int j = 0; j < MAXNUM_ScanMessage; j++)
        //     free(messageList[i]);
        // free(messageList);
        //ack
        printf("free end\n");
        Message msg_ack;
        msg_ack.setAck("server","client");
        Send_to_Client(x, &msg_ack, "ACK");
        printf("\n");
    }
    for(int i=0;i<MAXNUM_CLIENT;i++)
        free(namelist[i]);
    free(namelist);

    // char str_temp[MAXNUM_LOGMSG];
    sprintf(str_temp, "向clinet%d发送完毕聊天历史记录\n", x);
    print_to_log(str_temp);

    return true;
}
int change_password_first(int x,const bool isFirstLogin)
{
    printf("进入到改密码函数 client[%d].state:%d\n",x,client[x].state);
    if (client[x].state < 3)
        return false;
    if (isFirstLogin == false)
    {
        Message msg_password;
        msg_password.setNotChangePassword();
        Send_to_Client(x,&msg_password,"not change password");
        return true;
    }
    else
    {
        Message msg_change_password;
        msg_change_password.setChangePassword();
        Send_to_Client(x, &msg_change_password, "change password");
        bool flag = false;
        Message msg_password;
        char password[MAXNUM_PassWord];
        //读取修改后的密码
        Read_from_Client(x, &msg_password, "Passwaord");
        msg_password.getPassword(password);
        //在数据库中修改密码
        flag = mydb.setPassword(client[x].username, password);
        return flag;
    }
    return true;
}
int change_password_not_first(int x,Message *p_msg)
{
    bool flag = false;
    char password[MAXNUM_PassWord];
    p_msg->getPassword(password);
    //在数据库中修改密码
    flag = mydb.setPassword(client[x].username, password);
    return flag;
}
int transmit_exit_normal(int x, const bool login)
{
    printf("进入到转发正常退出包\n");
    mydb.setUserState(client[x].username, login);
    Message msg_friend_state;
    bool isOnline = false;
    msg_friend_state.setUserStateChange(client[x].username, isOnline);
    printf("clinet[%d]登陆信息变为%d\n", x, login);
    Transmit_to_Client(x, client[x].username, client[x].username, &msg_friend_state);

    char str_temp[MAXNUM_LOGMSG];
    sprintf(str_temp, "clinet[%d]登陆信息变为%d\n", x, login);
    print_to_log(str_temp);

    // for (int j = 0; j < MAXNUM_CLIENT; j++)
    // {
    //     printf("client[%d].state:%d,x:%d\n",j,client[j].state,x);
    //     if (client[j].state >= 4 && j != x)
    //     {
    //         printf("匹配成功，开始发信息\n");
    //         Send_to_Client(j, &msg_friend_state, "friend state change");
    //     }
    // }
}
int multi_login(int x, fd_set *p_allfd)
{
    printf("向clinet%d开启多用户登陆检测\n");
    bool flag = false;
    for (int i = 0; i < MAXNUM_CLIENT; i++)
    {   
        printf("i:%d,name:%s state:%d\n",i,client[x].username,client[i].state);
        if (!strcmp(client[x].username, client[i].username) && x != i)
        {
            printf("x:%d %s,i:%d %s\n", x, client[x].username, i, client[i].username);
            transmit_exit_force(i);
            tcp_disconnet(i, p_allfd);
            // tcp_disconnet(i, p_allfd);
            flag = true;
            break;
        }
    }
    transmit_replace_someone(x, flag); //这里修改一下
    return true;
}
int transmit_exit_force(int x)
{
    Message msg_exit_force;
    // msg_exit_force.setClientExit(); //这里只是测试，之后请去除
    // int i=0;
    // for (i = 0; i < 1024; i += 4)
    //     cout << *(int *)(((char *)&msg_exit_force) + i) << "\n";

    msg_exit_force.setForceExit();
    // printf("强制退出开始:%d",*(int*)(&msg_exit_force));
    // Type type = msg_exit_force.getType();
    // printf("强制退出结束:%d", *(int *)(&msg_exit_force));
    // printf("强制退出构造包%d\n",type);
    Send_to_Client(x, &msg_exit_force, "force exit");
}
int transmit_replace_someone(int x, const bool flag)
{
    Message msg_replace;
    if (flag)
    {
        msg_replace.setReplace();
        Send_to_Client(x, &msg_replace, "replace someone");
        
        print_to_log("replace someone\n");
    }
    else
    {
        msg_replace.setNotReplace();
        Send_to_Client(x, &msg_replace, "not replace someone");

        print_to_log("not replace someone\n");
    }

}
int Transmit_to_Client(int x, char *sendUserName, char *getUserName, Message *p_msg) //转发信息
{
    if (strcmp(sendUserName, getUserName) == 0)
    {
        for (int i = 0; i < MAXNUM_CLIENT; i++)
            if (i != x)
            {
                char str[100];
                sprintf(str, "client %d chat or file content transmit to client %d", x, i);
                Send_to_Client(i, p_msg, str);
            }
    }
    else
    {
        for (int i = 0; i < MAXNUM_CLIENT; i++)
            if (strcmp(getUserName, client[i].username) == 0 && i != x)
            {
                char str[100];
                sprintf(str, "client %d chat or file content transmit to client %d", x, i);
                Send_to_Client(i, p_msg, str);
            }
    }
}
int transmit_ACK(int x,Message *p_msg)
{
    char sendUserName[MAXNUM_UserName], getUserName[MAXNUM_UserName];
    p_msg->getAck(sendUserName, getUserName);
    printf("send:%s get:%s\n", sendUserName, getUserName);
    Message msg_ack;
    msg_ack.setAck(sendUserName, getUserName);
    printf("转发ACK\n");
    Transmit_to_Client(x, sendUserName, getUserName, &msg_ack);
    // for (int i = 0; i < MAXNUM_CLIENT; i++)
    // {
    //     printf("x:%d 匹配转发ACK getname:%s,匹配client[%d].name:%s\n",x, getUserName, i,client[i].username); 
    //     if (strcmp(getUserName, client[i].username) == 0 && i != x)
    //     {
    //         // Send_to_Client(i, p_msg, "ACK");
    //         // char *str = (char *)(p_msg);
    //         // int m = write(client[x].connect_fd, str, MAXNUM_MSG);
    //     }
    // }
}
int transmit_msg(int x, Message *p_msg, bool isFile)
{
    char sendUserName[MAXNUM_UserName], getUserName[MAXNUM_UserName];
    char chat_msg[MAXNUM_ChatMsg];
    /*------------------在线聊天消息和文件名(入库再转发)-------------------*/
    p_msg->getMsg(sendUserName, getUserName, chat_msg);
    printf("send:%s get:%s\n", sendUserName, getUserName);
    // printf("---------------------------------\n");
    // printf("调用数据库，增加消息记录\n");
    // printf("---------------------------------\n");
    mydb.addMessage(sendUserName, getUserName, chat_msg, isFile);
    Transmit_to_Client(x, sendUserName, getUserName, p_msg);

    char str_temp[MAXNUM_LOGMSG];
    sprintf(str_temp, "send:%s get:%s msg:%s\n", sendUserName, getUserName,chat_msg);
    print_to_log(str_temp);
}
int transmit_file(int x, Message *p_msg)
{
    char sendUserName[MAXNUM_UserName], getUserName[MAXNUM_UserName];
    char chat_msg[MAXNUM_ChatMsg];
    int length = 10;
    /*------------------文件消息(直接转发)-------------------*/
    p_msg->getFileMsg(sendUserName, getUserName);
    printf("send:%s get:%s\n",sendUserName,getUserName);
    Transmit_to_Client(x, sendUserName, getUserName, p_msg);
} //文件这么多，我收到头一个包，然后再开始接受？

int send_ChangeState(int x,const bool isOnline)
{
    for(int i=0;i<MAXNUM_CLIENT;i++)
        if(client[i].connect_fd != -1 && x != i)
        {
            Message msg_state;
            printf("username:%s\n",client[x].username);
            msg_state.setUserStateChange(client[x].username,isOnline);
            Send_to_Client(i,&msg_state,"change state");
        }
}

int login(Message *p_msg, int x, fd_set *p_allset) //登陆这里的状态有必要么?
{
    printf("进入到login函数中\n");
    char username[MAXNUM_UserName];
    char password[MAXNUM_PassWord];
    bool canLogin, isFirstLogin;
    p_msg->getUserNamePassword(username, password);
    printf("username:%s,password:%s\n",username,password);
    mydb.getCanlogin(username, password, canLogin, isFirstLogin);
    printf("从数据库中读取登陆信息canLogin:%d\n",canLogin);

    if (canLogin == true)
    {
        printf("可以登陆，进入发送ACK函数\n");

        char str_temp[MAXNUM_LOGMSG];
        sprintf(str_temp, "可以登陆，进入发送ACK函数\n");
        print_to_log(str_temp);

        send_ACK(x);
        sprintf(client[x].username, "%s", username);
        printf("进入多用户登陆检测 state%d\n", client[x].state);
        multi_login(x, p_allset); //检测是否多用户登陆
        send_ChangeState(x,true);
        bool flag;
        client[x].state = 2; //进入2状态，开始发送信息
        printf("开始发送配置信息username:%s state:%d\n",client[x].username,client[x].state);
        flag = send_config_friend(x);
        client[x].state += flag; //如果正确，则进入3状态，开始修改密码
        printf("开始进入修改密码函数 state:%d\n", client[x].state);
        flag = change_password_first(x, isFirstLogin); //这里是测试，之后请恢复
        client[x].state += flag; //如果正确，则进入4状态，开始等待聊天
    }
    else
    {
        char str_temp[MAXNUM_LOGMSG];
        sprintf(str_temp, "client[%d]登陆失败\n",x);
        print_to_log(str_temp);

        send_NAK(x);
        return false;
    }
    return true;
}