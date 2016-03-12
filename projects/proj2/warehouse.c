#include "slots.h"
#include <stdio.h>

int main(int argc, char ** argv) {

	int bin;

	initSlots();
	while(1==scanf("%d",&bin)) {
		if (-1==findSlot(bin)) {
			getBin(bin,0);
		}
		getWidget(bin);
	}
	printEarnings();
	return 0;
}

