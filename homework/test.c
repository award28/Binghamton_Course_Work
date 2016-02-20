#include <stdio.h>
#include <math.h>

int main(int argc, char **argv) {
   float exp = -1.0;
   float current = powf(2.0, exp);
   for(int i = 0; i < 20; i++) { 
       current = powf(2.0, exp);
       printf("%f\n",current);
        exp -= 1.0;
   }
}
