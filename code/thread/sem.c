#include<pthread.h>
#include<stdio.h>
#include<unistd.h>
#include<semaphore.h>

// typedef struct {queue
// {
//    int num;
//    queue *next; 
// }Queue,*QUEUE;


int queue[10] = {0};
sem_t sem_producer;
sem_t sem_plate;
int j = 0;
void* producer(void* arg)
{
    int i = 0;
    while(1)
    {
        sem_wait(&sem_plate);//等盘子
        queue[i] = rand()%1000 + 1;
        printf("producer queue[%d]=%d \n",i,queue[i]);
        sem_post(&sem_producer);
        i = (i+1)%10;
        sleep(rand()%3);
    }
}

void* consumer(void* arg)
{
 
    while(1)
    {
        sem_wait(&sem_producer);//等产品
        printf("---%d consumer queue[%d]=%d \n",(int)arg,j,queue[j]);
        queue[j] = 0;
        sem_post(&sem_plate);
        j = (j+1)%10;
        sleep(rand()%10);
    }
}

int main()
{
    int i=0;
    pthread_t tid1,tid2;
    sem_init(&sem_producer,0,0);//0个产品
    sem_init(&sem_plate,0,10);//10个盘子
    pthread_create(&tid1,NULL,producer,NULL);
    for(i=0;i<3;i++)
    {
        pthread_create(&tid2,NULL,consumer,(void*)i);
    }

    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);

    while(1)
    {
        sleep(10);
    }

}

