#ifndef InterruptGuardian_h
#define InterruptGuardian_h

#include "interrupts/InterruptVector.h"
#include "interrupts/Gate.h"
#include "io/PrintStream.h"

//extern PrintStream out;

class InterruptGuardian {
public:
	InterruptGuardian();
    
	static void handle(int num);

	static void registerGate(Gate* gate, int num);

private:
	static Gate* vectorTable[NrOfInterrupts];
};

#endif
