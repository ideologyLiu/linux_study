include ./common/SOURCE

#COMMON_DIR = common/

SOURCES += $(wildcard *.c)
#SOURCES += $(wildcard $(COMMON_DIR)/*.c)

OBJS = $(patsubst %.c,%.o,$(filter %.c,$(SOURCES)))

#选定编译服务器
COMPLIE_TOOLS = gcc #arm-mol-linux-uclibcgnueabihf-gcc

#头文件，库文件目录
INCLUDES = -I ./include  -I /usr/local/include  
#编译警告显示，优化等级
DFLAG = -Wall -O3

#指定所需lib库的文件夹
CFLAG =  -L /usr/local/lib  
CFLAGS = $(INCLUDES) $(DFLAG) $(CFLAG)

#链接的编译库
LIBS = -lpthread

ALL:pcap

pcap:$(OBJS)
	$(COMPLIE_TOOLS) $(CFLAGS) $(OBJS) -o pcap $(LIBS)

%.o:%.c
	$(COMPLIE_TOOLS) $(CFLAGS) -c  $< -o $@ $(LIBS)

.PHONY:clean
clean:
	rm -rf $(OBJS) pcap