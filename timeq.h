#ifndef TIMEQ_H_
#define TIMEQ_H_

#include "defs.h"
#include"elemtime.h"

class PCB;

class TimeQueue {
public:

	TimeQueue();
	~TimeQueue();

	void insert(PCB*,Time);

	ElemTime* removeFirst();

	friend class System;


	ElemTime *first, *last;

};



#endif
