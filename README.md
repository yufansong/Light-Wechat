# Light-Wechat
This is a final project of the Course -- "Computer Network"    
本项目为原创，代码，功能实现，报文设计，通信流程均未参考其他资料  
这个项目实现了微信的一些简单功能，主要分为client，server，database三个部分，其中client端使用qt完成，可以在Windows下运行，具有GUI界面  ，server端和database可以在linux下运行，database部分使用MySQL，代码中使用TCP链接，主要运行linux和Windows下socket库编写  
主要实现的功能有：
1. 用户名的创建，登陆，修改，退出
2. 多地登陆时的强制退出
3. 单人聊天与多人群聊
4. 聊天历史纪录的保存和读取
5. 文件的发送
6. 日志文件的读写
7. 数据库的加密存储
## 报文种类
根据客户端与服务器端的交互，报文的种类有以下几种  
1. LOGIN：  
   登录请求,每一次客户端想要连接服务器时发送的第一个包。  
   C->S  
2. ACK,确认包：  
   双方均可发送，用来表示某一个过程的结束  
3. NAK,否认包：  
   仅用于通知客户端登录失败所发的包  
   S->C  
4. TOTAL_USER_NUM：  
   传递总人数  
   S->C  
5. NAME_MSG：  
   用户信息，包括用户的名称以及在线状态  
   S->C  
6. PASS_CHAT_MSG：  
   历史信息，用于传输用户历史发送的消息  
   S->C  
7. CHANGE_PASSWORD：  
   改密码通知，如果检测到是第一次登陆会通知客户端更改密码  
   S->C  
8. NOT_CHANGE_PASSWORD：  
   给客户端的不改密码通知  
   S->C  
9.  MESSAGE：  
    实时消息传输，客户端发送报文，服务器端仅负责转发  
10. PASSWORD：  
    客户端需要更改密码时发送的包，包括新的密码  
    C->S  
11. FILE_NAME：  
    客户端需要给另一个用户传文件，这条消息需要包含文件名，服务器端仅负责转发  
    C->S  
12. FILE_MSG：  
    文件的具体内容，传文件内容,服务器端仅负责转发  
    C->S，S->C  
13. CLIENT_EXIT：  
    客户端登出前会通知服务器自己将要登出  
    C->S  
14. FORCE_EXIT：
    当有新的用户登录的时候服务器端要求客户端强制登出  
    S->C  
15. USER_STATE_CHANGE：  
    当有其他用户登入或下线，服务器通知其他用户  
    S->C  
16. MSG_NUM：  
    消息条数（配置信息，用户设置可读消息数）  
    S->C  
17. REPLACE：  
    在用户登录时给客户端的包，会提示其顶掉了别人  
18. NOT_REPLACE：  
    在用户登录时给客户端的包，会提示其没有顶掉别人  
## 报文分割
报文结构发送的18种报文中有许多类似的地方，比如要有报文头部对其类别进行识别，还有具体的字符串作为消息的内容等。为了统一管理将报文长度定为1024字节，总共分为四个部分：
1. 4字节的type，这是枚举类型，用于指示报文类型（网络序）
2. 20字节的字符数组s1
3. 20字节的字符数组s2
4. 4字节的int型变量number（网络序）
5. 976字节的字符数组s3具体格式如下：types1s2numbers303 423 2443 4447    481023
## 物理意义解释
报文具体规定所有报文格式相同，下面仅对报文中各部分的物理意义进行解释，其值也是主机序。
1. 登录请求
   * type=LOGIN (0)
   * s1：用户名
   * s2：密码功能：用户登录时发送给服务器的包，服务器返回ACK或NAK
   * 备注：这是TCP连接后发送的第一个报文。在客户端接收到确认或否定之前不处理服务器发送的消息。如果登录被拒绝，会返回用户操作界面，等待用户再次选择后再次尝试连接。type为网络序，（number暂时没有用到，也是网络序），后同s1和s2均是带尾零的字符串，长度限制在19字节，后同
2. 确认包
   * type=ACK (1)
   * s1：发送方用户名
   * s2：接收方用户名功能：服务器确认用户登录，发送给客户端，此时的s1，s2无实际意义。服务器通知客户端某次聊天记录发送完毕。此时的s1，s2无实际意义。客户端发送文件内容完成时的确认包。s1为发送方，s2为接收方。用于通知接收方文件内容都已经传输完毕无须再等待该类型报文。
   * 备注：因为有许多种通信过程需要这样一个表示“结束”或者“确认”的报文，因此将他们设置成同一个。
3. 否认包
   * type=NAK (2)
   * 功能：服务器发现用户名密码不匹配，拒绝用户登录
4. 总人数包
   * type=TOTAL_USER_NUM (3)
   * 功能：服务器告诉客户端当前群组中用户人数备注：在用户登录成功后传输给客户端，目的是告知客户端总人数，以及为后面发用户状况以及聊天记录等做准备。
5. 传好友信息
   * type=NAME_MSG (4)
   * s1是传输的对象的用户名
   * number：1代表在线0代表离线功能：服务器告诉客户端某个用户的名称以及该用户的在线状态
6. 传历史消息
   * type=PASS_CHAT_MSG（5）
   * s1：发送方姓名
   * s2：接收方姓名
   * s3：消息内容（不超过970字节，后同）
   * 功能：服务器向客户端发送一条聊天记录，内容包含发送方，接收方，消息内容
   * 备注：若发送方和接收方为同一个人，说明是群聊消息。
7. 通知更改密码
   * type=CHANGE_PASSWORD（6）
   * 功能：通知客户端改密码
   * 备注：当用户第一次登陆的时候需要通知客户端改密码
8. 通知无需更改密码
   * type=NOT_CHANGE_PASSWORD（7）
   * 功能：若用户并非第一次登陆无需更改用户密码
9.  传消息包
    * type=MESSAGE（8）
    * s1：发送方姓名
    * s2：接收方姓名
    * s3：消息内容功能：客户端给另一个用户发消息，服务器仅负责转发
10. 传密码包
    * type=PASSWORD（9）
    * s2：更改后的密码功能：客户端发送给数据库的密码包，返回修改后的密码，服务器端将改后的密码更新到数据库中备注：所有的关于更改密码的报文都按照这个格式传输，不论是第一次还是过程中。
11. 传文件名以及传文件提示
    * type=FILE_NAME（10）
    * s1：发送方姓名
    * s2：接收方姓名
    * s3：发送的文件名功能：当客户端发出这个包时就是在通知服务器他将要传文件给另一个用户，同时传输的还有文件名，服务器直接将这个包发给另一个客户端。
12. 传文件内容
    * type=FILE_MSG（11）
    * s1：发送方姓名
    * s2：接收方姓名number：这一次文件内容包的长度
    * s3：发送的文件内容功能：客户端读取文件内容后依次将其构造成报文发送给另一客户端，因为文件中间可能出现尾零的状况，所以需要number提示实际传输的字节数目。
13. 客户端登出消息
    * type=CLIENT_EXIT（12）
    * 功能：客户端退出时会主动给服务器发一个包告诉自己将要推出，客户端将这个包转发给所有其他的在线用户，并且在数据库修改用户在线信息备注：客户端发完包后主动退出，不用等待任何服务器的消息
14. 强制登出提示
    * type=FORCE_EXIT（13）
    * 功能：当服务器端收到某一个已在线用户再次登录的消息时，会给之前在线的用户发送一个强制其下线的包
15. 其他用户状态改变包
    * type=USER_STATE_CHANGE
    * s1：用户名功能：当有新用户上线时，会给所有其他在线用户发送一个包，提示某个用户状态改变，这个包一定会在强制登出提示（也就是旧的客户端下线）之后再发送。
16. 总消息条数
    * type=MSG_NUM（14）
    * number：用户配置的可读消息条数
    * 功能：当新用户登录时会传给该用户这样一个包，这也就是用户的配置信息，是用户最大显示的消息条数。
17. 顶掉其他用户的通知
    * type=REPLACE（16）
    * 功能：当新用户登录时会对该用户提示已经把其他同名用户挤了下去。是在登录时发送给客户端的包。客户端给出对应的提示信息
18. 没有顶掉其他用户的通知
    * type=NOT_REPLACE（17）
    * 功能：当新用户登录时会对该用户提示已经没有把其他同名用户挤了下去。是在登录时发送给客户端的包。客户端对此不作处理。
