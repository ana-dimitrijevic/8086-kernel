#ifndef _PCB_H_
#define _PCB_H_

#include "defs.h"
#include "thread.h"

class List;

class PCB {
public:

	static PCB* running;
	static PCB* idle;

	//static List* allThreads;

	PCB();
	PCB(Thread*, StackSize, Time);
	~PCB();
	ID getID();

	void start();
	void waitToComplete(); //joins on this thread
	static void sleep(Time);

private:

	friend class System;
	friend class KernelSem;
	friend class KernelEv;

	static ID idGenerator;
	static void wrapper();

	ID id;
	Thread* myThread;
	Data* stack;
	StackSegment ss;
	StackPointer sp;
	BasePointer bp;
	Time timeSlice;
	volatile State state;

	List* blockedOnThisThread;

};

#endif
