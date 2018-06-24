#include <sys/signal.h>
#include <stdio.h>
#include <stdlib.h>
void signal_handler(int sig)
{
    printf("Child reached signal handler: %d, signal: %d\n", getpid(), sig);
    exit(0);
}
void child_function(void)
{
    printf("Inside child function: %d\n", getpid());
    signal(SIGUSR1, signal_handler);
    pause();
}
int main(int argv, char** argc)
{
    int pid = fork();
    if(pid<0)
    {
        printf("Issue with fork\n");
        exit(1);
    }
    if(pid == 0)
    {
        printf("I am the child: %d\n", getpid());
        child_function();
        printf("We will never get here\n");
    }
    else
    {
        printf("I am the parent: %d\n", getpid());
        sleep(2);
        kill(pid, SIGUSR1);
        wait(NULL);
    }
    printf("Parent exiting: %d\n", getpid());
    return 0;
}

