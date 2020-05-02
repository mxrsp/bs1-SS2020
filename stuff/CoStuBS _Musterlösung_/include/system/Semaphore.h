#ifndef Semaphore_h
#define Semaphore_h

#include "sync/KernelSemaphore.h"
#include "sync/KernelLock.h"

/**
 *  Semaphore: Die Semaphorenimplementation für Benutzerprozesse
 */
class Semaphore: private KernelSemaphore {
public:
	Semaphore(int count = 1):KernelSemaphore(count)
	{}

	void wait()
	{
		KernelLock locked;
		KernelSemaphore ::wait();
	}

	void signal()
	{
		KernelLock locked;
		KernelSemaphore ::signal();
	}
};

#endif
