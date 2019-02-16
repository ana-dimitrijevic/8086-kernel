#include "kersem.h"
#include "pcb.h"
#include "list.h"
#include "SCHEDULE.H"

KernelSem::KernelSem(int initialValue) {
	val = initialValue;
	blockedOnThisSemaphore = new List();
}

KernelSem::~KernelSem() {

	if (blockedOnThisSemaphore != 0) {
		delete blockedOnThisSemaphore;
		blockedOnThisSemaphore = 0;
	}
}

void KernelSem::signal() {

	if (val++ < 0)
		deblock();

}

int KernelSem::wait(int toBlock) {

	int ret = 0;

	if (!toBlock && val <= 0)
		ret = -1;
	else if (--val < 0) {
		ret = 1;
		block();

	}

	return ret;
}



int KernelSem::getSemaphoreValue() const {
	return val;
}

void KernelSem::block() {
	PCB::running->state = BLOCKED;
	blockedOnThisSemaphore->insert(PCB::running);
	dispatch();
}

void KernelSem::deblock() {
	PCB* toDeblock = blockedOnThisSemaphore->removeFirst();
	if (toDeblock) {
		toDeblock->state = READY;
		Scheduler::put(toDeblock);
	}
}

