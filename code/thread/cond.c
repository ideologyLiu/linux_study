#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#define BUFFER_SIZE 10

int buffer[BUFFER_SIZE];
int count = 0;

sem_t mutex;
sem_t empty;
sem_t full;

void *producer(void *arg)
{
    int i;
    for (i = 0; i < 20; i++)
    {
        sem_wait(&empty);
        sem_wait(&mutex);
        buffer[count++] = i;
        printf("Produced %d\n", i);
        sem_post(&mutex);
        sem_post(&full);
        usleep(100000);
    }
    pthread_exit(NULL);
}

void *consumer(void *arg)
{
    int i;
    for (i = 0; i < 20; i++)
    {
        sem_wait(&full);
        sem_wait(&mutex);
        int val = buffer[--count];
        printf("Consumed %d\n", val);
        sem_post(&mutex);
        sem_post(&empty);
        usleep(200000);
    }
    pthread_exit(NULL);
}

int main()
{
    pthread_t prod_thread, cons_thread;

    sem_init(&mutex, 0, 1);
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);

    pthread_create(&prod_thread, NULL, producer, NULL);
    pthread_create(&cons_thread, NULL, consumer, NULL);

    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);

    sem_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}