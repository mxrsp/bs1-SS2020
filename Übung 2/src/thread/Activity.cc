
/*
 * Activity:
 * Diese Klasse implementiert kooperative aktive Objekte
 * fuer Co-Stubs.
 *
 * Anmerkung:
 * Im Gegensatz zur Coroutine wird eine
 * Instanz der Klasse Activity von einem Scheduler verwaltet.
 * Ein explizites Umschalten zu einer anderen Coroutine
 * wird damit hinfaellig.
 */

#include "thread/Activity.h"
#include "thread/ActivityScheduler.h"

	/* Aufsetzen eines Threads, der initiale Zustand ist "Blocked",
	 * da der Thread erst laufen darf, wenn der spezielle Konstruktor
	 * der abgeleiteten Klasse abgearbeitet ist. Die Aktivierung
	 * erfolgt von der abgeleiteten Klasse mittels "wakeup".
	*/
	Activity::Activity(void* tos) : Coroutine(tos), state(BLOCKED) {
	}

	/* Verpacken des aktuellen Kontrollflusses als Thread.
	 * Wird nur für den Hauptkontrollfluss "main" benötigt.
	 * Es wird hier kein Stack initialisiert.
	 * Beachte das Activity wegen der Vererbungsbeziehung von
	 * Coroutine abstrakt ist. Bei Bedarf muss "body" direkt
	 * aufgerufen werden.
	 */
	Activity::Activity() : Coroutine(), state(BLOCKED) {
        this -> state = READY;
        scheduler = ActivityScheduler();
        out.println("Wir sind im Konstruktor von Activity angekommen");
        for (int i = 0; i < 15000000; i++) {}
        
        scheduler.start(this);
        scheduler.schedule(this);
	}

	/* Im Destruktor muss ein explizites Terminieren dieser Aktivitaet erfolgen.
	 * Das muss geschehen, da aufgrund der Aufrufreihenfolge von
	 * Destruktoren bereits der abgeleitete Teil des Activity-Objekts zerstoert
	 * wurde und diese Aktivitaet daher keine Laufzeit mehr erhalten darf.
	 * Das Warten auf die Beendigung (mittels join()) muss im Destruktor der
	 * von Activity am weitesten abgeleiteten Klasse erfolgen.
	 */
	Activity::~Activity() {
        this -> exit();
	}
	
	void Activity :: operator delete (void* p, unsigned int i) {
        // hier muss vielleicht irgendwas passieren
    }

	/* Veranlasst den Scheduler, diese Aktivitaet zu suspendieren.
	 */
	void Activity::sleep() {
	
        
        if (this->isRunning()) {
            scheduler.suspend();
        } else {
            this->state = BLOCKED;
            //scheduler.remove(this); //wird aus der rdy list entfernt
        }
    }

	/* Veranlasst den Scheduler, diese Aktivitaet aufzuwecken.
	 */
	void Activity::wakeup() {
        
        out.println("wakeup in Activity wurde erreicht");
        for (int i = 0; i < 15000000; i++) {}
        
        if (this -> isBlocked()) {
            out.println("Zustand blockiert in Activity");
            this -> state = READY;
            scheduler.schedule((Schedulable*)this);
        } else {
             out.println("jetzt passiert gar nichts in wakeup in Activity");
        for (int i = 0; i < 40000000; i++) {}   
        }
	}

	/* Diese Aktivitaet gibt die CPU vorruebergehend ab.
	 */
	void Activity::yield() {
		
        out.println("Wir sind in yield in Activity angekommen");
        
        for (int i = 0; i < 15000000; i++) {}
        scheduler.reschedule();
	}

	/* Diese Aktivitaet wird terminiert. Hier muss eine eventuell
	 * auf die Beendigung wartende Aktivität geweckt werden.
	 */
	void Activity::exit() {
        
        out.println("exit in Activity wurde erreicht");
	
        if (sleepingProcess != 0) {
            Activity* wakeupedProcess = sleepingProcess;
            sleepingProcess = 0;
            wakeupedProcess -> wakeup();
        }
        
        scheduler.kill(this);
	}

	/* Der aktuelle Prozess wird solange schlafen gelegt, bis der
	 * Prozess auf dem join aufgerufen wird beendet ist. Das
	 * Wecken des wartenden Prozesses übernimmt exit.
	 */
	void Activity::join() {
        
        out.println("join in Activity wurde erreicht");
        for (int i = 0; i < 70000000; i++) {}
        
        Activity* currentProcess = (Activity*)scheduler.active();
        sleepingProcess = currentProcess;
        
        if (this->isZombie()) {
            scheduler.suspend();
        } else {
            currentProcess -> sleep();
        }
		
	}
