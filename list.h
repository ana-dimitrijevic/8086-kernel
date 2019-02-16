#ifndef _LIST_H_
#define _LIST_H_

#include "defs.h"

class Element;
class PCB;

class List {

public:

	List();
	~List();

	PCB* get(ID);
	PCB* get(PCB*);
	PCB* getFirst();
	PCB* getLast();

	void insert(PCB*);

	PCB* remove(ID);
	PCB* remove(PCB*);
	PCB* removeFirst();
	PCB* removeLast();



private:

	Element *first,*last;

};



#endif
