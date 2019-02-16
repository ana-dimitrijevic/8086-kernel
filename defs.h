#ifndef _DEFS_H_
#define _DEFS_H_

typedef unsigned int StackSegment;
typedef unsigned int StackPointer;
typedef unsigned int BasePointer;
typedef unsigned long StackSize;
typedef unsigned int Time;
typedef int ID;
typedef unsigned int Data;
typedef enum State { CREATED, READY, BLOCKED, COMPLETED };
typedef unsigned char IVTNo;


typedef void interrupt(*FunctionPointer)(...);

const StackSize defaultStackSize = 4096;
const StackSize maxStackSize = 1UL << 16;
const Time defaultTimeSlice = 2;


//#define LOCK asm pushf;\
	//	asm cli;


//#define UNLOCK asm popf;

extern volatile char dispatchRequested;
extern volatile unsigned preemptionDisabled;

#define HARD_LOCK asm pushf;\
             asm cli;

#define HARD_UNLOCK asm popf;

#define SOFT_LOCK ++preemptionDisabled;

#define SOFT_UNLOCK --preemptionDisabled;\
                    if (!preemptionDisabled && dispatchRequested)\
                        dispatch();\
else ;

#endif

#define PREPAREENTRY(num, flag) \
void interrupt interruptRoutine##num(...) {\
    if (flag)\
        IVTEntry::callOldRoutine(num);\
    IVTEntry::signal(num);\
}\
IVTEntry entry##num(num, interruptRoutine##num);


