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
        bool laeuft;
        
        out.println("kill in ActivityScheduler erreicht");
        
        if (act -> isRunning()) {
            laeuft = true;
        } else {
            laeuft = false;
        }
        
        act -> changeTo(Activity :: BLOCKED);
        
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
		Activity* active = (Activity*) this -> active();
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
        
		Activity* active = (Activity*) this -> active();
        
        out.print(active -> getNameActivity());
        out.println(" ist derzeit der aktive Prozess");
        
        Activity* next = (Activity*) to;
        
        if ((active -> isZombie() == false) && (active -> isBlocked() == false)){
            scheduler.reschedule();
            scheduler.schedule(active);
        }
        
        if (next == 0) {
                out.println("Zeiger ist Null in ActivityScheduler");
                for (int i = 0; i < 15000000; i++) {}
        }
        
//         while (next == 0) {
//              next = (Activity*)readylist.dequeue();
//              out.println("PARTYYY");
//         }
        
        scheduler.dispatch(next);
        
        // hier wird danach irgendwann Berta 0 ausgegeben
        // es muss eigentlich das Zeug hier drunter ausgegeben werden !!
        
        Activity* neuerAct = (Activity*) this -> active();
        out.print(neuerAct -> getNameActivity());
        out.println(" ist der NEUE aktive Prozess");
        
	}
