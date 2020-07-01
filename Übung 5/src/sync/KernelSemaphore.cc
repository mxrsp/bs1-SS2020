#include "sync/KernelSemaphore.h"
#include "io/PrintStream.h"

extern PrintStream out;

extern ActivityScheduler scheduler;

void KernelSemaphore::wait () {
    
    if (counter > 0) {
        this -> counter--;
        // out.println("counter--");
    } else {
        Activity* sleeper = (Activity*) scheduler.active();
        sleepers.enqueue(sleeper);
        sleeperSize++;
        //out.println("ACHTUNG KernelSemaphore wait sleep irgendwas");
        sleeper -> sleep();
    }
}

void KernelSemaphore::signal () {
    
    if (sleeperSize == 0) {
        this -> counter++;
        //out.println("counter++");
    } else {
        Activity* wakeUper = (Activity*) sleepers.dequeue();
        sleeperSize--;
        //out.println("ACHTUNG KernelSemaphore signal wakeup irgendwas");
        wakeUper -> wakeup();
    }
}



