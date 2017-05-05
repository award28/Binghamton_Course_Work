#include "ssfs.hpp"
#include <pthread.h>
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <assert.h>
#include <string>

using namespace std;

typedef struct diskOpArg {
	string fileName;
	//Controller &controller;
} diskOpArg;

void* diskOp(void *arg){
	diskOpArg *diskOpArg = arg;
	disk_op disOp(arg.fileName, arg.controller);
}

void* controller(void *arg) {
    Controller*controller = (Controller*)arg;

    char *res = controller->read(0, 0);
    cout << res << endl;

    return NULL;
}
    
int main(int argc, char *argv[]) {
    char *disk = argv[1];
	int numThreads, i;
	char *diskName;
	char *file[4];

    pthread_t cThread;
	pthread_t threads[numThreads];

    Controller *cntlr = new Controller(disk);
    std::queue<op> buffer;

	diskName = argv[1];

	numThreads = argc - 2;
	for(i = 2; i < argc; i++){
		file[i - 2] = argv[i];
	}

    int result_code = pthread_create(&cThread, NULL, &controller, cntlr);
    assert(!result_code);

    result_code = pthread_join(cThread, NULL );
    assert( !result_code );
	for(i = 0; i < numThreads; i++){
		diskOpArg temp;
		temp.fileName = file[i];
		pthread_create(&threads[i], NULL, diskOp, (void *)temp);
		cout << file[i] << endl;
	}

    return 0;
}
