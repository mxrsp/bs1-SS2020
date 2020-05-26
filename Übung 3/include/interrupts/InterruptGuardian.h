#ifndef InterruptGuardian_h
#define InterruptGuardian_h

#include "interrupts/InterruptVector.h"
#include "interrupts/Gate.h"

class InterruptGuardian {
public:
	InterruptGuardian();

    // mitgegebenes Attribut könnte auch int sein
    
	static void handle(int num);

	static void registerGate(Gate* gate, int num);

private:
	static Gate* vectorTable[NrOfInterrupts];
};

#endif
