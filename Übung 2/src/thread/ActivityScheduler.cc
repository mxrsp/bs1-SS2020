/*
 * ActivityScheduler: 	Diese Klasse implementiert die Zustandsverwaltung
 * 			für Activities
 *
 */

#include "lib/Queue.h"
#include "thread/Activity.h"
#include "thread/Dispatcher.h"
#include "thread/Scheduler.h"
#include "thread/ActivityScheduler.h"


	/* Suspendieren des aktiven Prozesses
	 * Der korrekte Ausfuehrungszustand ist zu setzen
	 * und danach der naechste lauffaehige Prozess zu aktivieren.
	 */
	void ActivityScheduler::suspend()	{
        out.println("suspend in  ActivityScheduler");
        Activity* active = (Activity*) this -> active();
        
        active -> changeTo(Activity :: BLOCKED);
        
        scheduler.reschedule();
	}

	/* Explizites Terminieren des angegebenen Prozesses
	 * Der Prozesszustand ist korrekt zu setzen
	 * und der Prozess aus der Ready-Liste des Schedulers
	 * zu entfernen. Falls der aktive Prozess zerstoert wird,
	 * ist dem naechsten lauffaehigen Prozess die CPU
	 * zuzuteilen.
	 */
	void ActivityScheduler::kill(Activity* act) {
        bool running;
        
        out.println("kill in ActivityScheduler erreicht");
        
        if (act -> isRunning()) {
            running = true;
        } else {
            running = false;
        }
        /*
        act -> changeTo(Activity :: BLOCKED);
		act -> ~Activity();*/
        
        if (running) {
            scheduler.remove(act);
        }
        
        scheduler.reschedule();
	}

	/* Terminieren des aktiven Prozesses,
	 * und Wechsel zum naechsten lauffaehigen Prozess
	 */
	void ActivityScheduler::exit() {
        out.println("exit in ActivityScheduler erreicht");
		Activity* active = (Activity*) this -> active();
        active -> exit();
        
        scheduler.reschedule();
	}

	/* Der aktive Prozess ist, sofern er sich nicht im Zustand
	 * Blocked oder Zombie befindet, wieder auf die Ready-Liste
	 * zu setzen. Danach ist "to" mittels dispatch die Kontrolle
	 * zu übergeben.
	 */
	void ActivityScheduler::activate(Schedulable* to) {
        
        out.println("activate in ActivityScheduler erreicht");
        
		Activity* active = (Activity*) this -> active();
        
        for (int i = 0; i < 15000000; i++) {}
        out.println("activate kurz vor Schleife in ActivityScheduler erreicht");
        for (int i = 0; i < 15000000; i++) {}
        // if ((active -> isZombie() == false) && (active -> isBlocked() == false)){
        // if (!(active -> isBlocked())) {
        if (true) {
            out.println("activate am Anfang von Schleife in ActivityScheduler erreicht");
            for (int i = 0; i < 15000000; i++) {}
            scheduler.schedule(active);
            out.println("Wir sind in der Schleife in active in ActivityScheduler");
            for (int i = 0; i < 15000000; i++) {}
        } else {
            for (int i = 0; i < 20000000; i++)
            out.println("Wir sind in der else-Zweig im ActivityScheduler");
        }
        
        for (int i = 0; i < 20000000; i++)
            out.println("Wir haben die Schleife verlassen im ActivityScheduler");
        
        
        dispatch((Activity*) to);
	}
