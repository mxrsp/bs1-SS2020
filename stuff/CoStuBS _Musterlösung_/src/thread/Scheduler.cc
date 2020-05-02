/*
 * Scheduler.cc
 *
 *  Created on: 14.05.2019
 *      Author: Tom
 */
#include "interrupts/IntLock.h"
#include "thread/Scheduler.h"
	// Einfuegen eines neuen Elements in die Ready-Liste.
	void Scheduler :: schedule(Schedulable* sched){

		readylist.enqueue(sched);
	}

	// Entfernen eines Elements von der Ready-Liste.
	void Scheduler :: remove(Schedulable* sched){

		readylist.remove(sched);
	}

	// Aktiviert das vorderste der Liste mittels activate.
	void Scheduler :: reschedule(){

		Schedulable *x = ((Schedulable*)readylist.dequeue());
		this->activate(x);
	}
