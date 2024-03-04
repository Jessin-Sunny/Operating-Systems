/*
Write a program where a parent process creates a child process and then
the child process loads another program to add two numbers into its memory
space. The parent process should wait for the child process to exit.
(Use:fork, execlp, wait, exit System calls).
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;
    pid=fork();         //creating a child process
    if(pid < 0)
    {
        printf("Process creation failed\n");
        return 1;
    }
    else if(pid == 0)           //child process
    {
        if(execlp("./add","add",NULL) == -1)
        {
            printf("Process loading failed\n");
        };
        exit(0);
    }
    else                        //parent process
    {
        wait(NULL);
        printf("Child Process has terminated\n");
    }
    return 0;
}
