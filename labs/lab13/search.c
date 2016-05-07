#include "search.h"
#include <stdio.h>
#include <string.h>

int numHits(char * file,char * srch) {
	FILE * fl=fopen(file,"r");
	if (fl==NULL) {
		char errorMsg[80]="Failed to open file ";
		strcat(errorMsg,file);
		strcat(errorMsg," Error: ");
		perror(errorMsg);
		return 0;
	}
	int count=0;
	int matched=0;
	int fc;
	fc=getc(fl);
	while(fc != EOF) {
		if (fc==srch[matched]) {
			matched++;
			if (srch[matched]=='\0') {
				count++;
				matched=0;
			}
		} else matched=0;
		fc=getc(fl);
	}
	fclose(fl);
	return count;
}