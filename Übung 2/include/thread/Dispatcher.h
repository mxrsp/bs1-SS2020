#ifndef Dispatcher_h
#define Dispatcher_h

/*
 * Dispatcher: 	Diese Klasse verwaltet den Zeiger auf den aktuell
 *		laufenden Prozess.
 *
 *	Anmerkung: Hier wird der Mechanismus der CPU-Zuteilung
 *	implementiert, daher ist dies eine Basisklasse
 *	des ActivitySchedulers, der wiederum fuer die strategischen
 *	Zuteilungsentscheidungen zustaendig ist.
 */

#include "thread/Coroutine.h"
#include "io/PrintStream.h"

extern PrintStream out;

class Dispatcher {
public:
	Dispatcher() 
	{ 
		running = 0; 
	}

	/* Definieren des ersten Prozesses.
	 * Wird nur einmal zur Initialisierung aufgerufen!!
	 */
	void init(Coroutine* act) 
	{ 
        out.println("Wir sind in init im Dispatcher angekommen");
        
        for (int i = 0; i < 15000000; i++) {}
        
		running = act; 
	}

	/* "active" liefert den Zeiger auf den aktiven Prozess.
	*/
	Coroutine* active() 
	{ 
		return running; 
	}

	/* "dispatch" wird vom ActivityScheduler aufgerufen,
	 * um vom aktiven zum neu ausgewaehlten Prozess zu wechseln.
	 * Man beachte die Reihenfolge der Anweisungen, die daraus
	 * resultiert, dass hier der Kontrollfluss gewechselt wird
	 */
	void dispatch(Coroutine* next)
	{
		Coroutine* curr = running;
        
        out.println("Wir sind in dispatch im Dispatcher");

        for (int i = 0; i < 15000000; i++) {}
        
		running = next;
        
		curr->resume(next);
	}

protected:
	Coroutine* running;
};

#endif
