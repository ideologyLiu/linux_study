#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<pthread.h>
#include<errno.h>

void sys_error(const char *str)
{
    perror(str);
    exit(1);
}

void printf_set(sigset_t *set)
{
    int i=0;
    for(i=1;i<32;i++)
    {
        if(sigismember(set,i))
        {
            putchar('1');
        }
        else
        {
            putchar('0');
        }
    }
    printf("\n");
}

int main(int argv,char* argc[])
{
    sigset_t set,oldset,pedset;
    int k = 0;
    int ret = 0;

    sigemptyset(&set);
    sigaddset(&set,SIGINT);
    ret = sigprocmask(SIG_BLOCK,&set,&oldset);
    if(ret == -1)
    {
        sys_error("sigprocmask error");
    }

    for(k=0;k<30;k++)
    {
        ret = sigpending(&pedset);
        if(ret == -1)
        {
            sys_error("sigpending error");
        }

        printf_set(&pedset);
        sleep(1);
    }
    
    return 0;
}


