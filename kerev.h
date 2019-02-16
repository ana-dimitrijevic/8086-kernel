#ifndef _KEREV_H_
#define _KEREV_H_

#include "event.h"

class PCB;

class KernelEv {
public:
    KernelEv();
    ~KernelEv();
    void wait();
    void signal();

private:
    PCB* owner;
    volatile int val;
};

#endif
