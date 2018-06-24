/* Task: using thread-specific data to implment a thread-safe version of mygetenv() */

#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>


#define MAXSTRINGSZ 4096

extern char **environ;

static char buf[MAXSTRINGSZ];

pthread_mutex_t lock;

char * mygetenv(const char *name)
{
    int  i, len;

    len = strlen(name);
    for (i = 0; environ[i] != NULL; i++) 
	{
        if ((strncmp(name, environ[i], len) == 0) && (environ[i][len] == '=')) 
		{
	    pthread_mutex_lock(&lock);
            strncpy(buf, &environ[i][len+1], MAXSTRINGSZ-1);
			buf[MAXSTRINGSZ-1] = '\0';
	    pthread_mutex_unlock(&lock);
            return buf;
		} 
	}
	
	return NULL;
}
