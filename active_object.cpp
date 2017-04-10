/*
 * Active Object
 */

class Servant {
public:
    Servant(size_t mq_size);
    void put(const Message &msg);
    Message get(void);
    bool empty();
    bool full();
private:
    /*
     * Internal Queue
     */
};

class Proxy {
public:
    enum {MAX_SIZE = 100};
    Proxy(size_t size = MAX_SIZE) : scheduler_(new Scheduler(size)), servant_(new Servant(size)){}

    void put(const Message &msg) {
        MethodRequest *method_request = new Put(servant_, msg);
        scheduler_enqueue(method_request);
    }

    MessageFuture get(void) {
        MessageFuture result;
        MethodRequest *method_request = new Get(Servant_, result);
        scheduler_->enqueue(method_request);
        return result;
    }
protected:
    Servant *servant_;
    Scheduler *scheduler_;
};

class MethodRequest {
public:
    virtual bool guard(void) const = 0;
    virtual bool call(void) const = 0;
};

class Put : public MethodRequest {
public:
    Put(Servant *rep, Message msg) : servant_(rep), msg_(msg) {}
    virtual bool guard(void) const {
        return !servant_->full();
    }
    virtual void call(void) {
        servant_->put(msg_);
    }
private:
    Servant *servant_;
    Message msg_;
};

class Get : public MethodRequest {
public:
    Get(Servant *rep, const MessageFuture &future) : servant_(rep), result_(future) {}
    virtual bool guard(void) const {
        return !servant_->empty();
    }
    virtual void call(void) {
        result_ = servant_->get();
    }
private:
    Servant *servant_;
    MessageFuture result_;
};

class ActivationQueue {
public:
    const int INFINITE = -1;
    typedef ActivationQueueIterator iterator;
    ActivationQueue(size_t high_water_mark);
    void enqueue(MethodRequest *method_request, long msec_timeout = INFINITE);
    void dequeue(MethodRequest *method_request, long msec_timeout = INFINITE);
private:
    /*
     * Synchronization mechanisms, condition variables and mutexes, and the 
     * queue implementation, e.g. an array or a linked list
     */
};

class Scheduler {
public:
    Scheduler(size_t high_water_mark) : act_queue(new ActivationQueue(high_water_mark)) {
        ThreadManager::instance()->spawn(svc_run, this);
    }
    void enqueue(MethodRequest *method_request) {
        act_queue->enqueue(method_request);
    }
    virtual void dispatch(void);
protected:
    ActivationQueue *act_queue_;
    static void *svc_run(void *args);
};

void * Scheduler::svc_run(void *args) {
    Scheduler *this_obj = reinterpret_cast<Scheduler *>(args);
    this_obj->dispatch();
}

void Scheduler::dispatch(void) {
    for (;;) {
        ActivationQueue::iterator iter;
        for (iter = act_queue_->begin(); iter != act_queue_->end(); ++iter) {
            MethodRequest *mr = *iter;
            if (mr->guard()) {
                act_queue_->dequeue(mr);
                mr->call();
                delete mr;
            }
        }
    }
}

class MessageFuture {
public:
    MessageFuture(const MessageFuture &f);
    MessageFuture(const Meesage &msg);
    void operator=(const MessageFuture &f);
    operator Message();
};

/*
 * Immediate evaluation
 */
Proxy mq;
Message msg = mq.get();
send(msg);

/*
 * Deferred evaluation
 */
MessageFuture future = mq.get();
Message msg = Message(future);


