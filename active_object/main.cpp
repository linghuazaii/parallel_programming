/* This file is auto-generated.Edit it at your own peril.*/
#include <stdio.h>
#include <unistd.h>
#include "proxy.h"
#include <pthread.h>
#include <time.h>

Proxy *proxy = NULL;

void *producer_routine(void *arg) {
    printf("Producer Routine\n");
    char msg_buffer[256];
    for (int i = 0; i < 10; ++i) {
        sleep(1);
        sprintf(msg_buffer, "I am Producer (time => %ld)\n", time(0));
        Message msg = Message(msg_buffer);
        proxy->produce(msg);
    }

    return NULL;
}

void *consumer_routine(void *arg) {
    printf("Consumer Routine\n");
    while (true) {
        MessageFuture *result = proxy->consume();
        sleep(1); // wait future has result
        if (result->hasMessage()) {
            Message msg = result->getMessage();
            printf("Consume Message => %s", msg.c_str());
        }
    }

    return NULL;
}

int main(int argc, char **argv) {
    proxy = new Proxy();

    pthread_t producer1, producer2, consumer;
    pthread_create(&producer1, NULL, producer_routine, NULL);
    pthread_create(&producer2, NULL, producer_routine, NULL);
    pthread_create(&consumer, NULL, consumer_routine, NULL);
    
    pthread_join(producer1, NULL);
    pthread_join(producer2, NULL);
    pthread_join(consumer, NULL);

    delete proxy;

    return 0;
}

