#include <stdio.h>
#include <pthread.h>
#include <assert.h>
#include <limits.h>

// how many bytes of the heap are free?
int bytesLeft = INT_MAX;
//need lock and condition too
pthread_cond_t  c;
pthread_mutex_t m;

void* allocate(int size) {
    pthread_mutex_lock(&m);
    while (bytesLeft < size)
        pthread_cond_wait(&c, &m);
    void *ptr = (void *) malloc(sizeof(void *)); // get mem from heap
    bytesLeft -= size;
    pthread_mutex_unlock(&m);
    return ptr;
}

void free(void *ptr, int size) {
    pthread_mutex_lock(&m);
    bytesLeft += size;
    pthread_cond_signal(&c); // whom to signal??
    pthread_mutex_unlock(&m);
}

int main(int argc, char *argv[]) {
    printf("parent: begin\n");
    pthread_t p;
    int i = 0;
    pthread_create(&p, NULL, allocate, &i);
    // how to wait for child? 
    pthread_join(p, NULL);
    printf("parent: end\n");
    return 0;
}
