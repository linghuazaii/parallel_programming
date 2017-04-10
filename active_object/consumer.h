#ifndef _CONSUMER_H
#define _CONSUMER_H
/*
 * File: consumer.h
 * Author: Charles, Liu.
 * Mailto: charlesli.cn.bj@gmail.com
 */
#include "servant.h"
#include "method_request.h"

class Consumer : public MethodRequest {
public:
    Consumer(Servant *servant, Message &msg) {
        servant_ = servant;
        msg_ = msg;
    }
    virtual bool guard() {
        return !servant_->empty();
    }
    virtual void call() {
        result_ = servant_->consume();
    }
private:
    Servant *servant_;
    MessageFuture result_;
};

#endif
