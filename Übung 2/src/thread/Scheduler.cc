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

	// Einfuegen eines neuen Elements in die Ready-Liste.
	void Scheduler::schedule(Schedulable* sched) {
	
	}

	// Entfernen eines Elements von der Ready-Liste.
	void Scheduler::remove(Schedulable* sched) {
		
	}

	// Aktiviert das vorderste der Liste mittels activate.
	void Scheduler::reschedule() {
		
	}
