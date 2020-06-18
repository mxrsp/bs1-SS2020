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

	void wait() {
		
		KernelLock lock;
		
		if(counter > 0) {	//Signale vorhanden
			counter = counter - 1;
			
		} else {	//keine Signale vorhanden -> schlafen
			Activity* act = (Activity*) scheduler.active();
			sleepers.enqueue(act);
			act -> sleep();
			}	
	}

	void signal() {
		
		KernelLock lock;
		
		if(sleepers.isEmpty()) {	//prüfen, ob jemand schläft
		counter = counter + 1;	//niemand schläft -> signal wird nur mitgezählt
		} else {
			Activity* next = (Activity*) sleepers.dequeue();
			next -> wakeup();
		}
	}
};
private:
	
	
#endif
