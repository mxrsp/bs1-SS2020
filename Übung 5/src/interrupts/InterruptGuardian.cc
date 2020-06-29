#include "interrupts/InterruptGuardian.h"
#include "sync/Monitor.h"

#include "interrupts/PanicGate.h"
#include "io/PrintStream.h"

extern PrintStream out;
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

void InterruptGuardian::handle(int num)
{
	Gate* gate = vectorTable[num];
    
	if(gate->prologue()){
		monitor.runEpilogue(gate);
	}
}

void InterruptGuardian::registerGate(Gate* gate,int num)
{   
     // out.println("gate wird registriert");
     //   for (int i = 0 ; i < 10000000; i++) {}
    
	if(!initialized){
		for(int i=0; i<NrOfInterrupts; i++){
			vectorTable[i] = &panicGate;
		}
		initialized = true;
	}
	if((num >= -1) && (num < NrOfInterrupts)){
		vectorTable[num] = gate;
	}
}

