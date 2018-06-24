#include <stdio.h>
#include <stdlib.h>
#include "printStack.h"

int main(int argc, char *argv[])
{
	SAVE_BASE_POINTER;
	

   printf("Factorial 6=%d\n",factorial(6));

	exit(0);
}

int factorial(int n) {
	printf("Before recursion\n");
	printFrame(1);
	int answer = 3735928559;
	if (n<3) answer=n;
	else answer=(factorial(n-1) * n);
	printf("After recursion\n");
	printFrame(1);
	return answer;
}
