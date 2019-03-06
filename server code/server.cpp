#include "head.h"
using namespace std;
// int state[MAXNUM_CLIENT];
// int connet_fdbuf[MAXNUM_CLIENT];
// Client client[MAXNUM_CLIENT];
// MyDB mydb;
int main(int argc, char const *argv[])
{
	////////////////////////////////////////////////////////////////////////////////
	//mydb.insert_user(); //记得删！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
	////////////////////////////////////////////////////////////////////////////////

/*-------------------定义参数及初始化------------------------*/
    //char IP_to_bind[32] = "192.168.80.230"; //要绑定的本机的IP地址，缺省未0.0.0.0
    // IP_to_bind[0] = '\0';
    int IP_bind_enable = 0;      //选择绑定(1)/不绑定(0)本机ip地址，缺省为不绑定
    int PORT_to_bind = -1;     //要绑定的TCP端口号，缺省值-1
    int socket_fd;               //用于监听的文件描述符
    struct sockaddr_in servaddr; //server TCP协议族
    int block_enable = 0;        //non-block
    int fork_enable = 0;         //no-fork

    if(argc <1 )
    {
        printf("需要输入绑定的端口号\n");
        return -1;
    }

    PORT_to_bind = atoi(argv[1]);

    if (-1 == (socket_fd = socket(AF_INET, SOCK_STREAM, 0)))
    {
        printf("socket创建失败:%s(errno:%d)\n", strerror(errno), errno);
        return -2;
    }

    //置端口复用
    int opt = 1;
    if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)))
    {
        printf("置端口复用失败:errno=%d(%s)\n", errno, strerror(errno));
        close(socket_fd);
        return -3;
    }
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;//inet_addr(IP_to_bind);
    servaddr.sin_port = htons(PORT_to_bind);

    //设置阻塞非阻塞
    int flag;
    if (-1 == (flag = fcntl(socket_fd, F_GETFL, 0)))
    {
        printf("%s(errno:%d)\n", strerror(errno), errno);
        return -4;
    }
    if (-1 == fcntl(socket_fd, F_SETFL, flag | O_NONBLOCK))
    {
        printf("%s(errno:%d)\n", strerror(errno), errno);
        return -5;
    }

    //绑定socket_fd
    if (bind(socket_fd, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1)
    {
        printf("socket绑定失败%s(errno:%d)\n", strerror(errno), errno);
        return -6;
    }

    //开始监听是否有客户端连接
    if (-1 == listen(socket_fd, MAXNUM_CLIENT))
    {
        printf("socket监听失败:%s(errno:%d)\n", strerror(errno), errno);
        return -7;
    }
    printf("等待客户端连接....\n");

/*-------------------开始监听处理------------------------*/
    fd_set rfd, wfd, allfd;
    // int connet_fdbuf[MAXNUM_CLIENT];
    int maxfd = socket_fd;
    for (int i = 0; i < MAXNUM_CLIENT; i++)
    {
        client[i].connect_fd = -1;
        client[i].state = 0;
        for (int j = 0; j < MAXNUM_UserName; j++)
            client[i].username[j] = '\0';
    }
    while (1)
    {
        FD_ZERO(&allfd);
        FD_ZERO(&rfd);
        FD_SET(socket_fd, &allfd);
        for (int j = 0; j < MAXNUM_CLIENT; j++)
            if (client[j].connect_fd != -1)
                FD_SET(client[j].connect_fd, &allfd);
        rfd = allfd;
        wfd = allfd;
        printf("while循环中第一个select阻塞开始\n");
        int result = select(maxfd + 1, &rfd, NULL, NULL, NULL);
        printf("while循环中第一个select阻塞结束 result:%d\n",result);
        if (result > 0 )//&& FD_ISSET(socket_fd, &rfd))
        {
            int k;
            if (FD_ISSET(socket_fd, &rfd))
            {
                for (k = 0; k < MAXNUM_CLIENT; k++) //连接
                    if (client[k].connect_fd == -1)
                    {
                        tcp_connect(k, socket_fd, &rfd, maxfd);
                        break;
                    }
                if (k == MAXNUM_CLIENT)
                    printf("server已满，心的clinet连接请求被拒绝\n");
            }
            for (int x = 0; x < MAXNUM_CLIENT; x++)
            {
                printf("尝试匹配 x: %d,conect%d\n",x,client[x].state);
                if ((client[x].connect_fd != -1) && FD_ISSET(client[x].connect_fd, &rfd))
                {
                    
                    printf("进入到FD_ISSET循环\n");
                    Message msg;

                    int n = Read_from_Client(x,&msg,"read");//这里是测试函数，之后请删除
                    printf("read n:%d\n",n);
                    if(n==0)
                        tcp_disconnet(x,&allfd);
                    // int n = read(client[x].connect_fd, (char *)(&msg), MAXNUM_MSG);
                    bool flag = false;

                    if (client[x].state == 1) //第i个链接接受登陆账户密码
                    {
                        printf("clinet%d开始接受登陆账号密码\n", x);
                        if (n > 0)
                        {
                            printf("clinet%d读到n>0，准备进入login函数\n");
                            flag = login(&msg, x, &allfd);
                        }
                        if (n == 0 || flag == false)
                        {
                            //n == 0与connect_fd[x]连接已中断，关闭描述符，移除allfd，对应的mc置无效，状态置0与connect_fd[x]连接已中断，关闭描述符，移除allfd，对应的mc置无效，状态置0
                            //flag == false 登陆失败
                            printf("flag:%d,n:%d\n",flag,n);
                            tcp_disconnet(x, &allfd);
                            continue;
                        }
                    }
                    else //非登陆信息:转发信息,退出信息
                    {                        
                        Type type = msg.getType();
                        printf("收到非登陆包 type:%d\n",type);
                        if (type == CLIENT_EXIT)
                        {
                            printf("收到正常退出包\n");
                            tcp_disconnet(x, &allfd);
                            transmit_exit_normal(x, false);
                        }
                        else if (type == FILE_MSG)
                        {
                            printf("收到文件内容包\n");
                            transmit_file(x, &msg);
                        }
                        else if (type == FILE_NAME || type == MESSAGE || type == ACK)
                        {
                            printf("收到文件名or聊天信息orACK\n");
                            if (type != ACK)
                            {
                                bool isFile = type == FILE_NAME ? true : false;
                                transmit_msg(x, &msg, isFile);
                            }
                            else 
                            {
                                // printf("直接write\n");
                                // char *str = (char *)(&msg);
                                // int m = write(client[0].connect_fd, str, MAXNUM_MSG);
                                // printf("直接write结束 m:%d\n",m);
                                transmit_ACK(x,&msg);
                            }
                        }
                        else if (type == PASSWORD)
                        {
                            printf("收到非第一次改密码\n");
                            bool flag = change_password_not_first(x, &msg);
                            if(flag == true)
                                client[x].state = 3;
                            else 
                                client[x].state = 2;
                        }
                    }
                }
            }
        }
    }

    /*-------------------结束------------------------*/
    return 0;
}
