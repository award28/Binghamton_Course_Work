#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <ctype.h>

void recFork(int levels, int children, int pauseFlag, int sleepTime) {
    pid_t pid;
    int i;

    pid = fork();

    if(pid) wait(NULL);

    if(!pid) {
        printf("ALIVE: \t Level %i process with pid=%i, child of ppid=%i.\n", levels, getpid(), getppid());

        if(levels > 0)
            for(i = 0; i < children; i++)
                recFork(levels - 1, children, pauseFlag, sleepTime);
        else if(pauseFlag) 
            pause();
        else
            sleep(sleepTime);

        printf("EXITING: Level %i process with pid=%i, child of ppid=%i.\n", levels, getpid(), getppid());
        kill(getpid(), 0);
        exit(0);
    }
}

int main(int argc, char **argv, char *envp[]) {
    int levels = 0;
    int children = 1;
    int sleepTime = 1; 
    int sleepFlag = 0;
    int pauseFlag = 0;
    int i;
    int c;

    while ((c = getopt(argc, argv, "M:N:ps:u")) != -1)
        switch (c) {
            case 'M':
                if(atoi(optarg) < 1 || atoi(optarg) > 3) {
                    fprintf (stderr, "Error on flag -M: The maximum number of child processes cannot exceed 3.\n");
                    exit(0);
                }
                children = atoi(optarg);
                break;
            case 'N':
                if(atoi(optarg) > 4 || atoi(optarg) < 0) {
                    fprintf (stderr, "Error on flag -N: The number of levels must be between 0 and 4.\n");
                    exit(0);
                }
                levels = atoi(optarg);
                break;
            case 'p':
                if(sleepFlag) {
                    fprintf (stderr, "Error on flags -s & -p: Both options cannot be choosen.\n");
                    exit(0);
                }
                pauseFlag = 1;
                break;
            case 's':
                if(pauseFlag) {
                    fprintf (stderr, "Error on flags -p & -s: Both options cannot be choosen.\n");
                    exit(0);
                }
                if(atoi(optarg) < 0) {
                    fprintf (stderr, "Error on flag -s: Time cannot be negative.\n");
                    exit(0);
                }
                sleepFlag = 1;
                sleepTime = atoi(optarg);
                break;
            case 'u':
                fprintf (stderr, "Usage: prog2tree [options]\n\tOptions:\n\t-u,\tPrint usage statement\n\t-N,\tNumber of levels\n\t-M,\tNumber of children\n\t-p,\tLeaf process should pauseFlag with pauseFlag()\n\t-s,\tLeaf process should sleep for <sleep-time>\n");
                exit(0);
                break;
            case '?':
                if (optopt == 'M' ||
                    optopt == 'N' || 
                    optopt == 'p' || 
                    optopt == 's' || 
                    optopt == 'u') {
                    fprintf(stderr, "Option -%c requires an argument.\n", optopt);
                    fprintf (stderr, "Usage: prog2tree [options]\n\tOptions:\n\t-u,\tPrint usage statement\n\t-N,\tNumber of levels\n\t-M,\tNumber of children\n\t-p,\tLeaf process should pauseFlag with pauseFlag()\n\t-s,\tLeaf process should sleep for <sleep-time>\n");
                }
                else if (isprint (optopt)) {
                    fprintf(stderr, "Unknown option `-%c'.\n", optopt);
                    fprintf (stderr, "Usage: prog2tree [options]\n\tOptions:\n\t-u,\tPrint usage statement\n\t-N,\tNumber of levels\n\t-M,\tNumber of children\n\t-p,\tLeaf process should pauseFlag with pauseFlag()\n\t-s,\tLeaf process should sleep for <sleep-time>\n");
                }
                else {
                    fprintf(stderr, "Unknown option character `\\x%x'.\n", optopt);
                    fprintf (stderr, "Usage: prog2tree [options]\n\tOptions:\n\t-u,\tPrint usage statement\n\t-N,\tNumber of levels\n\t-M,\tNumber of children\n\t-p,\tLeaf process should pauseFlag with pauseFlag()\n\t-s,\tLeaf process should sleep for <sleep-time>\n");
                }
                return 1;
            default:
                abort();
        }

    if(levels > 0)
        levels--;

    printf("ALIVE: \t Level %i process with pid=%i, child of ppid=%i.\n", levels, getpid(), getppid());

    if(levels > 0)
        for(i = 0; i < children; i++)
            recFork(levels - 1, children, pauseFlag, sleepTime);

    printf("EXITING: Level %i process with pid=%i, child of ppid=%i.\n", levels, getpid(), getppid());
    kill(getpid(), 0);

    return 0;
}
