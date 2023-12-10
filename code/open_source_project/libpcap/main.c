#include<pcap.h>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include "include/function.h"
#define SMALL_PACKET_CAPTURE_START "start"
#define SMALL_PACKET_CAPTURE_STOP "stop"


void main(int argc,char **argv)
{
    pthread_t input_t,package_t;
    int ret = 0;
    if(OK != default_param())
    {
        printf("[%s %d] default_param error \n", __FILE__, __LINE__);
    }
    (void)show_help();

    ret = pthread_create(&input_t,NULL,loop_in_input_information,NULL);
    if(OK!=ret)
    {
        printf("[%s %d] pthread_create loop_in_input_information error\n", __FILE__, __LINE__);
    }

    ret = pthread_create(&package_t,NULL,capture_package_task,NULL); 
    if(OK!=ret)
    {
        printf("[%s %d] pthread_create capture_package_task error\n", __FILE__, __LINE__);
    }

    while(1)
    {
        sleep(1);
    }

}