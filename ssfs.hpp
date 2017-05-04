#ifndef SSFS_HPP
#define SSFS_HPP
#include <iostream>
#include <string>
#include <pthread.h>

/*
class Clock {
    public:
        Clock(int arr[]);
        std::string execute(int cache);
    private:
        int accessed[numAccesses];
};
*/

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
