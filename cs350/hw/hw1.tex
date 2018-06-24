#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <assert.h>

int buffer;
int count = 0; // initially, empty

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

/* arg is the loop */
void *producer(void *arg) {
    int i;
    int loops = *(int *) arg;
    for (i = 0; i < loops; i++) {
        put(i);
    }
    return 0;
}

void *consumer(void *arg) {
    int i;
    while (1) {
        int tmp = get();
        printf("%d\n", tmp);
    }
    return 0;
}

int main(int argc, char *argv[]) {
    printf("parent: begin\n");
    pthread_t c;
    pthread_t p;
    int loop = 10;
    pthread_create(&c, NULL, consumer, &loop); // create child
    pthread_create(&p, NULL, producer, &loop); // create child

    pthread_join(c, NULL);
    pthread_join(p, NULL);
    printf("parent: end\n");
    return 0;
}
