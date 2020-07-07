
#include "thread/Coroutine.h"
#include "device/CPU.h"
#include "io/PrintStream.h"
#include "sync/Monitor.h"

extern CPU cpu;
extern PrintStream out;
extern Monitor monitor;

/*
 * Coroutine:
 * Diese Klasse implementiert Coroutinen, welche die Basis
 * für alle Arten von Prozessen in Co-Stubs sind.
 *
 *	Anmerkung: wir verwenden ein objektorientiertes
 *	Coroutinen-Modell, daher ist diese Klasse abstrakt.
 *	Eine Coroutine muss sich von dieser Klasse ableiten
 *	und eine "body" Methode definieren.
 *	Diese Methode ist dann gewissermassen die "main" Funktion
 *	fuer die Coroutine.
 *
 */

	/* Diese Funktion hat nur die Aufgabe
	 * den Rumpf der uebergebenen Coroutine aufzurufen
	 * und nach der Rueckkehr exit() aufzurufen,
	 * um die Termination des Rumpfes bekanntzugeben.
	 * Diese Prozedur dient so als eine Bruecke zwischen der
	 * nicht objektorientierten und der objektorientierten Welt
	 * Beachte, das "startup" als "static deklariert ist
	 * und deshalb keinen impliziten "this"-Zeiger uebergeben bekommt.
	 */
	void Coroutine::startup(Coroutine* obj) {
        
        // out.println("startUp in Coroutine wird aufgerufen ->");
        
        // cpu.enableInterrupts();
        
        monitor.leave();
        
        // while (1) {}
        
		obj -> body();
		// out.println("Exit in Coroutine wurde aufgerufen");
		obj -> exit();
	}

	/* Aufsetzen einer neuen Coroutine.
	 * Der Parameter "tos" (top of stack) ist der
	 * initiale Stackpointerwert fuer die neue Coroutine
	 * ACHTUNG: tos kann NULL sein (siehe Constructor)!
	 */
	void Coroutine::setup(void* tos) {
        
        if (!(tos)==0) {
            Coroutine::setUpCoroutine *setUp = (Coroutine::setUpCoroutine*) tos;
            
            setUp--;
            
            Coroutine *neueRoutine = this;
		
            // nirvana setzen
            setUp -> returnadresse = 0;
			setUp -> coroutine = startup;
			setUp -> routine = neueRoutine;
			
			this -> sp = setUp;
        } else {
            sp = &tos;
        }
	}
