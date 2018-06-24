#include <stdlib.h>
#include <stdio.h>
#include <math.h>

double root(double n,double tol);
double howClose(double n, double root);

int main(int argc, char **argv) {

	if (argc != 3) { 
		printf("Invoke %s <n> <e> where <n> is the number to find the square root of, and <e> is the tolerance.\n",argv[0]);
		return 1;
	}
	
	double n=atof(argv[1]);
	double err=atof(argv[2]);
	
	if (n<=0) {
		printf("Invoke %s <n> where <n> is a positive floating point number - you entered %s\n",argv[0],argv[1]);
		return 1;
	}
	
	double rn=root(n,err);
	printf("The square root of %g is %g\n",n,rn);
	return 0;
}

double root(double n,double tol) {

	int iter=0;
	double root=n/2;
	double error=howClose(n,root);
	double prev_root = root;
	while(error > tol) {
		
		iter++;
		/* Calculate a new value for root here */
		root = (root + (n/root))/2;				

		error=howClose(n,root);
		printf("  After %d iterations, root=%g error=%g\n",iter,root,error);
	
		if(root == prev_root) {
			printf("The new root %g is the same as the old root, %g.\n", root, prev_root);
			return prev_root;
		}
		prev_root = root;
	}
	return root;	
}

double howClose(double n, double root) {

	return fabs(n-root*root); /* fabs is floating point absolute value... fabs(3.6) = 3.6; fabs(-2.5) = 2.5 */
	
}
	
