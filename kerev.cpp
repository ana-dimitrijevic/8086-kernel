#include "kerev.h"
#include "SCHEDULE.h"
#include "pcb.h"

KernelEv::KernelEv() {
    owner = PCB::running;
    val = 0;
}

KernelEv::~KernelEv() {
	 owner = 0;
	 val=0;
}

void KernelEv::wait() {

    if (PCB::running == owner) {

    HARD_LOCK
    if (--val < 0) {
        PCB::running->state = BLOCKED;
        HARD_UNLOCK
        dispatch();
        //...
        return;
    }
    HARD_UNLOCK
    }

}

void KernelEv::signal() {
	HARD_LOCK
    if (val < 0) {
        owner->state = READY;
        val = 0;
        Scheduler::put(owner);
    }
    else {
        val = 1;
    }
	HARD_UNLOCK

   dispatch();
}

