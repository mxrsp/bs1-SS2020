#include "interrupts/InterruptGuardian.h"

#include "interrupts/PanicGate.h"
#include "io/Printstream.h"

extern PanicGate panicGate;

extern PrintStream out;

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

void InterruptGuardian::handle(int num)
{   
    // if (!(vectorTable[num] -> getNumber() == -1)) {
        vectorTable[num]->handle();
    // }
}

void InterruptGuardian::registerGate(Gate* gate,int num)
{
	if(!initialized){
		for(int i=0; i<NrOfInterrupts; i++){
			vectorTable[i] = &panicGate;
		}
		initialized = true;
	}
	if((num >= -1) && (num < NrOfInterrupts)){
		vectorTable[num] = gate;
        //out.println("interrupt wird registriert");
	}
}

