#include <stdio.h>
#include <pthread.h>
#include <assert.h>
#include <limits.h>

int buffer[INT_MAX];
int fill_ptr = 0;
int use_ptr = 0;
int count = 0; // initially, empty

pthread_cond_t  empty, fill;
pthread_mutex_t mutex;

void put(int value) {
    buffer[fill_ptr] = value;
    fill_ptr = (fill_ptr + 1) % INT_MAX;
    count++;
}

int get() {
    int tmp = buffer[fill_ptr];
    use_ptr = (fill_ptr + 1) % INT_MAX;
    count--;
    return tmp;
}

void *producer(void *arg) {
    int i;
    int loops = (int) arg;
    for (i = 0; i < loops; i++) {
        pthread_mutex_lock(&mutex);
        while(count == INT_MAX)
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
