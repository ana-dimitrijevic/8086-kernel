#ifndef _SYSTEM_H_
#define _SYSTEM_H_

#include "defs.h"
#include "pcb.h"

class TimeQueue;

extern volatile char dispatchRequested;
extern volatile unsigned preemptionDisabled;
extern volatile char explicitTimerCall;

class System {

public:

	static TimeQueue* sleepingThreads;

	static void initialize();
	static void restore();

	static void updateTimeQueue();

	static void interrupt timer(...);

private:

	static FunctionPointer oldTimer;
	static FunctionPointer newTimer;
};


#endif
