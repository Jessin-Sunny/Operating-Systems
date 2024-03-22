#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

struct area
{
    int server_up;
    int client_up;
    int rw;
    char msg[100];
};

struct area* shmptr;

int main()
{
    int shmid;
    int key=670;
    shmid=shmget(key,sizeof(struct area),IPC_CREAT | 0666);
    shmptr=(struct area*)shmat(shmid,NULL,0);
    shmptr->rw=0;
    while(1)
    {
        while(shmptr->rw != 1);
        while(shmptr->client_up == 0)
        {
            printf("Recieved from user2 : ");
            if(shmptr->msg == "stop")
            {
                exit(1);
            }
            else
            {
                puts(shmptr->msg);
                shmptr->server_up=0;
                shmptr->client_up=1;
            }
            printf("User 1 : ");
            if(shmptr->msg == "stop")
            {
                exit(1);
            }
            else
            {
                fgets(shmptr->msg,100,stdin);
                shmptr->rw=0;
            }
        }
    }
    shmctl(shmid,IPC_RMID,NULL);
    return 0;
}
