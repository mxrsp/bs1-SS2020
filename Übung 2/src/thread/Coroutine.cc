
#include "thread/Coroutine.h"

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
		//coroutine ruft die body methode auf in der main klasse
		obj -> body();
		
		//coroutine ruft exit auf
		obj -> exit();
	}

	/* Aufsetzen einer neuen Coroutine.
	 * Der Parameter "tos" (top of stack) ist der
	 * initiale Stackpointerwert fuer die neue Coroutine
	 * ACHTUNG: tos kann NULL sein (siehe Constructor)!
	 */
	void Coroutine::setup(void* tos) {
		
		//wenn nicht mainstack, dann neuen stack aufsetzen
        if (!(tos)==0) {
			
			//geben unserem neuen struct den tos pointer
            Coroutine::setUpCoroutine *setUp = (Coroutine::setUpCoroutine*) tos;
            
            Coroutine *neueRoutine = this;
			
			//returnadresse der coroutine wird auf startup gesetzt
			setUp -> coroutine = startup;
			setUp -> routine = neueRoutine;
			
			//stackpointer auf neuen stack zeigen lassen
			this -> sp = setUp;
        } else {
            sp = &tos;
        } 
	}
