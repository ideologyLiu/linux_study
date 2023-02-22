#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<errno.h>
#include<pthread.h>
#include<signal.h>
#include<sys/wait.h>

void sys_err(const char *str)
{
    perror(str);
    exit(1);
}

void catch_child(int signo)
{
    pid_t wpid;

    while((wpid = wait(NULL))!=-1)
    {
        printf("i catch child where id =%d \n",wpid);
    }

    return;  
}

int main(int argc,char* argv[])
{
   pid_t pid;
   int i=0;

   for(i=0;i<10;i++)
   {
        if((pid = fork() == 0))
        {
            break;
        }
   }

   if(i == 10)
   {
        struct sigaction act;

        act.sa_handler = catch_child;
        sigemptyset(&(act.sa_mask));
        act.sa_flags = 0;

        sigaction(SIGCHLD,&act,NULL);

        printf("i'm parent where pid = %d\n",getpid());

       while(1);      
   }
   else
   {
        printf("i'm child where pid = %d\n",getpid());
   }
}