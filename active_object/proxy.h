#ifndef _PROXY_H
#define _PROXY_H
/*
 * File: proxy.h
 * Author: Charles, Liu.
 * Mailto: charlesliu.cn.bj@gmail.com
 */
#include "servant.h"
#include "method_request.h"
#include "message.h"
#include "message_future.h"
#include "scheduler.h"
#include "producer.h"
#include "consumer.h"

class Proxy {
public:
    enum { MAX_SIZE = 1000 };
    Proxy(size_t size = MAX_SIZE) {
        scheduler_ = new Scheduler(size);
        servant_ = new Servant(size);
        scheduler_->run();
    }
    ~Proxy() {
        delete scheduler_;
        delete servant_;
    }
    void produce(Message &msg) {
        MethodRequest *method_request = new Producer(servant_, msg);
        scheduler_->enqueue(method_request);
    }
    MessageFuture * consume() {
        MessageFuture *result = new MessageFuture;
        MethodRequest *method_request = new Consumer(servant_, result);
        scheduler_->enqueue(method_request);
        return result;
    }
private:
    Servant *servant_;
    Scheduler *scheduler_;
};


#endif
