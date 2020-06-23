#ifndef KernelSemaphore_h
#define KernelSemaphore_h

#include"lib/Queue.h"
#include"thread/Activity.h"
#include"thread/ActivityScheduler.h"

/**
 * KernelSemaphore: Semaphorenimplementation für kooperative
 * Prozesse oder zur Anwendung innerhalb des Kernels.
 */
class KernelSemaphore {
public:
	// Initialisierung des Zaehlers
	KernelSemaphore(int count = 1)
	{
        this -> counter = count;
	}

	void wait();
	void signal();

private:
    
    int counter = 0;
    int sleeperSize = 0;
    Queue sleepers;

};

#endif

