#include <fcntl.h> //open
#include <unistd.h> //close
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include "usr_functions.h"
#include "mapreduce.h"
#include "common.h"

// add your code here ...


void mapreduce(MAPREDUCE_SPEC * spec, MAPREDUCE_RESULT * result)
{
    // Get file size to get chunk size of each split 
    int fd = open(spec->input_data_filepath, O_RDONLY);
    int size = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET); //Reset head to start of file
    close(fd);

    int chunk = size/spec->split_num;
    int excess = size % spec->split_num;
    int is_letter_counter = spec->usr_data == NULL;
    int fork_num = spec->split_num;

    struct timeval start, end;

    if (NULL == spec || NULL == result)
    {
        EXIT_ERROR(ERROR, "NULL pointer!\n");
    }
    
    gettimeofday(&start, NULL);

    pid_t driver = fork();				//Create initial map worker
    while(--fork_num && driver) driver = fork();	//Create remaining map workers

    if (!driver) {
        DATA_SPLIT split;
        split.fd = open(spec->input_data_filepath, O_RDONLY);
        split.size = chunk;
        split.usr_data = spec->usr_data;
        if (fork_num - 1 == spec->split_num) split.size += excess;

        int from = chunk*fork_num;
        if (fork_num) {
            lseek(split.fd, chunk*fork_num + 1, SEEK_SET);
            printf("Reading from %d to %d\n", from + 1, chunk*fork_num + split.size);
	} else {
            lseek(split.fd, chunk*fork_num, SEEK_SET);
            printf("Reading from %d to %d\n", from, chunk*fork_num + split.size);
	}

        //Define fd out names, i.e. mr-2.itm
        int num_len = snprintf( NULL, 0, "%d", fork_num );
        char* fork_num_str = malloc( num_len + 1 );
        snprintf( fork_num_str, num_len + 1, "%d", fork_num );
        char * fd_out_name = malloc(num_len + 8);
        memcpy(fd_out_name, "mr-", 3);
        memcpy(fd_out_name + 3, fork_num_str, num_len);
        memcpy(fd_out_name + 3 + num_len, ".itm", 5);

        int fd_out = open(fd_out_name, O_RDWR | O_CREAT | O_TRUNC);
        if (is_letter_counter) {
    	letter_counter_map(&split, fd_out);
    	//letter_counter_reduce(&split, fd_out);
        } else {
    	word_finder_map(&split, fd_out);
    	//word_finder_reduce(&split, fd_out);
        }
        free(fd_out_name);
        free(fork_num_str);

        close(split.fd);
        close(fd_out);

        _exit(0);
    }

    gettimeofday(&end, NULL);   

    result->processing_time = (end.tv_sec - start.tv_sec) * US_PER_SEC + (end.tv_usec - start.tv_usec);
}
