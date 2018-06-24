#include "search.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char ** argv) {

	int ai=1;
	while (ai<argc) {
		char * srch;
		char * file;
		srch=argv[ai+1];
		file=argv[ai];
		int hits=numHits(file,srch);
		printf("File %s has %d instances of %s\n",file,hits,srch);
		ai+=2;
	}
	exit(0);
}