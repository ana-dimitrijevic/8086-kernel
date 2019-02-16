#include "event.h"
#include "kerev.h"
#include "pcb.h"
#include <dos.h>

Event::Event(IVTNo ivtNo) {
	SOFT_LOCK
    myImpl = new KernelEv();
    IVTEntry::addEntry(ivtNo, this);
    SOFT_UNLOCK
}

Event::~Event() {
	SOFT_LOCK
	if (myImpl!=0){
    delete myImpl;
    myImpl=0;
	}
    SOFT_UNLOCK
}

void Event::wait(){
    myImpl->wait();
}

void Event::signal() {
    myImpl->signal();
}



