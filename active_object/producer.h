#ifndef _PRODUCER_H
#define _PRODUCER_H
/*
 * File: producer.h
 * Author: Charles, Liu.
 * Mailto: charlesliu.cn.bj@gmail.com
 */
#include "servant.h"
#include "method_request.h"
#include "message.h"

class Producer : public MethodRequest {
public:
    Producer(Servant *servant, Message &msg) {
        servant_ = servant;
        msg_ = msg;
    }
    virtual bool guard() {
        return !servant_->full();
    }
    virtual void call() {
        servant_->produce(msg_);
    }
private:
    Servant *servant_;
    Message msg_;
};

#endif
