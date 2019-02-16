#include"system.h"
#include "SCHEDULE.h"
#include "timeq.h"
#include "idle.h"
#include<dos.h>

void tick();

TimeQueue* System::sleepingThreads = new TimeQueue();

volatile char dispatchRequested;
volatile char explicitTimerCall;
volatile unsigned preemptionDisabled;

static volatile int cnt = defaultTimeSlice;

static volatile StackPointer tsp;
static volatile StackSegment tss;
static volatile BasePointer tbp;

ElemTime *curr, *prev;

FunctionPointer System::oldTimer = 0;
FunctionPointer System::newTimer = 0;

static volatile unsigned infinite;


void System::initialize() {

#ifndef BCC_BLOCK_IGNORE
	HARD_LOCK
	PCB::running = new PCB();
	IdleThread* idleThread = new IdleThread();
	PCB::idle = idleThread->getMyPCB();
	oldTimer = getvect(0x8);
	newTimer = timer;
	setvect(0x8, newTimer);
	setvect(0x60, oldTimer);
	HARD_UNLOCK
#endif
}

void System::restore() {

#ifndef BCC_BLOCK_IGNORE
	HARD_LOCK
	delete PCB::idle;
	delete PCB::running;
	setvect(0x8, oldTimer);
	oldTimer = 0;
	newTimer = 0;
	HARD_UNLOCK
#endif
}

void System::updateTimeQueue() {


	if(System::sleepingThreads->first) {
			ElemTime* sleeping = System::sleepingThreads->first;
			sleeping->timeRemaining--;
			while (System::sleepingThreads->first  && System::sleepingThreads->first->timeRemaining == 0) {
				System::sleepingThreads->first->pcb->state=READY;
				Scheduler::put(System::sleepingThreads->first->pcb);
				System::sleepingThreads->removeFirst();
			}

	}

}

void interrupt System::timer(...) {

	if (!explicitTimerCall) {

#ifndef BCC_BLOCK_IGNORE
		asm {
			int 0x60
		}
#endif
		tick();
		--cnt;
		System::updateTimeQueue();

	}

	explicitTimerCall = 0;

	if ((!infinite && cnt == 0) || dispatchRequested) {

		if (!preemptionDisabled) {
			dispatchRequested = 0;

#ifndef BCC_BLOCK_IGNORE
			asm {
				mov tsp, sp
				mov tss, ss
				mov tbp, bp
			}
#endif

			PCB::running->ss = tss;
			PCB::running->sp = tsp;
			PCB::running->bp = tbp;

			if ((PCB::running != PCB::idle) && (PCB::running->state == READY))
				Scheduler::put(PCB::running);

			if ((PCB::running = Scheduler::get()) == 0)
				PCB::running = PCB::idle;

			tss = PCB::running->ss;
			tsp = PCB::running->sp;
			tbp = PCB::running->bp;

			cnt = PCB::running->timeSlice;
			infinite = !(cnt > 0);

#ifndef BCC_BLOCK_IGNORE
			asm {
				mov sp, tsp
				mov ss, tss
				mov bp, tbp
			}
#endif
		} else {
			dispatchRequested = 1;
		}
	}
}
