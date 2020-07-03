#include "sync/Monitor.h"
#include "interrupts/IntLock.h"

#include "device/CPU.h"
#include "io/PrintStream.h"

extern PrintStream out;
extern CPU cpu;

void Monitor::runEpilogue(Gate *gate)
{
	// hoechste Interrupt-Prioritaet
	IntLock lock;
    
    // out.print("monitor.runEpilogue()");
    
	// bereits vermerkt!
	if (gate->isDeferred()) {
        // out.println("Das Gate ist bereits vermerkt -> nichts passiert");
        return; 
    }

	gate->setDeferred(true);
	// Kernel ist frei
	if (free) {
	
        // Kernel als besetzt markieren
		enter();
		
		// Interrupts an!
		cpu.enableInterrupts();
		
		// Epilog aufrufen
		gate->epilogue();
		
		cpu.disableInterrupts();
		gate->setDeferred(false);
		
		// Kernel wieder freigeben
		leave();
	} else {
		// Epilog merken
        deferred.enqueue(gate);
	}
}

void Monitor::leave()
{   
    // out.println("monitor.leave()");
    
	IntLock lock;
	Gate* next = (Gate*)deferred.dequeue();
	while (next) {
		cpu.enableInterrupts();
		// Epilog aufrufen
		next->epilogue();
		cpu.disableInterrupts();
		next->setDeferred(false);
		next = (Gate*)deferred.dequeue();
	}
	// Monitor freigeben
	free = true;
    // out.println("Kern ist frei");
}

