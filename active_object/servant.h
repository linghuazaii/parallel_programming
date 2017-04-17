#ifndef _SERVANT_H
#define _SERVANT_H
/*
 * File: servant.h
 * Author: Charles, Liu.
 * Mailto: charlesliu.cn.bj@gmain.com
 */
#include <queue>
#include "message.h"
#include "message_future.h"
using std::queue;

class Servant {
public:
    Servant(size_t mq_size) : size(mq_size) {}
    void produce(const Message &msg) {
        mq.push(msg);
    }
    void consume(MessageFuture *future) {
        Message msg = mq.front();
        mq.pop();
        future->setMessage(msg);
    }
    bool empty() {
        return (mq.size() == 0);
    }
    bool full() {
        return (mq.size() == size);
    }
private:
    queue<Message> mq;
    size_t size;
};

#endif
