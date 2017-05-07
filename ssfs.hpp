#ifndef SSFS_HPP
#define SSFS_HPP

#include <iostream>
#include <string>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <queue>
#include <cmath>

typedef std::pair<bool*, int> Bitmap;

struct SuperBlock {  
    int numBlocks;
    int blockSize;
};

struct op {
    std::string cmd;
    std::string name;
    int start = 0;
    int size = 0;
    std::string data;
    pid_t pid;
    std::string *response;
    pthread_cond_t *cond;
};

struct Inode {
    std::string name;
    int size;
    int dbp[12];
    int ibp;
    int dibp;
};

class Controller {
    public:
        Controller(std::string &disk, std::queue<op> *buffer);
        std::string read(std::string &name, int start, int size);
        bool write(std::string &name, int start, int size, std::string &data);
        Inode createInode(std::string &name);
        Inode findInode(std::string &name);
        bool execute();
    private:
        SuperBlock sb;
        std::string disk;
        unsigned long long inodeStart;
        unsigned long long filesStart;
        Bitmap bitmap;
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
