#ifndef SSFS_HPP
#define SSFS_HPP
#include <iostream>
#include <string>
#include <pthread.h>

struct SuperBlock {  
    int dataBlocks;
    int numInodes;
};

class Controller {
    public:
        char* read();
        bool write(char data[]);
    private:
        bool bitmap[256] = {false};
        bool inodeTable[256] = {false};
};

struct op {
    std::string command;
    pthread_t pid;
};
//std::queue<op> exe_queue;

class disk_op {
    public:
        disk_op(string f_name);
    private:
        run(
}

#endif
