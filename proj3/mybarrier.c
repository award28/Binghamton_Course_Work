#include "mybarrier.h"
#include <stdlib.h>
#include <stdio.h>


mybarrier_t * mybarrier_init(unsigned int count)
{
    mybarrier_t * barrier = malloc(sizeof(*barrier));
    if (NULL == barrier) return NULL;
	
    barrier->count = count;

    //init mutex
    pthread_mutexattr_t mutex_attr;
    pthread_mutexattr_init(&mutex_attr);
    pthread_mutex_init(&barrier->mutex, &mutex_attr);

    //init cond
    pthread_condattr_t cond_attr;
    pthread_condattr_init(&cond_attr);
    pthread_cond_init(&barrier->cond, &cond_attr);

    //destroy startup attr variables
    pthread_mutexattr_destroy(&mutex_attr);
    pthread_condattr_destroy(&cond_attr);

    return barrier;	
}

int mybarrier_destroy(mybarrier_t * barrier)
{
	if (NULL == barrier) return -1;
	int ret = 0;
	
	pthread_mutex_lock(&barrier->mutex);

	//wait for barrier to finish being used
	while (barrier->count > 0) 
		ret = pthread_cond_wait(&barrier->cond, &barrier->mutex);
	pthread_mutex_unlock(&barrier->mutex);
	pthread_cond_broadcast(&barrier->cond);

	//destroy my barrier variables and free
	pthread_cond_destroy(&barrier->cond);
	pthread_mutex_destroy(&barrier->mutex);
	free(barrier);
	
	return ret;
}

int mybarrier_wait(mybarrier_t * barrier)
{
	if (NULL == barrier || barrier->count < 0) return -1;
	int ret = 0;
	
	pthread_mutex_lock(&barrier->mutex);
	barrier->count -= barrier->count > -1;
	if (barrier->count == 0) ret = pthread_cond_broadcast(&barrier->cond);
	else {
	    while (barrier->count > 0) 
		    ret = pthread_cond_wait(&barrier->cond, &barrier->mutex);
	    pthread_cond_broadcast(&barrier->cond);
	}
	pthread_mutex_unlock(&barrier->mutex);
	
	return ret;
}


