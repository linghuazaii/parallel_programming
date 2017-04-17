#ifndef _CONSUMER_H
#define _CONSUMER_H
/*
 * File: consumer.h
 * Author: Charles, Liu.
 * Mailto: charlesli.cn.bj@gmail.com
 */
#include "servant.h"
#include "method_request.h"
#include "message.h"
#include "message_future.h"

class Consumer : public MethodRequest {
public:
    Consumer(Servant *servant, MessageFuture *future) {
        servant_ = servant;
        future_ = future;
    }
    virtual bool guard() {
        return !servant_->empty();
    }
    virtual void call() {
        servant_->consume(future_);
    }
private:
    Servant *servant_;
    MessageFuture *future_;
};

#endif
