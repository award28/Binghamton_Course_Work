#include <sys/signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

int *sharedMemory;
int numProcs;
int passVal;
int level = 0;

void signal_handler(int sig)
{
    printf("EXITING: Level %i process with pid=%i, child of ppid=%i.\n", level, getpid(), getppid());
    exit(0);
}
void child_function(void)
{
    signal(SIGUSR1, signal_handler);
    pause();
}

int main(int argc, char **argv, char *envp[]) {
    int i; 
    int checkVal;
    int fd = open("./array.txt", O_RDWR);
    int namedFd;
    int pipeNum[2];
    int val;
    pid_t pid;
    int child = 0;
    int mypid;
    char *namedPipe = "./myfifo";
    char buf[1024];

    if (fd == -1) {
        perror ("Open");
        return 1;
    }
    if(argc != 2) {
        printf("You must have a single argument that is an integer between 1 and 32, inclusive.\n");
        exit(0);
    }
    else if(atoi(argv[1]) > 32 || atoi(argv[1]) < 1) {
        printf("Your argument must be between 1 and 32, inclusive.\n");
        exit(0);
    }

    numProcs = atoi(argv[1]);
    passVal = numProcs;

    if ((sharedMemory = mmap (0, numProcs*sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0)) == &checkVal) {
        perror("mmap");
        return 0;
    }

    mkfifo(namedPipe, 0666);
    namedFd = open(namedPipe, O_RDONLY | O_NONBLOCK);

    if(numProcs > 1) {
        pipe(pipeNum);
        pid = fork();
    }

    if(!pid) {
        child++;
        passVal--;
        if(write(pipeNum[1], &passVal, sizeof(int)) <= 0) {
            perror("Write");
            exit(0);
        }
    }
    else {
        if(read(pipeNum[0], &val, sizeof(int)) <= 0)  {
            perror("read");
            exit(0);
        }
    }

    for(i = 2; i < numProcs && !pid; i++) {
        if(!pid) {
            pid = fork();
        }
        if(!pid) {
            child++;
            passVal--;
            if(write(pipeNum[1], &passVal, sizeof(int)) <= 0) {
                perror("Write");
                exit(0);
            }
        }
        else {
            if(read(pipeNum[0], &val, sizeof(int)) <= 0)  {
                perror("read");
                exit(0);
            }
        }
    }

    mypid = getpid();
    memcpy(sharedMemory + child, &mypid, sizeof(int));

    close(fd);

    if(passVal == 1) {
        namedFd = open(namedPipe, O_WRONLY);
        if(write(namedFd, "finished", sizeof("finished")) <= 0) {
            perror("Write 1");
            close(namedFd);
            exit(0);
        }
        else {
            close(namedFd);
            unlink(namedPipe);
        }
    }

    if(getpid() == sharedMemory[0]) {
        namedFd = open(namedPipe, O_RDONLY);
        if(read(namedFd, buf, 1024) <= 0) {
            perror("Named pipe read");
            close(namedFd);
            exit(0);
        }
        else {
            close(namedFd);
            unlink(namedPipe);

            if(!strcmp(buf, "finished")) {
                for(i = numProcs - 1; i >= 0; i--)
                    printf("ALIVE: \t Level %i process with pid=%i.\n", i, sharedMemory[i]);

                for(i = 1; i < numProcs; i++) {
                    kill(sharedMemory[i], SIGUSR1);
                    usleep(100);
                }
            }
        }

    munmap(sharedMemory, numProcs);
    printf("EXITING: Level %i process with pid=%i, child of ppid=%i.\n", level, getpid(), getppid());
    exit(0);
    }
    else {
        level = child;
        child_function();
    }

    return 0;
}
