#include <stdio.h>
#include "test_and_set_lock.h"
#include <pthread.h>

spin_lock mlock;
int count = 0;

void *routine0(void *arg) {
    int *cnt = (int *)arg;
    for (int i = 0; i < *cnt; ++i) {
        lock(mlock);
        ++count;
        unlock(mlock);
    }

    return NULL;
}

void *routine1(void *arg) {
    int *cnt = (int *)arg;
    for (int i = 0; i < *cnt; ++i) {
        lock(mlock);
        ++count;
        unlock(mlock);
    }
}

int main(int argc, char **argv) {
    lock_init(mlock);
    pthread_t thread0, thread1, thread2;
    int count0 = 10000;
    int count1 = 20000;
    int count2 = 30000;
    pthread_create(&thread0, NULL, routine0, (void *)&count0);
    pthread_create(&thread1, NULL, routine1, (void *)&count1);
    pthread_create(&thread2, NULL, routine1, (void *)&count2);
    
    pthread_join(thread0, NULL);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Expected: %d\n", (count0 + count1 + count2));
    printf("Reality : %d\n", count);

    return 0;
}
