#include "ssfs.hpp"
#include <pthread.h>
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <assert.h>
#include <string>

using namespace std;

struct diskOpArg {
	string fileName;
	Controller *controller;
};

void* diskOp(void *arg){
	diskOpArg *a = (diskOpArg*) arg;
	disk_op disOp(a->fileName, *(a->controller));
    return NULL;
}

void* controller(void *arg) {
    Controller *controller = (Controller*)arg;

    char *res = controller->read(0, 0);
    cout << res << endl;

    return NULL;
}
    
int main(int argc, char *argv[]) {
	int numThreads = 0, i;
	char *file[4];
    char *disk = argv[1];

    pthread_t cThread;
	pthread_t threads[numThreads];

    Controller *cntlr = new Controller(disk);
    std::queue<op> buffer;

	numThreads = argc - 2;
	for(i = 2; i < argc; i++){
		file[i - 2] = argv[i];
	}

    int result_code = pthread_create(&cThread, NULL, &controller, cntlr);
    assert(!result_code);
    diskOpArg *temp;
	for(i = 0; i < numThreads; i++){
        temp = (diskOpArg *)malloc(sizeof(diskOpArg));
        temp->controller = cntlr;
		temp->fileName = file[i];
		result_code = pthread_create(&threads[i], NULL, diskOp, (void *)temp);
        assert(!result_code);
		cout << file[i] << endl;
	}

    for(i = 0; i < numThreads; i++){
        result_code = pthread_join(threads[i], NULL);
        assert(!result_code);
    }

       result_code = pthread_join(cThread, NULL );
    assert(!result_code);

 return 0;
}
