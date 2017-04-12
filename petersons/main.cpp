#include <stdio.h>
#include "peterson_lock.h"

peterson_lock_t lock;
int count = 0;

void *routine0(void *arg) {
    int *cnt = (int *)arg;
    for (int i = 0; i < *cnt; ++i) {
        peterson_lock(lock, 0);
        ++count;
        peterson_unlock(lock, 0);
    }

    return NULL;
}

void *routine1(void *arg) {
    int *cnt = (int *)arg;
    for (int i = 0; i < *cnt; ++i) {
        peterson_lock(lock, 1);
        ++count;
        peterson_unlock(lock, 1);
    }
}

int main(int argc, char **argv) {
    peterson_lock_init(lock);
    pthread_t thread0, thread1;
    int count0 = 10000;
    int count1 = 20000;
    pthread_create(&thread0, NULL, routine0, (void *)&count0);
    pthread_create(&thread1, NULL, routine1, (void *)&count1);
    
    pthread_join(thread0, NULL);
    pthread_join(thread1, NULL);

    printf("Expected: %d\n", (count0 + count1));
    printf("Reality : %d\n", count);

    return 0;
}
