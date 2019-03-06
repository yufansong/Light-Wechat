# 指令编译器和选项
CC=g++
LIBS = $(shell mysql_config --libs)
CFLAGS = $(shell mysql_config --cflags)

server : server.o common.o message.o mysql.o
	$(CC) -o server server.o common.o message.o mysql.o $(LIBS)
server.o : server.cpp head.h
	$(CC) -c server.cpp $(CFLAGS)
common.o : common.cpp head.h
	$(CC) -c common.cpp $(CFLAGS)
message.o : message.cpp head.h
	$(CC) -c message.cpp $(CFLAGS)
mysql.o : mysql.cpp head.h
	$(CC) -c mysql.cpp $(CFLAGS) 
.PHONY:clean
clean:
	rm -rf server *.o

# # 指令编译器和选项
# CC=g++
# CFLAGS=-Wall -std=gnu99
 
# # 目标文件
# TARGET=server
# # 源文件
# SRCS=server.cpp common.cpp message.cpp mysql.cpp
 
# OBJS = $(SRCS:.c=.o)
 
# $(TARGET):$(OBJS)
# 	# @echo TARGET:$@
# 	# @echo OBJECTS:$^
# 	# $(CC) -o $@ $^
# 	# $(CC) -o $@ $(mysql_config --cflags) $^ $(mysql_config --libs)
 
# clean:
# 	rm -rf $(TARGET) $(OBJS)
 
# %.o:%.c
# 	$(CC) $(CFLAGS) -o $@ -c $<

