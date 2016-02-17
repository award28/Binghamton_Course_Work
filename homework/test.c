#include <stdio.h>

int getFirst(int);
int main(int argc, char **argv) {
	int x;
	x=getFirst(23);
	if (x==12) return 1;
	return 0;
}
int getFirst(int st) {
	return (st*124639 % 33167);
}
