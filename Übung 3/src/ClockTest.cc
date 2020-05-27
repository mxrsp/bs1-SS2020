
#include "device/CgaChannel.h"
#include "io/PrintStream.h"
#include "thread/ActivityScheduler.h"
#include "thread/Activity.h"

#include "device/CPU.h"
#include "device/PIC.h"
#include "device/Clock.h"
#include "interrupts/InterruptGuardian.h"

// globale Ein-/Ausgabeobjekte

// wird in der Clock erstellt

// CgaChannel cga;
// PrintStream out(cga);

CPU cpu;

InterruptGuardian interruptGuardian;
PIC pic;
Clock clock(2000);

extern CgaChannel cga;
extern PrintStream out;

// Objekte der Prozessverwaltung
ActivityScheduler scheduler; // der Scheduler

int main(){
 
 	cpu.enableInterrupts();
    
    while(1){}
}
