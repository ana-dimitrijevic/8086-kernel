#ifndef _ELEMTIME_H_
#define _ELEMTIME_H_

#include "defs.h"
#include "pcb.h"

class ElemTime {

public:

	ElemTime(PCB* newPCB, Time timeRemaining) {
		this->pcb = newPCB;
		this->next = 0;
		this->timeRemaining = timeRemaining;
	}
	~ElemTime() {
		 pcb = 0;
		 next = 0;
	}

	friend class TimeQueue;
	friend class System;

	PCB* pcb;
	Time timeRemaining;
	ElemTime* next;

};

#endif
