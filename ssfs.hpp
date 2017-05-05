#ifndef SSFS_HPP
#define SSFS_HPP
#include <iostream>
#include <string>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>

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
        Controller(char disk[]);
        char* read();
        bool write(char data[]);
        std::string execute(op command);
    private:
        char* disk;
        std::queue<op> exe_queue;
};

class disk_op {
    public:
        disk_op(string f_name);
};

#endif
