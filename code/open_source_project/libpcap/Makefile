COMMON_DIR = common/

BIN_DIR = BIN
OBJ_DIR = OBJ

SOURCES = $(wildcard *.c)
SOURCES += $(wildcard $(COMMON_DIR)/*.c)

OBJS = $(patsubst %.c,%.o,$(filter %.c,$(SOURCES)))

COMPLIE_TOOLS = arm-mol-linux-uclibcgnueabihf-gcc
#arm-ca9-linux-gnueabihf-gcc #


#头文件，编译优化 库文件目录
INCLUDES = -I ./include  -I /usr/local/include  #-I /usr/local/b1pro_compile/molchipv500-armgcc-uclibc/include
#-I /home/liuzheng16/capture_package/libpcap-1.10.4

DFLAG = -Wall -O3
CFLAG =  -L /usr/local/lib  #-L /usr/local/b1pro_compile/molchipv500-armgcc-uclibc/lib

CFLAGS = $(INCLUDES) $(DFLAG) $(CFLAG)

#链接的编译库
LIBS = -lpcap -lpthread

ALL:pcap

pcap:$(OBJ_DIR) dir mv
$(COMPLIE_TOOLS) $(CFLAGS) $(OBJ_DIR) -o $(BIN_DIR)/$@ $(LIBS)

%.o:%.c
$(COMPLIE_TOOLS) $(CFLAGS) -c  $< -o $@ $(LIBS)

dir:
	mkdir $(BIN_DIR)
	mkdir $(OBJ_DIR)
	
mv:
	mv $(OBJS) $(OBJ_DIR)
	
	
.PHONY:clean
clean:
rm -rf $(BIN_DIR) $(OBJ_DIR)