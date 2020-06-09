#include "interrupts/PanicGate.h"
#include "device/CgaChannel.h"
#include "device/CPU.h"
extern CPU cpu;
extern CgaChannel cga;

PanicGate::PanicGate(): Gate(-1) { }

void PanicGate::handle()
{
    out.println("Jetzt tritt ein PanikGate auf");
    while(1) {}
    
 cga.blueScreen("Panic: Illegal Trap/Interrupt!");
	cpu.halt();
}
