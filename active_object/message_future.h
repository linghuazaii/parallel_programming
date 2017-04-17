#ifndef _MESSAGE_FUTURE_H
#define _MESSAGE_FUTURE_H
/*
 * File: message_future.h
 * Description: type definition for class MessageFuture
 * Autor: Charles, Liu.
 * Mailto: charlesliu.cn.bj@gmail.com
 */
#include "message.h"

class MessageFuture {
public:
    MessageFuture() : has_message(false) {}
    ~MessageFuture() {}
    bool hasMessage() { 
        return has_message;
    }
    Message getMessage() {
        return msg_;
    }
    void setMessage(Message &msg) {
        msg_ = msg;
        has_message = true;
    }
private:
    Message msg_;
    bool has_message;
};

#endif
