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
        // IntLock lock;
        
        // out.println("Ein Objekt wird in die readylist gepackt");
        
        readylist.enqueue(sched);
	}

	// Entfernen eines Elements von der Ready-Liste.
	void Scheduler::remove(Schedulable* sched) {
        // IntLock lock;
        
        readylist.remove(sched);
	}

	// Aktiviert das vorderste der Liste mittels activate.
	void Scheduler::reschedule() {
        
        // IntLock lock;
        
		Schedulable* firstElement;
        
        firstElement = (Schedulable*) readylist.dequeue();
        
        this -> activate(firstElement);
	}
	
	// Aktivem Prozess wird CPU erst dann entzogen, wenn seine Zeitscheibe(Quantum) abgelaufen ist
    void Scheduler::checkSlice() {
        
        out.println("checkSlice wird aufgerufen.");
        
        // IntLock lock;
        
        if (((Activity*) scheduler.active()) -> isRunning()) {
            if (checkCounter >= ((Activity*) scheduler.active())->quantum()){
                checkCounter = 0;
                reschedule();
            } else {
                checkCounter++;
            }
        }
    }
