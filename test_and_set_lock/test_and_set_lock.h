#ifndef _TEST_AND_SET_LOCK_H
#define _TEST_AND_SET_LOCK_H
/*
 * File: test_and_set_lock.h
 * Description: spin lock use atomic test and set
 * Author: Charles, Liu.
 * Mailto: charlesliu.cn.bj@gmail.com
 */
#include <sched.h>

typedef bool spin_lock;

bool test_and_set(spin_lock &lock) {
    return __sync_bool_compare_and_swap(&lock, false, true);
}

void lock_init(spin_lock &lock) {
    lock = false;
}

void lock(spin_lock &lock) {
    while (!test_and_set(lock))
        sched_yield();
}

void unlock(spin_lock &lock) {
    __sync_bool_compare_and_swap(&lock, true, false);
}

#endif
