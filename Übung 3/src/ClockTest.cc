
#include "device/CgaChannel.h"
#include "io/PrintStream.h"
#include "thread/ActivityScheduler.h"
#include "thread/Activity.h"

// #include "device/CPU.h"
#include "device/PIC.h"
// #include "device/Clock.h"
// #include "interrupts/InterruptGuardian.h"

//CPU cpu;

//InterruptGuardian interruptGuardian;
PIC pic;
//Clock clock(10000);

// globale Ein-/Ausgabeobjekte
CgaChannel cga;
PrintStream out(cga);

// Objekte der Prozessverwaltung
ActivityScheduler scheduler; // der Scheduler

int main(){
    
    out.println("Programm startet");
    
    //out.wait();
 
 	//cpu.enableInterrupts();
 	
    // while(1){}
}
