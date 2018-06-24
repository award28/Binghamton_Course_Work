#include <stdio.h>
#include <pthread.h>
#include <assert.h>

int buffer;
int count = 0; // initially, empty

pthread_cond_t  empty, fill;
pthread_mutex_t mutex;

void put(int value) {
    assert(count == 0);
    count = 1;
    buffer = value;
}

int get() {
    assert(count == 1);
    count = 0;
    return buffer;
}

void *producer(void *arg) {
    int i;
    int loops = (int) arg;
    for (i = 0; i < loops; i++) {
        pthread_mutex_lock(&mutex);
        while(count == 1)
            pthread_cond_wait(&empty, &mutex);
        put(i);
        pthread_cond_signal(&fill);
        pthread_mutex_unlock(&mutex);
    }
    return 0;
}

void *consumer(void *arg) {
    int i;
    int loops = (int) arg;
    for (i = 0; i < loops; i++) {
        pthread_mutex_lock(&mutex);
        while(count == 0)
            pthread_cond_wait(&fill, &mutex);
        int tmp = get();
        pthread_cond_signal(&empty);
        pthread_mutex_unlock(&mutex);
        printf("%d\n", tmp);
    }
    return 0;
}

int main(int argc, char *argv[]) {
    printf("parent: begin\n");
    pthread_t c;
    pthread_t p;
    pthread_create(&c, NULL, consumer, NULL); // create child
    pthread_create(&p, NULL, producer, NULL); // create child
    pthread_join(c, NULL);
    pthread_join(p, NULL);    
    printf("parent: end\n");
    return 0;
}
