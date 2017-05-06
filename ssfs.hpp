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
    int start = 0;
    int size = 0;
    char* data;
    pid_t pid;
    std::string *response;
    pthread_cond_t *cond;
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
        Controller(std::string &disk, std::queue<op> *buffer);
        std::string read(std::string &name, int start, int size);
        bool write(std::string &name, int start, int size, char *data);
        bool execute();
    private:
        std::string disk;
        int inodeStart;
        std::queue<op> *buffer;
};

class disk_op {
    public:
        disk_op(std::string f_name, std::queue<op> *buf, pthread_mutex_t *mx);
    private:
        void parse(op &curr_op, std::string line);
        void push_op(std::queue<op> *buf, op out_op, pthread_mutex_t *mx);
};
#endif
