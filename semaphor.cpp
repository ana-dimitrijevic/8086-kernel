#include "semaphor.h"
#include "kersem.h"
#include "pcb.h"


Semaphore::Semaphore(int initialValue) {

	SOFT_LOCK
	myImpl = new KernelSem(initialValue);
	SOFT_UNLOCK

}

Semaphore::~Semaphore() {

	SOFT_LOCK
	if(myImpl!=0){
	delete myImpl;
	myImpl = 0;
	}
	SOFT_UNLOCK

}

void Semaphore::signal() {

	 HARD_LOCK
		myImpl->signal();
	 HARD_UNLOCK

}

int Semaphore::wait (int toBlock) {

	HARD_LOCK
		int ret = myImpl->wait(toBlock);
	 HARD_UNLOCK
		return ret;

}


int Semaphore::val () const {

	 HARD_LOCK
		int ret = myImpl->getSemaphoreValue();
	 HARD_UNLOCK
		return ret;
}

