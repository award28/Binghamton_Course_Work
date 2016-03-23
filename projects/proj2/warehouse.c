#include "slots.h"
#include <stdio.h>

typedef int bool;
#define true 1
#define false 0

int findLowest(int one, int two, int three, int four);

int main(int argc, char ** argv) {

	int bin;
    int bins[100] = { 0 };
    int curBins[4] = { -1, -1, -1, -1 };
    int slotToInsert = 0;
    int lowestNum = 0;
    bool inserted;
    bool replaced;

	initSlots();
	while(1==scanf("%d",&bin)) {
        inserted = false;
        replaced = false;
		bins[bin] += 1;

        //If needed bin isn't in a slot
        if (-1==findSlot(bin)) {
            
            //Check if there's an open slot
            for(int i = 0; i < 4 && !inserted; i++ ) {
                if(curBins[i] == -1) { 
                    curBins[i] = bin;
                    slotToInsert = i;
                    inserted = true;
                }
            }
            //If not, check which bin's been used the least
            if(!inserted) {
                lowestNum = findLowest(bins[curBins[0]], bins[curBins[1]], bins[curBins[2]], bins[curBins[3]]);
                for(int i = 0; i < 4 && !replaced; i++) {
                    if(lowestNum == bins[curBins[i]]) {
                        slotToInsert = i;
                        replaced = true;
                    }
                }
            }
            //return said bin, and get the one that's needed
            getBin(bin,slotToInsert);
		}
		getWidget(bin);
	}
	printEarnings();
	return 0;
}

int findLowest(int one, int two, int three, int four) {
   int smallest = one;
   int choices[4] = { one, two, three, four };
   for(int i = 0; i < 4; i++) if(smallest > choices[i]) smallest = choices[i];
   return smallest;
}

