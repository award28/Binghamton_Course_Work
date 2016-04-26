#include <stdio.h>
#include <string.h>
#include "printStack.h"

void printFrameStack(stackptr sp, baseptr bp, int nparms, char *prefix) {
	int current=0;
	if (0==strlen(prefix)) current=1;
	if (bp!=main_base) {
		char newPref[100]="caller's ";
		strcat(newPref,prefix);
		printFrameStack((void *)bp+4,bp->prev_nframe,nparms,(char *)newPref);
	}
	int i;
	int stackSize=(((void *)bp-(void *)sp)/4);
	printf("--------------- %s Stack Frame ------------------\n",current?"Current":prefix);
	for(i=stackSize; i>=0; i--) {
			printf("    	0x%08x -> %08x = %12d",sp+i,*(sp+i),*(sp+i));
			if (i==stackSize) printf(" ; %s ebp",prefix);
			if (i<=nparms && i>0 && !current) printf(" ; %s argument %i",prefix,i);
			if (i==0 && !current) printf(" ; %s return address",prefix);
			printf("\n");
	}
}



void printStackFrame(stackptr sp,baseptr bp,int nparms) {
	int i;
	int stackSize=(((void *)bp-(void *)sp)/4);
	printf("  Frame @ ebp=%08x ->  esp=%08x\n",bp,sp);
	printf("  Frame size: %d words = %d bytes\n",stackSize,stackSize*4);
	printf("  Previous frame @ %08x -> %008x\n", bp->prev_nframe,bp+1);
	printf("  Return address = %08x\n", bp->return_addr);
	if (nparms>0) {
		printf("  Parameters:\n");
		for(i=0; i < nparms; i++) {
			printf("   Parm %3d   = %08x\n",i+1,bp->parms[i]);
		}
	}
	printf("  Stack Frame Contents:\n");
	for(i=stackSize; i>=0; i--) {
		printf("    0x%02x(esp) = -0x%02x(ebp) -> %08x = %12d\n",
			i*sizeof(void *),(stackSize-i)*sizeof(void *),*(sp+i),*(sp+i));
	}
	printf("\n");
}
