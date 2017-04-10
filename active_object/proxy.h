#ifndef _PROXY_H
#define _PROXY_H
/*
 * File: proxy.h
 * Author: Charles, Liu.
 * Mailto: charlesliu.cn.bj@gmail.com
 */
#include "servant.h"
#include "method_request.h"

class Proxy {
public:
    enum { MAX_SIZE = 1000 };
    Proxy(size_t size = MAX_SIZE) {
        scheduler_ = new Scheduler(size);
        servant_ = new Servant(size);
    }
    void produce(const Message &msg) {
        MethodRequest *method_request = new Producer(servant_, msg);
        scheduler_->enqueue(method_request);
    }
    void consume() {
        MessageFuture result;
        MethodRequest *method_request = new Consumer(servant_, result);
        scheduler_->enqueue(method_request);
        return result;
    }
private:
    Servant *servant_;
    Scheduler *scheduler_;
};


#endif
