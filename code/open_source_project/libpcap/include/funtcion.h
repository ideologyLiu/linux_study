#ifndef __FUCTION_H__
#define __FUCTION_H__
#include <stdbool.h>

#define OK 0
#define ERROR -1

#define SMALL_PACKET_CAPTURE_PCAP "pcap"

#define SMALL_PACKET_CAPTURE_S "-s"
#define SMALL_PACKET_CAPTURE_P "-p"
#define SMALL_PACKET_CAPTURE_N "-n"
#define SMALL_PACKET_CAPTURE_C "-c"
#define SMALL_PACKET_CAPTURE_E "-e"
#define SMALL_PACKET_CAPTURE_M "-m"
#define SMALL_PACKET_CAPTURE_H "-h"
#define SMALL_PACKET_CAPTURE_R "-r"
#define SMALL_PACKET_CAPTURE_Q "-q"

#define MIN_PARAM_NUM 3
#define MAX_PARAM_NUM 4
#define CMD_STRLEN 8


typedef enum    
{
    SIZE = 0,
    TIME = 1,
    NUM = 2
}CMD;

typedef struct _CAPTURE_PACKAGE 
{
    bool start_stop_state; //抓包启停                                           
    char pathname[256];//抓包存储地址 考虑到内存，这个路径名是否需要支持最大？
    char network_interface_name[20];//选定抓包的网卡
    CMD capter_package_cmd;//抓包命令如数据包数量、时间和大小
    long long cmd_val; //为数量、时间、大小的具体参数
    char filter_capture_type[128];//设定过滤抓包的类型
    bool filter_enable;//过滤使能
    bool promiscuous_mode; //是否启用混杂模式
}CAPTURE_PACKAGE;

extern CAPTURE_PACKAGE g_package_param;


//  //回调函数指针，第一个参数是pcap_loop的最后一个参数，第二个参数是收到的数据包的pcap_pkthdr结构，第三个参数是数据包数据；
// void processPacket(u_char *arg, const struct pcap_pkthdr *pkthdr, const u_char *packet);
 
//  //抓包任务
// void* capture_package_task();

// //停止抓包
// int capture_package_stop();

//循环读取输入信息，进行相应操作。
void *loop_in_input_information();

//帮助
void show_help();;
#endif