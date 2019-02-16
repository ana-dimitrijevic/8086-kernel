#ifndef _IVTENTRY_H_
#define _IVTENTRY_H_

#include "defs.h"

class Event;

class IVTEntry {

	public:
    IVTEntry(IVTNo, FunctionPointer);
    ~IVTEntry();

    static void addEntry(IVTNo, Event*);
    static void callOldRoutine(IVTNo);
    static IVTEntry* getIVTEntry(IVTNo);
    static void signal(IVTNo);


private:

    friend class Event;
    IVTNo entryNo;
    FunctionPointer oldRoutine;
    Event* event;

};


static IVTEntry* IVTEntries[256];


#endif
