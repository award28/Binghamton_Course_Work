#include<stdio.h>

float factorial(float n);

int main(int argv,char **argc) {

	float n,fn;

	for(fn=n=2; fn>0; n++) {
		fn=factorial(n);
		printf("factorial(%f)=%f\n",n,fn);
	}
	return(0);

}

float factorial(float n) {
	if(n > 1) { n = n * factorial(n-1);}
	return n;
}

