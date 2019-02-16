#ifndef _SEMAPHOR_H_
#define _SEMAPHOR_H_

#include "defs.h"

class KernelSem;

class Semaphore {
public:
  Semaphore (int);
  virtual ~Semaphore ();
  virtual int wait (int);
  virtual void signal();
  int val () const;
private:
  KernelSem* myImpl;
};


#endif

