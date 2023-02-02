#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<ctype.h>
#include<string.h>
#include<sys/wait.h>
#include<sys/types.h>

#define SER_POER 8888


void *wait_child(int signo)
{
    while(waitpid(0,NULL,WNOHANG) > 0);
    
    return;
}
void sys_err(const char *str)
{
    perror(str);
    exit(0);
}

int main()
{
    pid_t pid = 0;
    int lfd=0,cfd=0;
    struct sockaddr_in server_addr,client_addr;
    socklen_t client_len = 0;
    char buf[BUFSIZ] = {0};
    int ret = 0;
    int n = 0;
    char client_ip[BUFSIZ] = {0};
    int client_ip_len = 0;
    
    lfd = socket(AF_INET,SOCK_STREAM,0);
    memset(&server_addr,0,sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SER_POER);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    //inet_pton(AF_INTE,"192.168.121.129",(void *)&server_addr.sin_addr.s_addr)

    ret = bind(lfd,(struct sockaddr *)&server_addr,sizeof(server_addr));
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

    while(1)
    {
        memset(&client_addr,0,sizeof(client_addr));
        client_len = sizeof(client_addr);
        cfd = accept(lfd,(struct sockaddr *)&client_addr,&client_len); 
        if(cfd < 0)
        {
            sys_err("accept error");
            return cfd;
        }
        inet_ntop(AF_INET,&client_addr.sin_addr.s_addr,(char *)client_ip,sizeof(client_ip));
       
        printf("client IP: %s,port:%d \n",client_ip, ntohs(client_addr.sin_port));
       
        pid = fork();
        if(pid < 0)
        {
           sys_err("fork error");
           return pid;
        }
        else if(pid == 0)
        {
             close(lfd);
             break;
        }
        else
        {
            close(cfd);
            signal(SIGCHLD,wait_child);//ÊÍ·Å½©Ê¬½ø³Ì
        }
    }


    if(pid == 0)
    {  
        while(1)
        {
            n = read(cfd,buf,sizeof(buf));
            if(n == 0)//client close
            {   
                close(cfd);
                return 0;
            }
            else if(n < 0)
            {
                sys_err("read error");
                exit(1);
            }
            for(int i=0;i<n;i++)
            {
                buf[i] = toupper(buf[i]);
            }
            
            ret = write(cfd,buf,n);
            if(ret < 0)
            {
                sys_err("write error");
            }
            
            
        }
    }
    else
    {
        close(cfd);
    }











    
    

}
