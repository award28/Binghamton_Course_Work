#include "ssfs.hpp"
#include <pthread.h>
#include <iostream>
#include <cstdlib>
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



int main(int argc, char* argv[]){
	int numThreads, i;
	char *diskName;
	char *file[4];
	
	if(argc < 3 || argc > 6){
		cout << "Usage ./" << argv[0] << " <disk file name> <thread1 file name> ..." << endl;
		exit(1);
	} 

	diskName = argv[1];

	numThreads = argc - 2;
	for(i = 2; i < argc; i++){
		file[i - 2] = argv[i];
	}

	pthread_t threads[numThreads];
	for(i = 0; i < numThreads; i++){
		diskOpArg temp;
		temp.fileName = file[i];
		pthread_create(&threads[i], NULL, diskOp, (void *)temp);
		cout << file[i] << endl;
	}
}
