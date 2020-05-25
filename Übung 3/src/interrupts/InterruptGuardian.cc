#include "interrupts/InterruptGuardian.h"

#include "interrupts/PanicGate.h"
extern PanicGate panicGate;

static bool initialized = false;
Gate* InterruptGuardian::vectorTable[NrOfInterrupts];

extern "C" void guardian(int num);

void guardian(int num)
{
	InterruptGuardian::handle(num);
}

InterruptGuardian::InterruptGuardian()
{
	if(!initialized){
		for(int i=0; i<NrOfInterrupts; i++){
			vectorTable[i] = &panicGate;
		}
		initialized = true;
	}
}

void InterruptGuardian::handle(unsigned num)
{
	vectorTable[num]->handle();
}

void InterruptGuardian::registerGate(Gate* gate,unsigned num)
{
	if(!initialized){
		for(int i=0; i<NrOfInterrupts; i++){
			vectorTable[i] = &panicGate;
		}
		initialized = true;
	}
	if(((int)num >= -1) && (num < NrOfInterrupts)){
		vectorTable[num] = gate;
	}
}

