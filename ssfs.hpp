#ifndef SSFS_HPP
#define SSFS_HPP
#include <iostream>
#include <string>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <queue>

struct SuperBlock {  
    int dataBlocks;
    int numInodes;
};

struct op {
    std::string command;
    pid_t pid;
};

class Controller {
    public:
        Controller(const char *disk);
        char* read(int, int);
        bool write(char[], int, int);
        void addCmd(op cmd);
    private:
        const char* disk;
        std::queue<op> buffer;
};

class disk_op {
    public:
        disk_op(std::string f_name);
    private:
        std::queue<op> buffer;
};

#endif
