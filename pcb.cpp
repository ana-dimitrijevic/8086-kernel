#include "pcb.h"
#include "SCHEDULE.H"
#include "system.h"
#include "list.h"
#include "timeq.h"
#include <dos.h>

ID PCB::idGenerator;
PCB* PCB::running;
PCB* PCB::idle;
//List* PCB::allThreads;

PCB::PCB() {

	id = PCB::idGenerator++;
	stack = 0;
	sp = 0;
	ss = 0;
	bp = 0;
	myThread = 0;
	timeSlice = defaultTimeSlice;
	state = READY;
	blockedOnThisThread = new List();
	//allThreads.insert(this);

}

PCB::PCB(Thread *thread, StackSize stackSize, Time timeSlice) :
id(PCB::idGenerator++),state(
		CREATED), myThread(thread), timeSlice(timeSlice), bp(0) {

#ifndef BCC_BLOCK_IGNORE
	stackSize /= 2;
	stack = new unsigned [stackSize];
	stack[stackSize - 1] = 0x0200;
	stack[stackSize - 2] = FP_SEG(PCB::wrapper);
	stack[stackSize - 3] = FP_OFF(PCB::wrapper);

	ss = FP_SEG(stack + (stackSize - 12));
	sp = FP_OFF(stack + (stackSize - 12));

	blockedOnThisThread = new List();

#endif
	//allThreads.insert(this);
}

PCB::~PCB() {

	//allThreads.remove(this);

	if (blockedOnThisThread)
		delete blockedOnThisThread;
	blockedOnThisThread = 0;

	if (stack)
		delete[] stack;
	stack = 0;

	

}

void PCB::start() {
	SOFT_LOCK
	if (state == CREATED) {
		state = READY;
		Scheduler::put(this);
	}
	SOFT_UNLOCK
}

void PCB::waitToComplete() {
	if ((state == COMPLETED) || (state == CREATED) || (this == PCB::idle)
			|| (this == PCB::running))
		return;
	SOFT_LOCK
	PCB::running->state = BLOCKED;
	blockedOnThisThread->insert(PCB::running);
	SOFT_UNLOCK
	dispatch();
}

void PCB::sleep(Time timeToSleep) {

	SOFT_LOCK
	PCB::running->state = BLOCKED;
	System::sleepingThreads->insert(PCB::running, timeToSleep);
	SOFT_UNLOCK

	dispatch();

}

ID PCB::getID() {
	return id;
}

void PCB::wrapper() {

	PCB::running->myThread->run();

	SOFT_LOCK

	List* blockedOnRunningThread = PCB::running->blockedOnThisThread;
	PCB* curr = blockedOnRunningThread->removeFirst();

	while (curr) {
		curr->state = READY;
		Scheduler::put(curr);
		curr = blockedOnRunningThread->removeFirst();
	}

	PCB::running->state = COMPLETED;

	SOFT_UNLOCK

	dispatch();
}

void dispatch() {
	if (preemptionDisabled)
		return;
	HARD_LOCK
	dispatchRequested = 1;
	explicitTimerCall = 1;
	System::timer();
	HARD_UNLOCK

}

