#include <sys/stat.h>
#include <sys/time.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h> //close
#include <fcntl.h> //open
#include <stdio.h>
#include <errno.h>

#include "usr_functions.h"
#include "mapreduce.h"
#include "common.h"

// add your code here ...

int count_lines(int fd) {
    char buf[1];
    int lines = 0;

    while(read(fd, buf, 1)) lines+= buf[0] == '\n';
    lseek(fd, 0, SEEK_SET);
    return lines;
}

void mapreduce(MAPREDUCE_SPEC * spec, MAPREDUCE_RESULT * result)
{
    char buf[5];
    int size;
    int fork_num = spec->split_num;
    int pipes_fd[fork_num][2];
    int letter_counter = spec->usr_data == NULL;
    int fd = open(spec->input_data_filepath, O_RDONLY);

    if (letter_counter) size = lseek(fd, 0, SEEK_END);
    else size = count_lines(fd);
    lseek(fd, 0, SEEK_SET); //Reset head to start of file
    close(fd);

    int chunk = size/spec->split_num;

    for(int i = 1; i < fork_num; i++) pipe(pipes_fd[i]);

    struct timeval start, end;

    if (NULL == spec || NULL == result) EXIT_ERROR(ERROR, "NULL pointer!\n");
    
    gettimeofday(&start, NULL);

    pid_t driver = fork();				//Create initial map worker

    if (driver) { 
	    result->map_worker_pid[0] = driver;
	    result->reduce_worker_pid = driver;
    }

    while(--fork_num && driver) {			//Create remaining map workers
	    driver = fork();
    	    if (driver) result->map_worker_pid[spec->split_num - fork_num] = driver;
    }

    if (!driver) {
        DATA_SPLIT split;
        split.fd = open(spec->input_data_filepath, O_RDONLY);
        split.usr_data = spec->usr_data; 
	if (fork_num + 1 == spec->split_num) split.size = size - chunk*fork_num;
	else split.size = chunk;

	if (!letter_counter) { printf("Split size: %d\n", split.size); _exit(0); }
        if (fork_num) lseek(split.fd, chunk*fork_num + 1, SEEK_SET);
	else lseek(split.fd, chunk*fork_num, SEEK_SET);

        //Define fd out names; i.e. mr-0.itm, mr-1.itm, etc...
        int num_len = snprintf( NULL, 0, "%d", fork_num );
        char* fork_num_str = malloc( num_len + 1 );
        snprintf( fork_num_str, num_len + 1, "%d", fork_num );
        char * fd_out_name = malloc(num_len + 8);
        memcpy(fd_out_name, "mr-", 3);
        memcpy(fd_out_name + 3, fork_num_str, num_len);
        memcpy(fd_out_name + 3 + num_len, ".itm", 5);

        int fd_out = open(fd_out_name, O_RDWR | O_CREAT | O_TRUNC);
	chmod(fd_out_name, S_IRWXU|S_IRGRP|S_IXGRP|S_IROTH);

        if (letter_counter) letter_counter_map(&split, fd_out);
        else word_finder_map(&split, fd_out);

        free(fd_out_name);
        free(fork_num_str);
        close(split.fd);
        close(fd_out);

	if (fork_num) {
	    close(pipes_fd[fork_num][0]);
	    write(pipes_fd[fork_num][1], "gg", 2);
            _exit(0);
	}

	//Reducer is the only child process left...

	for (int i = 1; i < spec->split_num; i++) {
	    close(pipes_fd[i][1]);
	    read(pipes_fd[i][0], buf, 2);
	}

	char * fd_in_name = NULL;
	int * p_fd_in = malloc(sizeof(int) * spec->split_num);

	for(int i = 0; i < spec->split_num; i++) {
            num_len = snprintf( NULL, 0, "%d", i );
            fork_num_str = malloc( num_len + 1 );
            snprintf( fork_num_str, num_len + 1, "%d", i );
            fd_in_name = malloc(num_len + 8);
            memcpy(fd_in_name, "mr-", 3);
            memcpy(fd_in_name + 3, fork_num_str, num_len);
            memcpy(fd_in_name + 3 + num_len, ".itm", 5);

            p_fd_in[i] = open(fd_in_name, O_RDWR);
	}
        
	fd_out = open("mr.rst", O_RDWR | O_CREAT | O_TRUNC);
	chmod("mr.rst", S_IRWXU|S_IRGRP|S_IXGRP|S_IROTH);

	if (letter_counter) letter_counter_reduce(p_fd_in, spec->split_num, fd_out);
	else word_finder_reduce(p_fd_in, spec->split_num, fd_out);

	for(int i = 0; i < spec->split_num; i++) close(p_fd_in[i]);
        _exit(0);
    }

    gettimeofday(&end, NULL);   

    result->processing_time = (end.tv_sec - start.tv_sec) * US_PER_SEC + (end.tv_usec - start.tv_usec);
}
