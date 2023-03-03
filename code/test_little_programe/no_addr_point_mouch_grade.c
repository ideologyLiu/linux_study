#include<stdio.h>

typedef struct
{
    void * test_point;
    int length;
}TEST_ONE;
TEST_ONE *test;

int main(int argv,char*argc[])
{
    char* p1 = NULL;
    char* p2 = NULL;
    char* p3 = NULL;
    test = (TEST_ONE*)malloc(sizeof(TEST_ONE));
    test->test_point = malloc(128);
    p1 = (char*)test->test_point;

    snprintf(p1,sizeof(TEST_ONE),"%s","test\n");
    p2 = p1;
    printf("p2=%p *p2=%s",p2,p2);
    p3 = p2;
    printf("p3=%p\n",p3);
   // while(1);
    return 0;
}
