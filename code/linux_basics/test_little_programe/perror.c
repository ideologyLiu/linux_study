#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
int main()
{
    int ret = 0;
    ret = open("./a.c",O_RDONLY);
    if(ret<0)
    {
        perror("open error");
    }
    return 0;
}
