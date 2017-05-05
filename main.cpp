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
    std::queue<op> buff;
};

void* diskOp(void *arg){
    diskOpArg *a = (diskOpArg*) arg;
    disk_op diskOp(a->fileName, (a->buff));
    return NULL;
}

void* controller(void *arg) {
    Controller *controller = (Controller*)arg;

    /*
    showdown = false;

    while(!shutdown) {
        controller->execute();
    }
    */

    return NULL;
}

int main(int argc, char *argv[]) {
    int numThreads = 0, i;
    char *file[4];
    char *disk = argv[1];

    pthread_t cThread;
    pthread_t threads[numThreads];

    std::queue<op> buffer;
    Controller *cntlr = new Controller(disk, buffer);

    numThreads = argc - 2;
    for(i = 2; i < argc; i++) {
        file[i - 2] = argv[i];
    }

    int result_code = pthread_create(&cThread, NULL, &controller, &cntlr);
    assert(!result_code);
    diskOpArg *temp;
    for(i = 0; i < numThreads; i++){
        temp = (diskOpArg *)malloc(sizeof(diskOpArg));
        temp->buff = buffer;
        temp->fileName = file[i];
        result_code = pthread_create(&threads[i], NULL, diskOp, (void *)temp);
        assert(!result_code);
        cout << file[i] << endl;
    }

    for(i = 0; i < numThreads; i++){
        result_code = pthread_join(threads[i], NULL);
        assert(!result_code);
    }

    result_code = pthread_join(cThread, NULL);
    assert(!result_code);

    return 0;
}
