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
    std::string cmd;
    std::string name;
    int start;
    int size;
    char* data;
    pid_t pid;
};

struct p_file {
    char name[33];
    int size; // in bytes
    int dbp[12];
    int *ibp;
    int **dibp;
    // data ??
};

class Controller {
    public:
        Controller(const char *disk, std::queue<op> &buffer);
        char* read(std::string &name, int start, int size);
        bool write(std::string &name, int start, int size, char *data);
        void execute();
    private:
        const char* disk;
        std::queue<op> buffer;
};

class disk_op {
    public:
        disk_op(std::string f_name, std::queue<op> &buf);
    private:
        void parse(op &curr_op, std::string line);
};
#endif
