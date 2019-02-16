#ifndef _KERSEM_H_
#define _KERSEM_H_

class List;

class KernelSem {
public:
	KernelSem (int);
	~KernelSem ();
	int wait (int);
	void signal();
	int getSemaphoreValue()const;
protected:
	void block();
	void deblock();
private:
	int val;
	List* blockedOnThisSemaphore;

};

#endif
