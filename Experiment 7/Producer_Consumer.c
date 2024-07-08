#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#define size 5

int S=1;
int E=size;
int F=0;
int in=0;
int out=0;
int count=0;
int buffer[size];
void wait(int *sem)
{
    while((*sem)<=0);
    (*sem)--;
}

void signal(int *sem)
{
    (*sem)++;
}

void *producer(void* arg)
{
    int flag=1;
    int item=0;
    while(flag==1)
    {
        wait(&E);
        wait(&S);
        sleep(1);
        buffer[in]=item;
        printf("PRODUCER : %d\n",item);
        in=(in+1)%size;
        count++;
        signal(&S);
        signal(&F);
        item=(item+1)%size;
    }
}

void *consumer(void *arg)
{
    int item,flag=1;
    while(flag == 1)
    {
        wait(&F);
        wait(&S);
        sleep(1);
        item=buffer[out];
        out=(out+1)%size;
        count--;
        printf("CONSUMER : %d\n",item);
        signal(&S);
        signal(&E);
    }
}

void main()
{
    pthread_t p,c;
    pthread_create(&p,NULL,producer,NULL);
    pthread_create(&c,NULL,consumer,NULL);
    pthread_join(p,NULL);
    pthread_join(c,NULL);
}
