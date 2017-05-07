#include <pthread.h>
#include <iostream>
#include <unistd.h>
#include <assert.h>
#include <string>

#include "ssfs.hpp"

using std::cout;
using std::endl;
using std::string;

struct diskOpArg {
    string fileName;
    std::queue<op> *buff;
    pthread_mutex_t *mutex;
};

void* diskOp(void *arg){
    diskOpArg *a = (diskOpArg*) arg;
    disk_op diskOp(a->fileName, a->buff, a->mutex);
    return NULL;
}

void* controller(void *arg) {
    Controller *controller = (Controller*)arg;

    while (controller->execute()) {}
    
    return NULL;
}

int main(int argc, char *argv[]) {
    int numThreads = argc - 2, i;
    char *file[4];
    string disk = argv[1];

    pthread_t cThread;
    pthread_mutex_t mx;
    pthread_t threads[numThreads];

    std::queue<op> *buffer = new std::queue<op>;
    Controller *cntlr = new Controller(disk, buffer);
    cout << "Getting here" << endl;

    numThreads = argc - 2;
    for(i = 2; i < argc; i++) {
        file[i - 2] = argv[i];
    }

    int result_code;


    diskOpArg *temp = (diskOpArg *)malloc(sizeof(diskOpArg));
    temp->buff = buffer;
    temp->mutex = &mx;


    for(i = 0; i < numThreads; i++){
        temp->fileName = file[i];
        result_code = pthread_create(&threads[i], NULL, diskOp, (void *)temp);
        assert(!result_code);
    }

    for(i = 0; i < numThreads; i++){
        result_code = pthread_join(threads[i], NULL);
        assert(!result_code);
    }

    result_code = pthread_create(&cThread, NULL, &controller, cntlr);
    assert(!result_code);

    result_code = pthread_join(cThread, NULL);
    assert(!result_code);

    return 0;
}
