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
//#include "thread/ActivityScheduler.h"
#include "device/Clock.h"

extern PrintStream out;
//ActivityScheduler activityScheduler; 

	// Einfuegen eines neuen Elements in die Ready-Liste.
	void Scheduler::schedule(Schedulable* sched) {

        readylist.enqueue(sched);
        
	}

	// Entfernen eines Elements von der Ready-Liste.
	void Scheduler::remove(Schedulable* sched) {

        readylist.remove(sched);
        
	}

	// Aktiviert das vorderste der Liste mittels activate.
	void Scheduler::reschedule() {
        
		Schedulable* firstElement;
        
        firstElement = (Schedulable*) readylist.dequeue();
        
        if (firstElement != 0) {
            this -> activate(firstElement);
        } 
	}
	
	// Aktivem Prozess wird CPU erst dann entzogen, wenn seine Zeitscheibe(Quantum) abgelaufen ist
    void Scheduler::checkSlice() {
        //int quantum = Schedulable :: quantum();
//         int quantum = 1;
//         
//         out.println("checkSlice wird aufgerufen");
//         out.wait();
//         
//         if (quantum == 0) {
//             this -> reschedule();
//         }
//         
        
        
        if (clock.ticks() == ((Activity*) scheduler.active())->quantum()){
            clock.nullticks();
            this->reschedule();
        }
        
    }
