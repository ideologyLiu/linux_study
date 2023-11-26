#include<stdio.h>
#include<sys/mman.h>
#include<unistd.h>
#include<fcntl.h>

void sys_err(const char*str)
{
    perror(str);
    exit(1);
}


int main(int argc,char *argv[])
{
    char *p = NULL;
    int fd = 0;
    int ret = 0;
    int len = 0;
    pid_t pid;

    fd = open("testmmp",O_RDWR|O_CREAT|O_TRUNC,0664);
    {
        if(fd == -1)
        sys_err("open error ");
    }

    ret = ftruncate(fd,20);
    if(ret == -1)
    {
        sys_err("ftruncate error");
    }
    len = lseek(fd,0,SEEK_END);
    p = mmap(NULL,len,(PROT_READ|PROT_WRITE),MAP_SHARED,fd,0);
    if(p == MAP_FAILED)
    {
        sys_err("map error");
    }

    close(fd);

    pid = fork();
    if(pid > 0)
    {
        strcpy(p,"hello world");  
    }
    else if(pid == 0)
    {
        sleep(1);
        printf("testmmp = %s \n",p);    
        ret = munmap(p,len);
        if(ret == -1)
        {
           sys_err("munmap erro ");
        } 3
    }
    else
    {
        sys_err("fork error");
    }


   
    
    return 0;
}
