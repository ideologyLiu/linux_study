#include<stdio.h>

struct student
{
    int roll;
    int age;
    char name[20];
    float marks;
};



int main()
{
    char buf[100];
    memset(buf, 0, sizeof(buf));
    struct student *p;
    struct student s1;
    s1.roll = 1;
    s1.age = 20;
    strcpy(s1.name, "Rajesh");
    s1.marks = 90.5;
    memcpy(buf, &s1, sizeof(s1));
    p = (struct student *)buf;
    printf("Roll: %d\n", p->roll);
    printf("marks: %f\n", p->marks);
}