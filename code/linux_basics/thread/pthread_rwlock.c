#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<string.h>


pthread_rwlock_t rwlock;
char g_test_str[18] = {0};
void sys_err(const char *str)
{
    perror(str);
    exit(0);
}

void tnf(void *arg)
{
    pthread_t tid;
   
    while(1)
    {
        if((int)arg == 4)//第五个线程进行写加锁
        {
            pthread_rwlock_wrlock(&rwlock);
            memset(g_test_str,0,sizeof(g_test_str));
            snprintf(g_test_str,"%s","HELLO WORLD\n");
            pthread_rwlock_unlock(&rwlock);        
        }
        
        else if((int)arg == 3)//第4个线程进行写加锁
        {
            pthread_rwlock_wrlock(&rwlock);
            memset(g_test_str,0,sizeof(g_test_str));
            snprintf(g_test_str,"%s","hello world\n");
            pthread_rwlock_unlock(&rwlock);        
        }
        else
        {
            pthread_rwlock_rdlock(&rwlock);
            printf("%s",g_test_str);
            pthread_rwlock_unlock(&rwlock);
        }
       
        sleep(rand()%3);
    }
}

int main(int argc,char* argv[])
{
    pthread_t tid;
    int i = 0;
    int ret = 0;
   
    pthread_rwlock_init(&rwlock,NULL);
    snprintf(g_test_str,"%s","hello world\n");
    for(i=0;i<10;i++)
    {
        ret = pthread_create(&tid,NULL,&tnf,(void *)i);//传参用值传递
        if(ret!=0)
        {
            sys_err("pthread_create error");
        }
    }
    while(1)
    {
        sleep(1);
    }
    printf("main:pid =%d tid =%lu \n",getpid(),pthread_self());
    return 0;
}
