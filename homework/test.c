#include <stdio.h>
#include <math.h>

int main(int argc, char **argv) {
	int matrix[2][3];
	int *mptr = &matrix[0][0];
	int row; int col;
	for(row=0; row<2; row++) {
		for(col=0; col<3; col++) {
			matrix[row][col] = (row*10) + col;
			printf("%d\n", matrix[row][col]);
		}
	}

	printf("The fifth element of matrix is %d\n",*(mptr+5));
}
