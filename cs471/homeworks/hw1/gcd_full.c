#include <stdio.h>
#include "gcd.h"


/* Imperative style modification of example 1.20  */

int gcdI(int i, int j) {
	while (i != j) { 
		if (i > j) {
			i = i - j;
		} else {
			j = j - i;
		}
	}      
	return i;
}


/* Modiification of 1.4 page 38 */
int  gcdM(int i, int j) {
	while (i != j) {
		if (i > j) {
			i = i % j;
		} else {
			j = j % i;
		}
	}
	return i;

}


int gcd_myM(int i, int j) {
	while(i != j) {
		if (i > j) {
			if (!(i % j)) return j;
			i = i % j;
		} else {
			if (!(j % i)) return i;
			j = j % i;
		}
	}
	return i;
} 


/* 
  ADD code for the recursive style implementation
*/
int  gcdF(int i, int j) {
	if (!(i % j)) return j;
	return gcdF(j, i % j);
}


int main(int argc, char **argv) {
	if (argc < 3) {
		printf("%s usage: [I] [J]\n", argv[0]);
		return 1;
	}
	int i = atoi(argv[1]);
	int j = atoi(argv[2]);
	int r = gcdF(i,j);
	printf("%d\n", r);
	return 0;
}
