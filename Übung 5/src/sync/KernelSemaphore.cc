#include "sync/KernelSemaphore.h"
#include "io/PrintStream.h"

extern PrintStream out;

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



