#ifndef _METHOD_REQUEST_H
#define _METHOD_REQUEST_H
/*
 * File: method_request.h
 * Author: Charles, Liu.
 * Mailto: charlesliu.cn.bj@gmail.com
 */

class MethodRequest {
public:
    virtual bool guard() = 0;
    virtual void call() = 0;
};

#endif
