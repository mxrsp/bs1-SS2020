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
#include "device/CPU.h"
#include "interrupts/IntLock.h"

extern CPU cpu;

	/* Suspendieren des aktiven Prozesses
	 * Der korrekte Ausfuehrungszustand ist zu setzen
	 * und danach der naechste lauffaehige Prozess zu aktivieren.
	 */
	void ActivityScheduler::suspend()	{
        
        IntLock lock;
        
        Activity* active = (Activity*) scheduler.active();
        
        active -> changeTo(Activity :: BLOCKED);
        
        scheduler.reschedule();
        
        active = (Activity*) scheduler.active();
        
	}

	/* Explizites Terminieren des angegebenen Prozesses
	 * Der Prozesszustand ist korrekt zu setzen
	 * und der Prozess aus der Ready-Liste des Schedulers
	 * zu entfernen. Falls der aktive Prozess zerstoert wird,
	 * ist dem naechsten lauffaehigen Prozess die CPU
	 * zuzuteilen.
	 */
	void ActivityScheduler::kill(Activity* act) {
        
        IntLock lock;
        
        bool laeuft;

        if (act -> isRunning()) {
            laeuft = true;
        } else {
            laeuft = false;
        }
        
        act -> changeTo(Activity :: ZOMBIE);
        
        if (laeuft) {
            scheduler.reschedule();
        } else {
            scheduler.remove(act);
        }
	}

	/* Terminieren des aktiven Prozesses,
	 * und Wechsel zum naechsten lauffaehigen Prozess
	 */
	void ActivityScheduler::exit() {
        
        IntLock lock;
        
		Activity* active = (Activity*) scheduler.active();
        active -> changeTo(Activity :: ZOMBIE);
        
        this -> reschedule();
	}

	/* Der aktive Prozess ist, sofern er sich nicht im Zustand
	 * Blocked oder Zombie befindet, wieder auf die Ready-Liste
	 * zu setzen. Danach ist "to" mittels dispatch die Kontrolle
	 * zu übergeben.
	 */
	void ActivityScheduler::activate(Schedulable* to) {
        
        Activity* active = (Activity*) scheduler.active(); 
        Activity* next = (Activity*) to;

        // wenn Zustand Running oder Ready, dann automatisch nicht im Zustand Blocked/Zombie
        if ((active -> isRunning()) ||  (active -> isReady())){
            active -> changeTo(Activity :: READY);
            scheduler.schedule(active);
        }

        if(next == 0) {
            while (next == 0) {
                
                out.print(".");
                for (int i = 0 ; i < 10000; i++);
                
                // interrupts kurz zulassen
                cpu.enableInterrupts();
                cpu.halt();
                cpu.disableInterrupts();
                
                next = (Activity*) readylist.dequeue();
            }
            next -> changeTo(Activity :: RUNNING);
            dispatch(next);
        } else {
            // kein Prozesswechsel, wenn der zu aktivierende Prozess eh aktiv ist  
            if (next != active) {
                next -> changeTo(Activity :: RUNNING);
                dispatch(next);
            }
        }
	}
