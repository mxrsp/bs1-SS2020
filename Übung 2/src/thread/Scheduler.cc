/*
 * Scheduler: 	Diese Klasse implementiert die Zuteilungsstrategie
 *		fuer die CPU.
 *
 *	Anmerkung: Hier wird ein einfacher First-Come-First-Served
 *	Algorithmus implementiert, der sich auf eine
 *	ready-liste stuetzt, in dem alle lauffaehigen Prozesse
 *	miteinander verkettet sind.
 */

#include "lib/Queue.h"
#include "thread/Schedulable.h"
#include "thread/Scheduler.h"


	// Einfuegen eines neuen Elements in die Ready-Liste.
	void Scheduler::schedule(Schedulable* sched) {
        out.println("schedule in Scheduler wurd erreicht");
        
        out.print(((Activity*)sched) -> getNameActivity());
        out.println(" wird in die Readyliste eingefuegt");
        
        if (sched == 0) {
            out.println("Der Pointer in Scheduler ist Null");
        }
        for (int i = 0; i < 40000000; i++) {}
        
        readylist.enqueue(sched);
	}

	// Entfernen eines Elements von der Ready-Liste.
	void Scheduler::remove(Schedulable* sched) {
        out.println("remove in Scheduler wurd erreicht");
        readylist.remove(sched);
	}

	// Aktiviert das vorderste der Liste mittels activate.
	void Scheduler::reschedule() {
        
        out.println("Wir sind in reschudele im Scheduler");
        
		Schedulable* firstElement;
        
        firstElement = (Schedulable*) readylist.dequeue();
        
        out.print(((Activity*)firstElement) -> getNameActivity());
        out.println(" wird von der Readyliste geloescht");
        
        if (firstElement == 0) {
                out.println("FirstElement ist Null im Scheduler");
                for (int i = 0; i < 70000000; i++) {}
        }
        
        
        
        for (int i = 0; i < 40000000; i++) {}
        this -> activate(firstElement);
	}
