#ifndef _THREAD_H_
#define _THREAD_H_

#include "defs.h"

class PCB;

class Thread {
public:

    virtual ~Thread();
    void start();
    void waitToComplete();
    static void sleep(Time);
    PCB* getMyPCB();

protected:

    friend class PCB;
    Thread(StackSize stackSize=defaultStackSize, Time time=defaultTimeSlice);
    virtual void run() {}

private:
    PCB *myPCB;
};

void dispatch();

#endif
