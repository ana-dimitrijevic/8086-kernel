#include "list.h"
#include "element.h"
#include "pcb.h"

List::List() {
	first=0;
	last=0;
}



List::~List() {

	if (first==0) return;
	else{

	Element* toDelete;
	while(first) {

		toDelete=first;
		first=first->next;
		delete toDelete;

	}

	first=0;
	last=0;

	}

}

PCB* List::getFirst() {

	if (first!=0) {
		return first->pcb;
	}
	else {
		return 0;
	}


}

PCB* List::getLast() {

	if (last!=0){
		return last->pcb;
	}
	else {
		return 0;
	}


}

PCB* List::get(ID requestedID) {

	if (first==0) return 0;
	else {

	Element* curr=first;
	while(curr && curr->pcb->getID()!=requestedID) {
		curr=curr->next;
	}

	if (curr==0) return 0;
	else return curr->pcb;
	}

}

PCB* List::get(PCB* requestedPCB) {

	if (first==0) return 0;
	else {

	Element* curr=first;
	while(curr && curr->pcb!=requestedPCB) {
		curr=curr->next;
	}

	if (curr==0) return 0;
	else return curr->pcb;
	}

}


void List::insert(PCB* newPCB) {

	Element* newElement=new Element(newPCB);

	if (first==0) first=newElement;
	else last->next=newElement;

	last=newElement;

}


PCB* List::removeFirst() {

	if (first!=0) {

		PCB* toReturn = first->pcb;
		Element* toDelete=first;

		if(first==last) {
			first=0;
			last=0;
		}

		else {
			first=first->next;
		}

		delete toDelete;
		return toReturn;
	}
	else return 0;

}


PCB* List::removeLast() {

	if (first!=0) {
		PCB* toReturn = last->pcb;

		Element* toDelete=last;

		if(first==last) {
			first=0;
			last=0;
		}
		else {
			Element* prev=first;
			while (prev->next!=last) {prev=prev->next;}
			prev->next=0;
			last=prev;
		}

		delete toDelete;
		return toReturn;
	}
	else return 0;

}

PCB* List::remove(PCB* requestedPCB) {

		if (first==0) return 0;
		else {

		Element *curr=first, *prev=0;

		while(curr && curr->pcb!=requestedPCB) {
			prev=curr;
			curr=curr->next;
		}

		if (curr==0) return 0;
		else {

			
			if (curr==first && first==last) {
					first=0;
					last=0;
					}

			
			else if (curr==first) {
					first=first->next;
					}

			else {
				if(prev->next==last) last=prev;
				prev->next=curr->next;
			}


			PCB* toReturn=curr->pcb;
			delete curr;
			return toReturn;
		}
		}

}

PCB* List::remove(ID requestedID) {

	if (first==0) return 0;
	else {

	Element *curr=first, *prev=0;

	while(curr && curr->pcb->getID()!=requestedID) {
		prev=curr;
		curr=curr->next;
	}

	if (curr==0) return 0;
	else {

		
		if (curr==first && first==last) {
			first=0;
			last=0;
		}

		
		else if (curr==first) {
			first=first->next;
		}

		
		else {
			if(prev->next==last) last=prev;
			prev->next=curr->next;
		}


		PCB* toReturn=curr->pcb;

		delete curr;
		return toReturn;
	}
	}
}


