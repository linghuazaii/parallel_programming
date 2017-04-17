#ifndef _ACTIVATION_QUEUE_H
#define _ACTIVATION_QUEUE_H
/*
 * File: activation_queue.h
 * Author: Charles, Liu.
 * Mailto: charlesliu.cn.bj@gmai.com
 */
#include <vector>
#include <algorithm>
#include "method_request.h"
#include "lock.h"
using std::vector;

typedef vector<MethodRequest *> ACTIVATION_QUEUE;
typedef vector<MethodRequest *>::iterator ACTIVATION_QUEUE_ITERATOR;

class ActivationQueue {
public:
    enum {INFINITE = -1};
    ActivationQueue(size_t high_water_mark) {
        high_water_mark_ = high_water_mark;
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
            if (act_queue_.size() < high_water_mark_)
                act_queue_.push_back(method_request);  
        }

        lock.unlock();
    }
    void dequeue(MethodRequest *method_request, long msec_timeout = INFINITE) {
        int ret = 0;
        if (msec_timeout = INFINITE)
            lock.lock();
        else
            ret = lock.timedlock(msec_timeout);

        if (ret == 0) {
            ACTIVATION_QUEUE_ITERATOR iter = find(act_queue_.begin(), act_queue_.end(), method_request);
            if (iter != act_queue_.end())
                act_queue_.erase(iter);
        }

        lock.unlock();
    }
    int size() {
        int count = 0;
        lock.lock();
        count = act_queue_.size();
        lock.unlock();
        return count;
    }
    MethodRequest *at(size_t i) {
        MethodRequest *method_request;
        lock.lock();
        method_request = act_queue_.at(i);
        lock.unlock();
        return method_request;
    }
private:
    vector<MethodRequest *> act_queue_;
    size_t high_water_mark_;
    Lock lock;
};

#endif
