/* This file is auto-generated.Edit it at your own peril.*/
#include <iostream>
#include <string>
#include <stdio.h>
#include <cstring>
#include <unistd.h>
#include <cstdlib>
#include <vector>
#include <set>
#include <map>
#include <termios.h>
#include <inttypes.h>
#include <errno.h>
#include <algorithm>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/uio.h>
#include <sys/mman.h>
#include <sched.h>
#include <malloc.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>
#include "lock.h"
#include <pthread.h>
using namespace std;

Lock lock;

void *routine(void *arg) {
    int ret = lock.timedlock(999);
    if (ret == 1)
        cout<< "timeout" <<endl;
    else if (ret == 0)
        cout<<"locked"<<endl;
    else
        cout<<"error"<<endl;
    lock.unlock();

    return NULL;
}

int main(int argc, char **argv) {
    lock.lock();
    pthread_t thread;
    pthread_create(&thread, NULL, routine, NULL);
    sleep(1);
    lock.unlock();

    pthread_join(thread, NULL);

    return 0;
}

