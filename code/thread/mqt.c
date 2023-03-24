#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include<mqueue.h>
#include<fcntl.h>

mqd_t mqd_temp;

typedef struct msg
{
    int age;
    int grade;
}Msg,*MSG;

void* test_send(void *arg)
{
    int ret = 0;
    Msg t1;
    t1.age = 100;
    t1.grade=16;
    while(1)
    {
        printf("mq_send sizeof(t1)=%d\n",sizeof(t1));
        ret = mq_send(mqd_temp,(char*)&t1,8,0);
        if(ret != 0)
        {
            perror("mqSend error");
        }
       
        sleep(1);
    }

}

void* test_recevie(void* arg)
{
    Msg t2;

    int ret = 0;
    while(1)
    {
        ret = mq_receive(mqd_temp,(char*)&t2,sizeof(t2),NULL);
        if(ret == sizeof(t2))
        {
            printf("receive age=%d grade=%d \n",t2.age,t2.grade);
        }
        else if(ret == -1)
        {
            perror("mq_receive");
        }
        printf("ret=%d\n",ret);
        sleep(2);
    }

}

int main()
{
    pthread_t tid1,tid2;
    struct mq_attr mqttr;
    mqttr.mq_maxmsg = 0;
    mqttr.mq_msgsize = 0;//sizeof(Msg);
    mqd_temp = mq_open("/mq_test",O_CREAT|O_RDWR,0664,&mqttr);
    if(mqd_temp == -1)
    {
        perror("mq_open error");
    }
    printf("1 mqd_temp =%d\n",mqd_temp );
    pthread_create(&tid1,NULL,test_send,NULL);
    pthread_create(&tid2,NULL,test_recevie,NULL);
    while(1)
    {
        sleep(10);
    }
    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);
}