#ifndef SSFS_HPP
#define SSFS_HPP

#include <iostream>
#include <string>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <queue>
#include <vector>
#include <cmath>

typedef std::pair<bool*, int> Bitmap;
typedef std::pair<struct Inode, int> InodeData;

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
        bool execute();
        std::queue<op> *buffer;
    private:
        std::string read(std::string &name, int start, int size);
        std::string cat(std::string &name);
        bool write(std::string &name, int start, int size, std::string &data);
        bool import(std::string &name, std::string &file);
        InodeData createInode(std::string &name);
        InodeData findInode(std::string &name);
        void updateInode(Inode inode, int pos);
        bool deleteFile(std::string &name);
        std::vector<int> posArray(Inode inode);
        std::vector<int> ibpArray(int ibp);
        int findFreePos();
        std::string list();
        SuperBlock sb;
        std::string disk;
        unsigned long long inodeStart;
        unsigned long long filesStart;
        Bitmap bitmap;
        bool shutdown;
};

class disk_op {
    public:
        disk_op(std::string f_name, std::queue<op> *buf, pthread_mutex_t *mx);
    private:
        void parse(op &curr_op, std::string line);
        void push_op(std::queue<op> *buf, op out_op, pthread_mutex_t *mx);
};
#endif
