#include "timeq.h"

TimeQueue::TimeQueue() {
	first = 0;
	last = 0;
}

TimeQueue::~TimeQueue() {

	if (first == 0)
		return;
	else {

		ElemTime* toDelete;

		while (first) {

			toDelete = first;
			first = first->next;
			delete toDelete;

		}

		first = 0;
		last = 0;

	}

}

void TimeQueue::insert(PCB* pcb, Time time) {

	ElemTime* newElem = new ElemTime(pcb, time);
	ElemTime *curr=first, *prev=0;


	 while (curr && curr->timeRemaining <= time) {
	        time -= curr->timeRemaining;
	        prev = curr;
	        curr = curr->next;
	    }

	 newElem->timeRemaining = time;
	 newElem->next = curr;


	 if (prev!=0)
	         prev->next = newElem;
	     else
	         first = newElem;

	 if (curr!=0)
	         curr->timeRemaining -= time;


}


ElemTime* TimeQueue::removeFirst() {

	if (!first)
		return 0;

	ElemTime* toDelete = first;

	first = first->next;
	if (last == toDelete)
		last = 0;

	delete toDelete;
	return first;

}
