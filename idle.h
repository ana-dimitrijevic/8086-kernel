#ifndef _IDLE_H_
#define _IDLE_H_

#include "thread.h"

class IdleThread: public Thread {
public:
	IdleThread() :
			Thread(defaultStackSize, defaultTimeSlice) {
	}
protected:
	void run() {
		volatile int x = 1;
		while (x) {
		}
	}
};

#endif

