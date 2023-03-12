#include<stdio.h>
#include<pthread.h>

int g_temp;

void sys_err(const char *str)
{
    perror(str);
    exit(0);
}

void tnf(void *arg)
{
    pthread_t tid;
  //  sleep((int)arg);
    g_temp = 50;
    tid = pthread_self();
    while(1)
    {        
        printf("i`m i=%d pid =%d tid =%lu\n",(int)(arg)+1,getpid(),tid); 
        sleep(2);
    }
}

int main(int argc,char* argv[])
{
    pthread_t tid;
    int i = 0;
    int ret = 0;
    g_temp = 1;
//    for(i=0;i<5;i++)
    {
        ret = pthread_create(&tid,NULL,&tnf,(void *)i);//传参用值传递
        if(ret!=0)
        {
            sys_err("pthread_create error");
        }
    }
   
    printf("g_temp = %d ",g_temp);
    sleep(5);
    pthread_cancel(tid);
    while(1)
    {    
        printf("main:pid =%d tid =%lu \n",getpid(),pthread_self());
        sleep(2);
    }
    return 0;
}
