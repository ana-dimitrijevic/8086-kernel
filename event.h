#ifndef _EVENT_H_
#define _EVENT_H_

#include "defs.h"
#include "ivtentry.h"

class KernelEv;


class Event {
public:
	Event(IVTNo);
	~Event();
	void wait();
protected:
	friend class IVTEntry;
	void signal();
private:
	KernelEv* myImpl;
};


#endif
