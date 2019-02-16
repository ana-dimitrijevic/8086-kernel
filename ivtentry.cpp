#include "ivtentry.h"
#include "kerev.h"
#include <dos.h>

IVTEntry::IVTEntry(IVTNo ivtNo, FunctionPointer newRoutine)
{
#ifndef BCC_BLOCK_IGNORE
	HARD_LOCK
	entryNo=ivtNo;
    event=0;
    oldRoutine = getvect(ivtNo);
    setvect(ivtNo, newRoutine);
    IVTEntries[ivtNo] = this;
    HARD_UNLOCK
#endif
}

IVTEntry::~IVTEntry() {
#ifndef BCC_BLOCK_IGNORE
	HARD_LOCK
    setvect(entryNo, oldRoutine);
	oldRoutine=0;
	HARD_UNLOCK
#endif
}

void IVTEntry::addEntry(IVTNo ivtNo, Event* event) {
   IVTEntries[ivtNo]->event = event;
}

void IVTEntry::callOldRoutine(IVTNo ivtNo) {

	FunctionPointer old = IVTEntries[ivtNo]->oldRoutine;
	(*old)();

}

IVTEntry* IVTEntry::getIVTEntry(IVTNo ivtNo) {
    return IVTEntries[ivtNo];
}

void IVTEntry::signal(IVTNo ivtNo) {
    if (IVTEntries[ivtNo]->event != 0)
        IVTEntries[ivtNo]->event->signal();
}


