#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
	char buffer[1024];
	union {
		unsigned int ival;
		char cval[4];
	} pval;

	while(fgets(buffer,sizeof(buffer),stdin)) {
		while (buffer[strlen(buffer)-1]=='\n')
			buffer[strlen(buffer)-1]=0x00; // chomp newline

		switch(buffer[0]) {
			case 'C' :
				printf("%s",buffer+2);
				break;

			case 'D' :
				if (1==sscanf(buffer+2,"%i ",&pval.ival)) {
					putchar(pval.cval[0]);
					putchar(pval.cval[1]);
					putchar(pval.cval[2]);
					putchar(pval.cval[3]);
				}
				break;
			default:
				fprintf(stderr,"Unrecognized: %s\n",buffer);
		}
	}
	putchar('\n');
	return 0;
}

