#include<stdio.h>
#include<pthread.h>

int main(int argc,char* argv[])
{
    pthread_t tid;
    tid = pthread_self();
    printf("pid =%d tid =%lu\n",getpid(),tid);
    return 0;
}