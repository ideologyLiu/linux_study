#include<stdio.h>
#include<pthread.h>
#include<string.h>

void sys_err(const char *str)
{
    perror(str);
    exit(0);
}

void* tnf(void *arg)
{
    pthread_t tid;
    int i = 10;
    sleep((int)arg);
    tid = pthread_self();
    printf("i`m i=%d pid =%d tid =%lu\n",(int)(arg)+1,getpid(),tid); 
    
    return (void *)i;
}

int main(int argc,char* argv[])
{
    pthread_t tid;
    int i = 0;
    int ret = 0;

  //  for(i=0;i<5;i++)
    {
        ret = pthread_create(&tid,NULL,tnf,(void *)i);//传参用值传递
        if(ret!=0)
        {
            sys_err("pthread_create error");
        }
    }

    pthread_detach(tid);

    sleep(1);
    ret = pthread_join(tid,(void **)&i);
    if(ret != 0)
    {
        printf("pthread join error %s\n",strerror(ret));
    }
    printf("main:pid =%d tid =%lu i=%d \n",getpid(),pthread_self(),i);
    sleep(1);
    return 0;
}