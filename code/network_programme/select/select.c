#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<pthread.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>	

#define INET_ADDRSTRLEN 16
#define SEVER_PORT 6666
#define FD_SIZE 1024

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
    struct sockaddr_in clien_addr;
    socklen_t clien_addrlen = 0;
    int clientfd  = 0;
    char buf[BUFSIZ] = {0};
    int maxfd=0;
    char str[INET_ADDRSTRLEN]={0};
    int maxi = -1;
    int i = 0;
    int n = 0;
    int j = 0;
    int client[FD_SIZE] = {0};
    fd_set allset,rest;
    int nready = 0;
    
    addr.sin_family = AF_INET;
    addr.sin_port = htons(SEVER_PORT);
    addr.sin_addr.s_addr=htonl(INADDR_ANY);


   // printf("INADDR_ANY = %d \n",INADDR_ANY);
    lfd = socket(AF_INET,SOCK_STREAM,0);
    if(lfd < 0)
    {
        sys_err("socket error");
        return lfd;
    }
    maxfd = lfd;
    ret = bind(lfd,(struct sockaddr *)&addr,sizeof(addr));
    if(ret < 0)
    {
        sys_err("bind error");
        return ret;
    }


    ret = listen(lfd,128);
    if(ret < 0)
    {
        sys_err("listen error");
        return ret;
    }
    maxi = -1; 
    for(i=0;i<FD_SIZE;i++)
    {
        client[i] = -1;
    }

    FD_ZERO(&allset);
    FD_SET(lfd,&allset);    //构造select监控文件描述符

    while(1)
    {
        rest = allset;     
        nready = select(maxfd+1,&rest,NULL,NULL,NULL);
        if(nready < 0)
        {
            sys_err("select error");
        }

        if(FD_ISSET(lfd,&rest)) //说明有新的客户端链接请求
        {
            memset(&clien_addr,0,sizeof(clien_addr));
            clien_addrlen = sizeof(&clien_addr);
            clientfd = accept(lfd,(struct sockaddr *)&clien_addr,&clien_addrlen);//此时不会阻塞
            if(clientfd < 0)
            {
               sys_err("accept error");
               return clientfd;
            }
            for(i=0;i<FD_SIZE;i++)
            {
                if(client[i] < 0)
                {
                    client[i] = clientfd;//保存accept返回的文件描述符到client[]里
                    break;
                }
            }

            if(i == FD_SIZE)
            {
                sys_err("too many clients \n");
            }

            FD_SET(clientfd,&allset);
            if(clientfd > maxfd)
            {
                maxfd = clientfd;//select第一个参数需要
            }

            if(i > maxi)
            {
                maxi = i;//保证maxi存的总是client[]最后一个元素下标
            }
            if(--nready == 0)
            {
                continue;
            }
           
            
        }
        
        
        for(i=0;i<=maxi;i++)//检测那个clients有数据就绪
        {
            if((lfd = client[i])<0)
            {
                continue;
            }
            if(FD_ISSET(lfd,&rest))
            {
                if((n = read(lfd,buf,sizeof(buf)))== 0)
                {
                    close(lfd);
                    FD_CLR(lfd,&allset);//解除select对此文件描述符的监控
                    client[i]=i;
                }
                else if(n>0)
                {
                    for(j=0;j<n;j++)
                    {
                        buf[j] = toupper(buf[j]);
                    }
                    sleep(1);
                    write(lfd,buf,n);
                }
                if(--nready == 0)
                {
                    break;  //跳出for,但还在while中
                }
                    
            }
        }
    }
    
   

  
    close(clientfd);
    close(lfd);
    
    return 0;
    
}

