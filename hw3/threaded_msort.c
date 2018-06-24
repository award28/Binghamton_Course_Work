#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include "common.h"

int str_is_decimal_num(char * str);
int is_regular_file(char * file_path);
int number_of_lines(FILE * fp);
int cmpfunc(const void *, const void *);

typedef struct QSORT_INFO {
    int begin_idx;
    int chunk;
    int *data;
} qs_info;

typedef struct MERGE_INFO {
    int start_idx;
    int first_size;
    int second_size;
    int *data;
} merge_info;

void * qsorter(void * arg) {
	qs_info * info = (qs_info *) arg;

	info->data += info->begin_idx;
	qsort(info->data, info->chunk, sizeof(int), cmpfunc);
	printf("qsort thread: start element idx: %d; sorting size: %d\n", \
		info->begin_idx, info->chunk);

	return 0;
}

void * merger(void * arg) {
	merge_info * info = (merge_info *) arg;
	info->data += info->start_idx;
	printf("merge thread: start element idx: %d; 1st split size: %d; 2nd split size: %d\n", \
		info->start_idx, info->first_size, info->second_size);

	qsort(info->data, info->first_size + info->second_size, sizeof(int), cmpfunc);
	return 0;
}

int main(int argc, char * argv[])
{
    char *idata_fp = NULL, *line = NULL;
    FILE *idata_fs = NULL;
    size_t len;
    unsigned int data_size = 0;
    int split_num = 0, i = 0;
    int *data = NULL;

    /* --- handle user inputs --- */
    if (argc < 3) {
        printf("Usage: %s input_data_file split_num\n", argv[0]);
        exit(1);
    }

    if (!is_regular_file(argv[1])) {
        printf("Regular input data file %s does not exist.\n", argv[1]);
        exit(1);
    }

    if (!str_is_decimal_num(argv[2])) {
        printf("%s is not a valid split size. It should be a decimal number. \n", argv[2]);
        exit(1);
    }

    idata_fp = argv[1];
    split_num = atoi(argv[2]);

    /* --- open the input data file --- */
    idata_fs = fopen(idata_fp, "r");
    if (NULL == idata_fs) {
        EXIT_ERROR(ERROR, "fopen failed!\n");
    }

    /* --- get the number of input data, and allocate data buffer accordingly ---*/
    data_size = number_of_lines(idata_fs);
    if (data_size < split_num)
    {
        printf("data_size(%d) is smaller than split_num(%d)!\n", data_size, split_num);
        exit(1);
    }

    /* --- allocate mem for the input data --- */
    data = malloc(data_size * sizeof(*data));
    if (NULL == data) {
        EXIT_ERROR(ERROR, "malloc failed!\n");
    }

    /* --- read the numbers to sort from the input file to the data buffer ---*/
    i = 0;
    while (getline(&line, &len, idata_fs) != -1) {
        data[i] = atoi(line);
        i++;
    }

    /* --- print the input data ---*/
    printf("========== input data (data_size=%d, split_num=%d) ==========\n", data_size, split_num);
    for (i = 0; i < data_size; i++) {
        printf("%d ", data[i]);
    }
    printf("\n");

	pthread_t tids[split_num];
	pthread_attr_t attrs[split_num];
	qs_info qsInfo;

	int finished = 0;

	printf("----- qsort round: %d threads needed -----\n", split_num);
    	int chunk = data_size / split_num;
	int last = data_size - ((split_num - 1) * chunk);

        for(int i = 0; i < split_num; i++) {
                qsInfo.begin_idx = chunk*i;
		qsInfo.chunk = (split_num - i - 1) ? chunk : last;
		qsInfo.data = data;
        
		pthread_attr_init(&attrs[i]);
		pthread_create(&tids[i], &attrs[i], qsorter, &qsInfo);
		pthread_join(tids[i], NULL);
        }

	merge_info mergeInfo;
	int num_sorted_splits = split_num;
	int split_size;
	for (int p = floor((float)num_sorted_splits/2); p > 1 || !finished; p = floor((float)num_sorted_splits/2)) {
   	    split_size = data_size/num_sorted_splits;
	    num_sorted_splits -= p;
	    finished = p <= 1;

 	    printf("----- merge round: %d threads needed -----\n", p);
	        for(int i = 0; i < p; i++) {
	            mergeInfo.start_idx = split_size*2*i;
		    mergeInfo.first_size = split_size;
		    mergeInfo.second_size = (finished) ? data_size - split_size : split_size;
		    mergeInfo.data = data;
                    
		    pthread_attr_init(&attrs[i]);
		    pthread_create(&tids[i], &attrs[i], merger, &mergeInfo);
		    pthread_join(tids[i], NULL);
	    
		}
	}

    /* --- print the result ---*/
    fprintf(stderr, "========== threaded merge sort result ==========\n");
    for (i = 0; i < data_size; i++) {
        printf("%d ", data[i]);
    }
    printf("\n");


    /* --- free resourses ---*/
    if (line) {
        free(line);
        line = NULL;
    }

    if (data) {
        free (data);
        data = NULL;
    }
    
    fclose(idata_fs);
    exit(0);
}
