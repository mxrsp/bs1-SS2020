#ifndef Semaphore_h
#define Semaphore_h

#include "sync/KernelSemaphore.h"
#include "sync/KernelLock.h"
#include "thread/Activity.h"
#include "thread/ActivityScheduler.h"

/**
 *  Semaphore: Die Semaphorenimplementation für Benutzerprozesse
 */
class Semaphore: private KernelSemaphore {
public:
	
	Semaphore(int count = 1) : counter(count) {		
	}

	void wait()
	{
        KernelLock lock;
        KernelSemaphore :: wait();
	}

	void signal()
	{
        KernelLock lock;
        KernelSemaphore :: signal();
	}
};
private:
	
	
#endif
