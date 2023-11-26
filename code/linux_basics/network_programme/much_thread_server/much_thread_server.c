#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<ctype.h>
#include<string.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<pthread.h>

#define SER_POER 8888


struct s_info 
{
    struct sockaddr_in cli_addr;  
    int connfd;
};

void *do_work(void * arg)
{
    int n,i;
    struct s_info *ts = (struct s_info*)arg;
    char str[INET_ADDRSTRLEN];//#define INET_ADDRSTRLEN 16 可以使用"[+d"查看
    char buf[BUFSIZ]={0};
    
    while(1)
    {
        n = read(ts->connfd,buf,sizeof(buf));
        if(n==0)
        {
            printf("the client %d colse \n",ts->connfd);
            break;
        }
        for(i=0;i<n;i++)
        {
            buf[i] = toupper(buf[i]);
        }
        write(ts->connfd,buf,n);
    }
    close(ts->connfd);
    return (void *)0;

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
    struct s_info ts[256];//最大线程数创建出的结构体
    int i = 0;
    int tid = 0;
    char str[BUFSIZ] = {0};
	int opt = 1;

    lfd = socket(AF_INET,SOCK_STREAM,0);
    memset(&server_addr,0,sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SER_POER);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    //inet_pton(AF_INTE,"192.168.121.129",(void *)&server_addr.sin_addr.s_addr)
    
	setsockopt(lfd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
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

        ts[i].connfd = cfd;
        ts[i].cli_addr = client_addr;
 
        printf("client ip:%s prot:%d \n",inet_ntop(AF_INET,&(ts[i].cli_addr.sin_addr.s_addr),str,sizeof(str)),ntohs(ts[i].cli_addr.sin_port));
        pthread_create(&tid,NULL,do_work,(void *)&ts[i]);        
        pthread_detach(tid); //线程分离
        i++;
    }

    return 0;

}

