#ifndef _SCHEDULER_H
#define _SCHEDULER_H
/*
 * File: scheduler.h
 * Description: type definition for class Scheduler
 * Author: Charles, Liu.
 * Mailto: charlesliu.cn.bj@gmail.com
 */
#include "activation_queue.h"
#include "method_request.h"
#include <pthread.h>

void* dispatch(void *arg);

class Scheduler {
public:
    Scheduler(size_t high_water_mark) {
        act_queue_ = new ActivationQueue(high_water_mark);
        svr_run = ::dispatch;
    }
    ~Scheduler() {
        delete act_queue_;
    }
    void enqueue(MethodRequest *method_request) {
        act_queue_->enqueue(method_request);
    }
    void run() {
        pthread_t thread_id;
        pthread_attr_t thread_attr;
        pthread_attr_init(&thread_attr);
        pthread_attr_setdetachstate(&thread_attr, PTHREAD_CREATE_DETACHED);
        pthread_create(&thread_id, &thread_attr, svr_run, this);
        pthread_attr_destroy(&thread_attr);
    }
    void dispatch() {
        ACTIVATION_QUEUE mark_delete;
        for (;;) {
            int count = act_queue_->size();
            for (int i = 0; i < count; ++i) {
                MethodRequest *method_request = act_queue_->at(i);
                if (method_request == NULL)
                    printf("method request is NULL\n");
                if (method_request->guard()) {
                    mark_delete.push_back(method_request);
                    method_request->call();
                }
            }
            for (ACTIVATION_QUEUE_ITERATOR iter = mark_delete.begin(); iter != mark_delete.end(); ++iter) {
                act_queue_->dequeue(*iter);
            }
        }
    }
private:
    ActivationQueue *act_queue_;
    void *(*svr_run)(void *);
};

void* dispatch(void *arg) {
    Scheduler *this_obj = (Scheduler *)arg;
    this_obj->dispatch();
}

#endif
