#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#include "common.h"
#include "usr_functions.h"

/* User-defined map function for the "Letter counter" task.  
   This map function is called in a map worker process.
   @param split: The data split that the map function is going to work on.
                 Note that the file offset of the file descripter split->fd should be set to the properly
                 position when this map function is called.
   @param fd_out: The file descriptor of the itermediate data file output by the map function.
   @ret: 0 on success, -1 on error.
 */
int letter_counter_map(DATA_SPLIT * split, int fd_out)
{
    int rv;
    int num_len;
    char* line = NULL;
    char * data = malloc(split->size + 1);
    int counter[26] = {0};

    rv = read(split->fd, data, split->size);
    if (rv < 0) {
	    free(data);
	    return rv;
    }
    for (int i = 0; i < split->size; i++) {
	    if (data[i] > 64 && data[i] < 91) 
		    counter[data[i] - 65]++;
	    else if (data[i] > 96 && data[i] < 123) 
		    counter[data[i] - 97]++;
    }

    for (int i = 0; i < 26; i++) {
    	num_len = snprintf( NULL, 0, "%d", counter[i] );
    	line = malloc( num_len + 4 );
    	snprintf( line, num_len + 4, "%c %d\n", i + 65, counter[i] );

	rv = write(fd_out, line, num_len + 3);
	free(line);

	if (rv < 0) { 
		free(data); 
		return rv; 
	}
    }

    free(data);
    return 0;
}

/* User-defined reduce function for the "Letter counter" task.  
   This reduce function is called in a reduce worker process.
   @param p_fd_in: The address of the buffer holding the intermediate data files' file descriptors.
                   The imtermeidate data files are output by the map worker processes, and they
                   are the input for the reduce worker process.
   @param fd_in_num: The number of the intermediate files.
   @param fd_out: The file descriptor of the final result file.
   @ret: 0 on success, -1 on error.
   @example: if fd_in_num == 3, then there are 3 intermediate files, whose file descriptor is 
             identified by p_fd_in[0], p_fd_in[1], and p_fd_in[2] respectively.

*/
int letter_counter_reduce(int * p_fd_in, int fd_in_num, int fd_out)
{
    // add your implementation here ...
    
    return 0;
}

/* User-defined map function for the "Word finder" task.  
   This map function is called in a map worker process.
   @param split: The data split that the map function is going to work on.
                 Note that the file offset of the file descripter split->fd should be set to the properly
                 position when this map function is called.
   @param fd_out: The file descriptor of the itermediate data file output by the map function.
   @ret: 0 on success, -1 on error.
 */
int word_finder_map(DATA_SPLIT * split, int fd_out)
{
    // add your implementation here ...
    
    return 0;
}

/* User-defined reduce function for the "Word finder" task.  
   This reduce function is called in a reduce worker process.
   @param p_fd_in: The address of the buffer holding the intermediate data files' file descriptors.
                   The imtermeidate data files are output by the map worker processes, and they
                   are the input for the reduce worker process.
   @param fd_in_num: The number of the intermediate files.
   @param fd_out: The file descriptor of the final result file.
   @ret: 0 on success, -1 on error.
   @example: if fd_in_num == 3, then there are 3 intermediate files, whose file descriptor is 
             identified by p_fd_in[0], p_fd_in[1], and p_fd_in[2] respectively.

*/
int word_finder_reduce(int * p_fd_in, int fd_in_num, int fd_out)
{
    // add your implementation here ...
    
    return 0;
}


