#include "sync/KernelSemaphore.h"

// Initialisierung des Zaehlers
//KernelSemaphore::KernelSemaphore (int count = 1) {}

extern ActivityScheduler scheduler;

void KernelSemaphore::wait () {
    
    if (counter > 0) {
        counter--;
    } else {
        Activity* sleeper = (Activity*) scheduler.active();
        sleepers.enqueue(sleeper);
        sleeperSize++;
        sleeper -> sleep();
    }
}

void KernelSemaphore::signal () {
    
    if (sleeperSize == 0) {
        counter++;
    } else {
        Activity* wakeUper = (Activity*) sleepers.dequeue();
        sleeperSize--;
        wakeUper -> wakeup(); 
    }
}



