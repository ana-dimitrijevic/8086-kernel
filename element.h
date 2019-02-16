#ifndef _ELEMENT_H_
#define _ELEMENT_H_

#include "pcb.h"

class Element {

public :
	Element(PCB* newPCB) {
		this->pcb = newPCB;
		this->next = 0;
	}
	~Element() {
		 pcb = 0;
		 next = 0;
	}

private :

	friend class List;
	friend class System;

	PCB* pcb;
	Element* next;
};



#endif
