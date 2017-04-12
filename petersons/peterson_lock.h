#ifndef _PETERSON_LOCK_H
#define _PETERSON_LOCK_H
/*
 * Description: implementing peterson's locking algorithm
 * File: peterson_lock.h
 * Author: Charles, Liu.
 * Mailto: charlesliu.cn.bj@gmail.com
 */
#include <pthread.h>

typedef struct {
    bool flag[2];
    bool victim;
} peterson_lock_t;

void peterson_lock_init(peterson_lock_t &lock) {
    lock.flag[0] = lock.flag[1] = false;
    lock.victim = 0;
}

void peterson_lock(peterson_lock_t &lock, int id) {
    lock.victim = id;
    lock.flag[id] = true;
    asm volatile ("mfence" : : : "memory");
    while (lock.flag[1 - id] == false && lock.victim != id);
}

void peterson_unlock(peterson_lock_t &lock, int id) {
    lock.flag[id] = false;
    lock.victim = id;
}

#endif
