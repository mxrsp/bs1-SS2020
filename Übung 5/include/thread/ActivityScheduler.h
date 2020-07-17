#ifndef ActivityScheduler_h
#define ActivityScheduler_h

/*
 * ActivityScheduler: 	Diese Klasse implementiert die Zustandsverwaltung
 * 			für Activities
 *
 */

#include "thread/Scheduler.h"
#include "lib/Queue.h"
#include "thread/Activity.h"
#include "thread/Dispatcher.h"

class ActivityScheduler: public Dispatcher, public Scheduler {
public:
	ActivityScheduler()
	{
	}

	/* Initialisieren der ersten Aktivität, des Schedulers
	 * und des Dispatchers.
	 * Wird nur einmal aufgerufen.
	 */
	void start(Activity* act)
	{       
        act -> changeTo(Activity :: RUNNING);
        
        act -> setNameActivity("Init");
        
        Coroutine* c = (Coroutine*) act;
        init(c);
	}

	/* Suspendieren des aktiven Prozesses
	 * Der korrekte Ausfuehrungszustand ist zu setzen
	 * und danach der naechste lauffaehige Prozess zu aktivieren.
	 */
	void suspend();

	/* Explizites Terminieren des angegebenen Prozesses
	 * Der Prozesszustand ist korrekt zu setzen
	 * und der Prozess aus der Ready-Liste des Schedulers
	 * zu entfernen. Falls der aktive Prozess zerstoert wird,
	 * ist dem naechsten lauffaehigen Prozess die CPU
	 * zuzuteilen.
	 */
	void kill(Activity* act);

	/* Terminieren des aktiven Prozesses,
	 * und Wechsel zum naechsten lauffaehigen Prozess
	 */
	void exit();

    bool getActivateBlocked () {
        return this -> activateBlocked;
    }

protected:
	/* Der aktive Prozess ist, sofern er sich nicht im Zustand
	 * Blocked oder Zombie befindet, wieder auf die Ready-Liste
	 * zu setzen. Danach ist "to" mittels dispatch die Kontrolle
	 * zu übergeben.
	 */
	virtual void activate(Schedulable* to);

    
private:
    
    bool activateBlocked = false;
    
};

extern ActivityScheduler scheduler;

#endif
