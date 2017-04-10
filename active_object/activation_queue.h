#ifndef _ACTIVATION_QUEUE_H
#define _ACTIVATION_QUEUE_H
/*
 * File: activation_queue.h
 * Author: Charles, Liu.
 * Mailto: charlesliu.cn.bj@gmai.com
 */
#include <queue>
#include "method_request.h"
#include "lock.h"
using std::queue;

class ActivationQueue {
public:
    const int INFINITE = -1;
    ActivationQueue(size_t high_water_mark) {
        size = high_water_mark;
    }
    ~ActivationQueue() {
    }
    void enqueue(MethodRequest *method_request, long msec_timeout = INFINITE) {
        int ret = 0;
        if (msec_timeout == INFINITE)
            lock.lock();
        else
            ret = lock.timedlock(msec_timeout);

        if (ret == 0) {
            act_queue_.push_back(method_request);  
        }

        lock.unlock();
    }
    void dequeue(Method_request *method_request, long msec_timeout = INFINITE) {
    
    }
private:
    queue<MethodRequest *> act_queue_;
    size_t size;
    Lock lock;
};

#endif
