#include "head.h"
using namespace std;
// int state[MAXNUM_CLIENT];
// int connet_fdbuf[MAXNUM_CLIENT];
// Client client[MAXNUM_CLIENT];
// MyDB mydb;
int main(int argc, char const *argv[])
{
	////////////////////////////////////////////////////////////////////////////////
	//mydb.insert_user(); //�ǵ�ɾ��������������������������������������������������������������������
	////////////////////////////////////////////////////////////////////////////////

/*-------------------�����������ʼ��------------------------*/
    //char IP_to_bind[32] = "192.168.80.230"; //Ҫ�󶨵ı�����IP��ַ��ȱʡδ0.0.0.0
    // IP_to_bind[0] = '\0';
    int IP_bind_enable = 0;      //ѡ���(1)/����(0)����ip��ַ��ȱʡΪ����
    int PORT_to_bind = -1;     //Ҫ�󶨵�TCP�˿ںţ�ȱʡֵ-1
    int socket_fd;               //���ڼ������ļ�������
    struct sockaddr_in servaddr; //server TCPЭ����
    int block_enable = 0;        //non-block
    int fork_enable = 0;         //no-fork

    if(argc <1 )
    {
        printf("��Ҫ����󶨵Ķ˿ں�\n");
        return -1;
    }

    PORT_to_bind = atoi(argv[1]);

    if (-1 == (socket_fd = socket(AF_INET, SOCK_STREAM, 0)))
    {
        printf("socket����ʧ��:%s(errno:%d)\n", strerror(errno), errno);
        return -2;
    }

    //�ö˿ڸ���
    int opt = 1;
    if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)))
    {
        printf("�ö˿ڸ���ʧ��:errno=%d(%s)\n", errno, strerror(errno));
        close(socket_fd);
        return -3;
    }
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;//inet_addr(IP_to_bind);
    servaddr.sin_port = htons(PORT_to_bind);

    //��������������
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

    //��socket_fd
    if (bind(socket_fd, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1)
    {
        printf("socket��ʧ��%s(errno:%d)\n", strerror(errno), errno);
        return -6;
    }

    //��ʼ�����Ƿ��пͻ�������
    if (-1 == listen(socket_fd, MAXNUM_CLIENT))
    {
        printf("socket����ʧ��:%s(errno:%d)\n", strerror(errno), errno);
        return -7;
    }
    printf("�ȴ��ͻ�������....\n");

/*-------------------��ʼ��������------------------------*/
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
        printf("whileѭ���е�һ��select������ʼ\n");
        int result = select(maxfd + 1, &rfd, NULL, NULL, NULL);
        printf("whileѭ���е�һ��select�������� result:%d\n",result);
        if (result > 0 )//&& FD_ISSET(socket_fd, &rfd))
        {
            int k;
            if (FD_ISSET(socket_fd, &rfd))
            {
                for (k = 0; k < MAXNUM_CLIENT; k++) //����
                    if (client[k].connect_fd == -1)
                    {
                        tcp_connect(k, socket_fd, &rfd, maxfd);
                        break;
                    }
                if (k == MAXNUM_CLIENT)
                    printf("server�������ĵ�clinet�������󱻾ܾ�\n");
            }
            for (int x = 0; x < MAXNUM_CLIENT; x++)
            {
                printf("����ƥ�� x: %d,conect%d\n",x,client[x].state);
                if ((client[x].connect_fd != -1) && FD_ISSET(client[x].connect_fd, &rfd))
                {
                    
                    printf("���뵽FD_ISSETѭ��\n");
                    Message msg;

                    int n = Read_from_Client(x,&msg,"read");//�����ǲ��Ժ�����֮����ɾ��
                    printf("read n:%d\n",n);
                    if(n==0)
                        tcp_disconnet(x,&allfd);
                    // int n = read(client[x].connect_fd, (char *)(&msg), MAXNUM_MSG);
                    bool flag = false;

                    if (client[x].state == 1) //��i�����ӽ��ܵ�½�˻�����
                    {
                        printf("clinet%d��ʼ���ܵ�½�˺�����\n", x);
                        if (n > 0)
                        {
                            printf("clinet%d����n>0��׼������login����\n");
                            flag = login(&msg, x, &allfd);
                        }
                        if (n == 0 || flag == false)
                        {
                            //n == 0��connect_fd[x]�������жϣ��ر����������Ƴ�allfd����Ӧ��mc����Ч��״̬��0��connect_fd[x]�������жϣ��ر����������Ƴ�allfd����Ӧ��mc����Ч��״̬��0
                            //flag == false ��½ʧ��
                            printf("flag:%d,n:%d\n",flag,n);
                            tcp_disconnet(x, &allfd);
                            continue;
                        }
                    }
                    else //�ǵ�½��Ϣ:ת����Ϣ,�˳���Ϣ
                    {                        
                        Type type = msg.getType();
                        printf("�յ��ǵ�½�� type:%d\n",type);
                        if (type == CLIENT_EXIT)
                        {
                            printf("�յ������˳���\n");
                            tcp_disconnet(x, &allfd);
                            transmit_exit_normal(x, false);
                        }
                        else if (type == FILE_MSG)
                        {
                            printf("�յ��ļ����ݰ�\n");
                            transmit_file(x, &msg);
                        }
                        else if (type == FILE_NAME || type == MESSAGE || type == ACK)
                        {
                            printf("�յ��ļ���or������ϢorACK\n");
                            if (type != ACK)
                            {
                                bool isFile = type == FILE_NAME ? true : false;
                                transmit_msg(x, &msg, isFile);
                            }
                            else 
                            {
                                // printf("ֱ��write\n");
                                // char *str = (char *)(&msg);
                                // int m = write(client[0].connect_fd, str, MAXNUM_MSG);
                                // printf("ֱ��write���� m:%d\n",m);
                                transmit_ACK(x,&msg);
                            }
                        }
                        else if (type == PASSWORD)
                        {
                            printf("�յ��ǵ�һ�θ�����\n");
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

    /*-------------------����------------------------*/
    return 0;
}
