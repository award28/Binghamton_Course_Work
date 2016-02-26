#include <stdio.h>
#include <math.h>

int main(int argc, char **argv) {
   float exp = 140.0;
   float current = powf(2.0, exp);
   for(int i = 0; i < 20; i++) { 
       current = powf(2.0, exp);
       printf("%g -- %f\n",current,exp);
        exp -= 1.0;
   }
}
