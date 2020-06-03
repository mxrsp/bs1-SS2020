/*
 * Scheduler: 	Diese Klasse implementiert die Zuteilungsstrategie
 *		fuer die CPU.
 *
 *	Anmerkung: Hier wird ein einfacher First-Come-First-Served
 *	Algorithmus implementiert, der sich auf eine
 *	ready-liste stuetzt, in dem alle lauffaehigen Prozesse
 *	miteinander verkettet sind.
 */

#include "thread/Scheduler.h"
#include "io/PrintStream.h"
#include "device/Clock.h"
#include "interrupts/IntLock.h"

extern PrintStream out;

	// Einfuegen eines neuen Elements in die Ready-Liste.
	void Scheduler::schedule(Schedulable* sched) {
        IntLock lock;
        
        readylist.enqueue(sched);
	}

	// Entfernen eines Elements von der Ready-Liste.
	void Scheduler::remove(Schedulable* sched) {
        IntLock lock;
        
        readylist.remove(sched);
	}

	// Aktiviert das vorderste der Liste mittels activate.
	void Scheduler::reschedule() {
        
        IntLock lock;
        
		Schedulable* firstElement;
        
        firstElement = (Schedulable*) readylist.dequeue();
        
        // if (firstElement != 0) {
            this -> activate(firstElement);
        // } 
	}
	
	// Aktivem Prozess wird CPU erst dann entzogen, wenn seine Zeitscheibe(Quantum) abgelaufen ist
    void Scheduler::checkSlice() {
        
        IntLock lock;
        
//          out.print(clock.ticks());
//          out.print("  ");
//          out.print(((Activity*) scheduler.active())->quantum());
//          out.println();
        
//         for (int i = 0; i < 100000; i++) {}
//         out.println(" checkSlice aufgerufen      ");
        
        if (clock.ticks() == ((Activity*) scheduler.active())->quantum()){
            clock.setTicks(0);
            //out.println("Jetzt sind wir in der Endlosschleife");
            //while(1) {}
            this->reschedule();
        }
    }
