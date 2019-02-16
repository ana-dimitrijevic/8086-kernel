#include "thread.h"
#include "pcb.h"

Thread::Thread(StackSize stackSize, Time timeSlice) {

	if (stackSize > maxStackSize)
		stackSize = maxStackSize;
	if (stackSize < 0)
		stackSize = defaultStackSize;
	if (timeSlice < 0)
		timeSlice = defaultTimeSlice;

	SOFT_LOCK
	myPCB = new PCB(this, stackSize, timeSlice);
	SOFT_UNLOCK
}

Thread::~Thread() {
	waitToComplete();
	SOFT_LOCK
	if (myPCB) {
		delete myPCB;
		myPCB = 0;
	}
	SOFT_UNLOCK
}

void Thread::start() {
	myPCB->start();
}

void Thread::waitToComplete() {
	myPCB->waitToComplete();
}

void Thread::sleep(Time timeToSleep) {
	PCB::sleep(timeToSleep);
}

PCB* Thread::getMyPCB() {
	return myPCB;
}

