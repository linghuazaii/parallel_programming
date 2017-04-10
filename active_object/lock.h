#ifndef _TIMEOUT_LOCK_H
#define _TIMEOUT_LOCK_H
/*
 * Description: lock with timeout
 * File: lock.h
 * Author: Charles, Liu.
 * Mailto: charlesliu.cn.bj@gmail.com
 */
#include <pthread.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

class Lock {
public:
    Lock() {
        pthread_mutex_init(&mutex_, NULL);
        timeout = false;
    }
    void lock() {
        timeout = false;
        pthread_mutex_lock(&mutex_);
    }
    int timedlock(int ms_timeout) {
        struct timespec now;
        clock_gettime(CLOCK_REALTIME, &now);
        now.tv_nsec += ms_timeout * 1000000;
        if (now.tv_nsec >= 1000000000) {
            now.tv_sec += now.tv_nsec / 1000000000;
            now.tv_nsec %= 1000000000;
        }
        int ret = pthread_mutex_timedlock(&mutex_, &now);
        if (ret == ETIMEDOUT) {
            timeout = true;
            return 1;
        } else if (ret == 0) {
            timeout = false;
            return 0;
        } else {
            timeout = true;
            fprintf(stderr, "error in pthread_mutex_timedlock() (%s)\n", strerror(ret));
            return -1;
        }
    }
    void unlock() {
        if (timeout == false)
            pthread_mutex_unlock(&mutex_);
    }
    ~Lock() {
        pthread_mutex_destroy(&mutex_);
    }
private:
    pthread_mutex_t mutex_;
    bool timeout;
};

#endif 
