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
        Activity* active = (Activity*) scheduler.active();
        
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
        bool laeuft;
        
        out.print(act -> getNameActivity());
        out.println(" wird vom ActivityScheduler umgebracht");
        for (int i = 0; i < 40000000; i++) {}
        
        if (act -> isRunning()) {
            laeuft = true;
        } else {
            laeuft = false;
        }
        
        act -> changeTo(Activity :: ZOMBIE);
        
        scheduler.remove(act);
        
        if (laeuft) {
            scheduler.reschedule();
        } 
	}

	/* Terminieren des aktiven Prozesses,
	 * und Wechsel zum naechsten lauffaehigen Prozess
	 */
	void ActivityScheduler::exit() {
        out.println("exit in ActivityScheduler erreicht");
		Activity* active = (Activity*) scheduler.active();
        active -> exit();
        
        // TODO: Welches exit wird wann aufgerufen-> vgl Activity
        
        scheduler.reschedule();
	}

	/* Der aktive Prozess ist, sofern er sich nicht im Zustand
	 * Blocked oder Zombie befindet, wieder auf die Ready-Liste
	 * zu setzen. Danach ist "to" mittels dispatch die Kontrolle
	 * zu übergeben.
	 */
	void ActivityScheduler::activate(Schedulable* to) {
        
        out.println("activate in ActivityScheduler erreicht");
        
		Activity* active = (Activity*) scheduler.active();
        
        out.print(active -> getNameActivity());
        out.print(" ist derzeit der aktive Prozess und dieser hat den Zustand: ");
        out.println(active -> getState());
        active -> changeTo(Activity :: READY);
        
        Activity* next = (Activity*) to;
        
        if (next == 0) {
                out.println("Zeiger ist Null in ActivityScheduler");
                for (int i = 0; i < 15000000; i++) {}
        }
        
//         while (next == 0) {
//              next = (Activity*)readylist.dequeue();
//              out.println("PARTYYY");
//         }

        if ((active -> isZombie() == false) && (active -> isBlocked() == false)){
            // scheduler.reschedule();
            scheduler.schedule(active);
        }
        
        next -> changeTo(Activity :: RUNNING);
        scheduler.dispatch(next);
        
        Activity* neuerAct = (Activity*) scheduler.active();
        out.print(neuerAct -> getNameActivity());
        out.print(" ist der NEUE aktive Prozess und dieser hat den Zustand: ");
        out.println(neuerAct -> getState());
        
        // hier wird danach irgendwann Berta 0 ausgegeben
        // es muss eigentlich das Zeug hier drunter ausgegeben werden !!
        
	}
