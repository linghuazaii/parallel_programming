#ifndef _SERVANT_H
#define _SERVANT_H
/*
 * File: servant.h
 * Author: Charles, Liu.
 * Mailto: charlesliu.cn.bj@gmain.com
 */
#include <queue>
using std::queue;

class Servant {
public:
    Servant(size_t mq_size) : size(mq_size) {}
    void produce(const Message &msg) {
        mq.push_back(msg);
    }
    Message consume() {
        Message msg = mq.front();
        mq.pop_front();
        return msg;
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
