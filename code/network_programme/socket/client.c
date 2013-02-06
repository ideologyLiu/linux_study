#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<pthread.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>	

void sys_err(const char *str)
{
    perror(str);
    exit(1);
}


int main(int argc,char* argv[])
{
    int lfd = 0;
    int ret = 0;
    struct sockaddr_in addr;
    char alpht[BUFSIZ] = {0};
    
    addr.sin_family = AF_INET;
    addr.sin_port = htons(9527);
    addr.sin_addr.s_addr=htonl(INADDR_ANY);

    lfd = socket(AF_INET,SOCK_STREAM,0);
    if(lfd < 0)
    {
        sys_err("socket error");
        return lfd;
    }

    ret = connect(lfd,(struct sockaddr *)&addr,sizeof(addr));
    if(ret < 0)
    {
        sys_err("connect error");
        return ret;
    }
   
    while(1)
    {
        printf("please input raw alpht: \n");
        gets(alpht);
        ret = write(lfd,(const void *)alpht,strlen(alpht));
        if(ret < 0)
        {
            sys_err("write err");
            return ret;
        }
        
        ret = read(lfd,(void *)alpht,sizeof(alpht));
        if(ret < 0)
        {
            sys_err("read err");
            return ret;
        }
     
        write(STDOUT_FILENO,alpht,ret);
        printf("\n");
     
    }
   
    close(lfd);
    
    return 0;
    
}
