
#include "device/CgaChannel.h"
#include "device/CPU.h"
#include "io/PrintStream.h"
#include "thread/Activity.h"
#include "thread/ActivityScheduler.h"
#include "device/PIC.h"
#include "device/Clock.h"
#include "interrupts/InterruptGuardian.h"


/*
 * test.cc
 *
 *  Created on: 06.05.2019
 *      Author: Tom
 */

CPU cpu;

InterruptGuardian interruptGuardian;
PIC pic;
Clock clock(2500);

// globale Ein-/Ausgabeobjekte

// Objekte der Prozessverwaltung
ActivityScheduler scheduler; // der Scheduler

int main(){

	cpu.enableInterrupts();
	while(1){}

}

