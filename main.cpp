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
    pthread_mutex_t *mutex;
};

void* diskOp(void *arg){
    diskOpArg *a = (diskOpArg*) arg;
    disk_op diskOp(a->fileName, a->buff, a->mutex);
    return NULL;
}

void* controller(void *arg) {
    Controller *controller = (Controller*)arg;

    /*
    string name = "Hello.txt";
    int start = 5000;
    int size = 28;
    char *data = "Hello Darkness my old Friend";
    controller->write(name, start, size, data);
    cout << controller->read(name, start, size) << endl;
    */

    int i = 0;
    while(i < 20) {
        controller->execute();
        i++;
    }

    return NULL;
}

int main(int argc, char *argv[]) {
    int numThreads = argc - 2, i;
    char *file[4];
    string disk = argv[1];

    pthread_t cThread;
    pthread_mutex_t mx;
    pthread_t threads[numThreads];

    std::queue<op> buffer;
    Controller *cntlr = new Controller(disk, buffer);

    for(i = 2; i < argc; i++) {
        file[i - 2] = argv[i];
    }

    int result_code;

    diskOpArg *temp;
    for(i = 0; i < numThreads; i++){
        temp = (diskOpArg *)malloc(sizeof(diskOpArg));
        temp->buff = buffer;
        temp->fileName = file[i];
        temp->mutex = &mx;
        result_code = pthread_create(&threads[i], NULL, diskOp, (void *)temp);
        assert(!result_code);
        cout << file[i] << endl;
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
