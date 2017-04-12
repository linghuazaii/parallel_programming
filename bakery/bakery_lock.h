#ifndef _BAKERY_LOCK_H
#define _BAKERY_LOCK_H
/*
 * File: bakery_lock.h
 * Description: bakery lock implementation
 * Author: Charles, Liu.
 * Mailto: charlesliu.cn.bj@gmail.com
 */
#include <sched.h>
#include <pthread.h>

#define MAX_LOCK 64

typedef struct {
    bool entering[MAX_LOCK];
    int priority[MAX_LOCK];
    pthread_t thread_id[MAX_LOCK];
} bakery_lock_t;

typedef struct {
    pthread_t thread_id;
    int priority;
} bakery_pair;

int bakery_compare(bakery_pair &lh, bakery_pair &rh) {
    if (lh.thread_id < rh.thread_id)
        return -1;
    else if (lh.thread_id > rh.thread_id)
        return 1;
    else {
        if (lh.priority < rh.priority)
            return 1;
        else if (lh.priority > rh.priority)
            return -1;
        else 
            return 0;
    }
}

int max_priority(int *priority, int count) {
    int max = 0;
    for (int i = 0; i < count; ++i)
        if (max < priority[i])
            max = priority[i];

    return max;
}

void bakery_lock_init(bakery_lock_t &lock) {
    for (int i = 0; i < MAX_LOCK; ++i) {
        lock.entering[i] = false;
        lock.priority[i] = 0;
        lock.thread_id[i] = 0;
    }
}

void bakery_lock(bakery_lock_t &lock, int id) {
    lock.entering[id] = true;
    lock.priority[id] = max_priority(lock.priority, MAX_LOCK) + 1;
    lock.thread_id[id] = pthread_self();
    lock.entering[id] = false;
    for (int i = 0; i < MAX_LOCK; ++i) {
        while (lock.entering[i])
            sched_yield();
        bakery_pair lh, rh;
        lh.thread_id = lock.thread_id[i];
        lh.priority = lock.priority[i];
        rh.thread_id = lock.thread_id[id];
        rh.priority = lock.priority[id];
        asm volatile("mfence":::"memory");
        while (lock.priority[i] != 0 && bakery_compare(lh, rh) == -1)
            sched_yield();
    }
}

void bakery_unlock(bakery_lock_t &lock, int id) {
    lock.priority[id] = 0;
}

#endif
