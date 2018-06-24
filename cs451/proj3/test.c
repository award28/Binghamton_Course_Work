#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "mybarrier.h"

void *test_thread(void *args) {
    mybarrier_t *barrier = (mybarrier_t *)args;
    printf("Start\n");
    sleep(rand() % 7);
    printf("Wait\n");
    mybarrier_wait(barrier);
    printf("Exit\n");
    pthread_exit(NULL);
    return NULL;
}

int main(int argc, char * argv[]) 
{
    if (argc != 2) return 1;
    int NUM_THREADS = atoi(argv[1]);

    pthread_t threads[NUM_THREADS];
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    mybarrier_t *barrier = mybarrier_init(NUM_THREADS);

    srand(time(NULL));

    for (int i = 0; i < NUM_THREADS; i++) 
        pthread_create(&threads[i], &attr, test_thread, barrier);

    pthread_attr_destroy(&attr);
    mybarrier_destroy(barrier);

    for (int i = 0; i < NUM_THREADS; i++) 
        pthread_join(threads[i], NULL);
}
