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
    struct sockaddr_in addr_out;
    socklen_t addrlen = 0;
    int accept_fd = 0;
    char alpht[BUFSIZ] = {0};
    
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8000);
    addr.sin_addr.s_addr=htonl(INADDR_ANY);
    
    lfd = socket(AF_INET,SOCK_STREAM,0);
    if(lfd < 0)
    {
        sys_err("socket error");
        return lfd;
    }
    
    ret = bind(lfd,(struct sockaddr *)&addr,sizeof(&addr));
    if(ret < 0)
    {
        sys_err("bind error");
        return ret;
    }


    ret = listen(lfd,20);
    if(ret < 0)
    {
        sys_err("listen error");
        return ret;
    }

    memset(&addr_out,0,sizeof(addr_out));
    addrlen = sizeof(&addr_out);
    accept_fd = accept(lfd,(struct sockaddr *)&addr_out,&addrlen);
    if(accept_fd < 0)
    {
        sys_err("accept error");
        return accept_fd;
    }


    while(1)
    {
        ret = read(accept_fd,(void *)alpht,sizeof(alpht));
        write(STDOUT_FILENO,alpht,ret);
        for(int i=0;i<ret;i++)
        {
          alpht[i] = toupper(alpht[i]);
        }
       
        write(accept_fd,(const void *)alpht,ret);
    }

  
  
    close(accept_fd);
    close(lfd);
    
    return 0;
    
}
