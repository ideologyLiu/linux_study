#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int g_share[10] =  {0};   // 共享资源
int head = 0;           // 队列头
int tail = 0;           // 队列尾

void* producer(void* arg)
{
    int i = 0;
    while(1)
    {
        pthread_mutex_lock(&mutex);
        g_share[head]= 1;
        printf("producer head = %d\n",head);
        head = (head + 1) % 10;
 
        pthread_mutex_unlock(&mutex);
        pthread_cond_broadcast(&cond);
        sleep(rand()%3);
    }
}

void *consumer(void* arg)
{
    while(1)
    {
        pthread_mutex_lock(&mutex);
        pthread_cond_wait(&cond,&mutex);
        printf("consumer g_share[%d] = %d\n",tail,g_share[tail]);
        g_share[tail] = 0;
        tail = (tail+1) % 10;
        pthread_mutex_unlock(&mutex);

        sleep(1);
    }
}

int main()
{
    pthread_t producer_t,consumer_t;
    int ret = 0;
    int i = 0;

    ret = pthread_create(&producer_t,NULL,producer,NULL);
    if(ret != 0)
    {
        printf("create producer thread failed");
    }

    for(i=0;i<3;i++)  //创建三个消费者线程
    {
        ret = pthread_create(&consumer_t,NULL,consumer,NULL);
        if(ret != 0)
        {
            printf("create consumer thread failed");
        }
    }

    pthread_join(producer_t,NULL);
    pthread_join(consumer_t,NULL);
    return 0;
}