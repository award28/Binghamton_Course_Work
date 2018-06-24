#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <string.h>
#include <time.h> 

int cmpfunc (const void * a, const void * b) {
    return ( *(int*)a - *(int*)b );
}

int main(int argc, char **argv, char *envp[]) {
    clock_t t;
    
    t = clock();

    FILE *inputFile, *outputFile, *countFile;
    char *userid = getenv("USER");
    double time_taken;
    int uidSize = strlen(userid);
    int valSize = argc - optind;
    int *values;
    int *uidOccurence = (int*) malloc(sizeof(int) * 128);
    int numInts = 100;
    int numIntsFlag = 0;
    int inputFileFlag = 0;
    int countFileFlag = 0;
    int outputFileFlag = 0;
    int minInt = 1;
    int maxInt = 255;
    int curVal;
    int i; 
    int j;
    int c;

    if (uidOccurence == NULL) {
        perror("Error with uidOccurence: ");
        exit(1);
    }
    
    for(i = 0; i < 128; i++) uidOccurence[i] = 0;

    while ((c = getopt(argc, argv, "c:i:m:M:n:o:u")) != -1)
        switch (c) {
            case 'c':
                countFileFlag = 1;
                countFile = fopen(optarg, "w");
                if(countFile == NULL) {
                    fprintf(stderr, "Error on flag -i: Can't open the count file %s.\n", optarg);
                    exit(1);
                }
                break;
            case 'i':
                inputFileFlag = 1;
                inputFile = fopen(optarg, "r");
                if(inputFile == NULL) {
                    fprintf(stderr, "Error on flag -i: Can't open the input file %s.\n", optarg);
                    exit(1);
                }
                break;
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
                    fprintf (stderr, "Error on flag -n: The number of integers which can be sorted must be between 0 and 1,000,000.\n");
                    exit(0);
                }
                numIntsFlag = 1;
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
            case 'u':
                fprintf (stderr, "Usage: prog1sorter [options]\n\tOptions:\n\t-u,\tPrint usage statement\n\t-n,\tMax number of integers to sort\n\t-m,\tMinimum value allowed to be sorted\n\t-M,\tMaximum value allowed to be sorted\n\t-i,\tFile name to read input from\n\t-o,\tFile name to output sorted values\n\t-c,\tFile name to output ASCII value association to username characters\n");
                exit(0);
                break;
            case '?':
                if (optopt == 'c' ||
                    optopt == 'i' ||    
                    optopt == 'm' || 
                    optopt == 'M' || 
                    optopt == 'n' || 
                    optopt == 'o') 
                    fprintf(stderr, "Option -%c requires an argument.\n", optopt);
                else if (isprint (optopt))
                    fprintf(stderr, "Unknown option `-%c'.\n", optopt);
                else
                    fprintf(stderr, "Unknown option character `\\x%x'.\n", optopt);
                return 1;
            default:
                abort();
        }

    if(inputFileFlag) {
        fscanf(inputFile, "%i", &valSize);

        values = (int*) malloc(sizeof(int) * valSize);
        if (values == NULL) {
            perror("Error with values: ");
            exit(1);
        }

        if(numIntsFlag) {
            if(numInts != valSize) {
                fprintf(stderr, "Error on flag -n: The number of integers specified must be the same.\n");
                exit(0);
            }
        }

        for(i = 0; fscanf(inputFile, "%i", &curVal) != EOF && i < numInts && i < valSize;) {
            if(minInt <= curVal && curVal <= maxInt) {
                values[i] = curVal;
                i++;
            }
        }
        valSize = i;

        fclose(inputFile);
    }
    else {
        fscanf(stdin, "%i", &valSize);

        values = (int*) malloc(sizeof(int) * valSize);
        if (values == NULL) {
            perror("Error with values: ");
            exit(1);
        }

        if(numInts != valSize && numIntsFlag) {
            fprintf (stderr, "Error on flag -n: The number of integers specified must be the same.\n");
            exit(0);
        }
        
        for(i = 0, j = 0; i < valSize; i++) {
            fscanf(stdin, "%i", &curVal);
            if(minInt <= curVal && curVal <= maxInt) {
                values[j] = curVal;
                j++;
            }
        }
        valSize = j;
    }

    qsort(values, valSize, sizeof(int), cmpfunc);

    if(outputFileFlag) {
        for(i = 0 ; i < valSize; i++) {
            fprintf(outputFile, "%d\n", values[i]);
            if(values[i] < 128)
                uidOccurence[values[i]]++;
        }
        fclose(outputFile);
    }
    else {
        for(i = 0 ; i < valSize; i++) {
            printf("%d\n", values[i]);
            if(values[i] < 128)
                uidOccurence[values[i]]++;
        }
    }

    if(countFileFlag) {
        for(i = 0; i < uidSize; i++)
            fprintf(countFile, "%c\t%i\t%i\n", userid[i], userid[i], uidOccurence[(int)userid[i]]);
        fclose(countFile);
    }
    else {
        for(i = 0; i < uidSize; i++)
            printf("%c\t%i\t%i\n", userid[i], userid[i], uidOccurence[(int)userid[i]]);
    }

    t = clock() - t;
    time_taken = (((double)t)/CLOCKS_PER_SEC)*1000; // in seconds

    fprintf(stderr, "prog1sorter took %f milliseconds\n", time_taken);

    free(values);
    free(uidOccurence);

    return 0;
}
