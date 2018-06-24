#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <time.h> 

int cmpfunc (const void * a, const void * b) {
    return ( *(int*)a - *(int*)b );
}

int main(int argc, char **argv, char *envp[]) {
    FILE *outputFile;
    int numInts = 100;
    int outputFileFlag = 0;
    int seedFlag = 0;
    int minInt = 1;
    int maxInt = 255;
    unsigned long seed;
    time_t t;
    int i; 
    int c;

    while ((c = getopt(argc, argv, "m:M:n:o:s:u")) != -1)
        switch (c) {
            case 'm':
                if(atoi(optarg) < 1) {
                    fprintf (stderr, "Error on flag -m: The minimum number of an integer must be greater than 1.\n");
                    exit(0);
                }
                minInt = atoi(optarg);
                break;
            case 'M':
                if(atoi(optarg) > 1000000) {
                    fprintf (stderr, "Error on flag -M: The maximum number of an integer must be less than 1,000,000.\n");
                    exit(0);
                }
                maxInt = atoi(optarg);
                break;
            case 'n':
                if(atoi(optarg) > 1000000 || atoi(optarg) < 0) {
                    fprintf (stderr, "Error on flag -n: The number of integers which can be generated must be between 0 and 1,000,000.\n");
                    exit(0);
                }
                numInts = atoi(optarg);
                break;
            case 'o':
                outputFileFlag = 1;
                outputFile = fopen(optarg, "w");
                if(outputFile == NULL) {
                    fprintf(stderr, "Error on flag -o: Can't open the output file %s.\n", optarg);
                    exit(1);
                }
                break;
            case 's':
                seedFlag = 1;
                seed = atoi(optarg);
                break;
            case 'u':
                fprintf (stderr, "Usage: prog1generator [options]\n\tOptions:\n\t-u,\tPrint usage statement\n\t-n,\tNumber of integers to generate\n\t-m,\tMinimum value allowed to be generated\n\t-M,\tMaximum value allowed to be generated\n\t-o,\tFile name to output generated values\n\t-s,\tSeed for the random generated numbers\n");
                exit(0);
                break;
            case '?':
                if (optopt == 'm' ||
                    optopt == 'M' ||    
                    optopt == 'n' || 
                    optopt == 'o' || 
                    optopt == 's' || 
                    optopt == 'u') 
                    fprintf(stderr, "Option -%c requires an argument.\n", optopt);
                else if (isprint (optopt))
                    fprintf(stderr, "Unknown option `-%c'.\n", optopt);
                else
                    fprintf(stderr, "Unknown option character `\\x%x'.\n", optopt);
                return 1;
            default:
                abort();
        }

    if(minInt > maxInt) {
        fprintf(stderr, "Error on flag -M & -m: The max can not be less than the min.\n");
        exit(1);
    }

    // Intializes random number generator
    if(seedFlag)
        srand(seed);
    else 
        srand((unsigned) time(&t));

    if(outputFileFlag) {
        fprintf(outputFile, "%i\n", numInts);
        for(i = 0 ; i < numInts; i++) {
            fprintf(outputFile, "%d\n", (rand() % (maxInt - minInt + 1)) + minInt);
        }

        fclose(outputFile);
    }
    else {
        printf("%i\n", numInts);
        for(i = 0 ; i < numInts; i++) {
            printf("%d\n", (rand() % (maxInt - minInt + 1)) + minInt);
        }
    }

    return 0;
}
