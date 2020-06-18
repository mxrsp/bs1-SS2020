#include "sync/KernelSemaphore.h"
#include "thread/Activity.h"
#include "thread/ActivityScheduler.h"

void KernelSemaphore::wait() {	
	if(counter > 0) {	//Signale vorhanden
		counter = counter - 1;
	} else {	//keine Signale vorhanden -> schlafen
		Activity* act = (Activity*) scheduler.active();
		sleepers.enqueue(act);
		act -> sleep();
	}	
}

void KernelSemaphore::signal() {
	if(sleepers.isEmpty()) {	//prüfen, ob jemand schläft
		counter = counter + 1;	//niemand schläft -> signal wird nur mitgezählt
	} else {
		
	}
}
