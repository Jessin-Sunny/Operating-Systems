#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

struct shared_area
{
    int user1_up;
    int user2_up;
    int rw;
    char msg[100];
};

struct shared_area* shmptr;

int main()
{
    int shmid;
    int key=520;
    shmid=shmget(key,sizeof(struct shared_area),IPC_CREAT | 0666);
    shmptr=(struct shared_area*)shmat(shmid,NULL,0);
    shmptr->rw=0;
    while(1)
    {
        while(shmptr->user2_up == 1)
        {
            printf("Recieved from user1 : ");
            if((shmptr->msg,"stop") ==0)
            {
                exit(1);
            }
            else
            {
                puts(shmptr->msg);
            }
            shmptr->user1_up=1;
            shmptr->user2_up=0;
        }
        printf("User 2 : ");
        if(strcmp(shmptr->msg,"stop") == 0)
        {
            exit(1);
        }
        else
        {
            fgets(shmptr->msg,sizeof(shmptr->msg),stdin);
        }
        shmptr->rw=1;
        while(shmptr->rw ==1);
    }
    return 0;
}
