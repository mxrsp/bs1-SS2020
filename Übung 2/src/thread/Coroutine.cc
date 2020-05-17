
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
        out.println("Coroutine startup wird aufgerufen");
        for (int i = 0; i < 30000000; i++) {}
        
		obj -> body();
        
        out.println("Der Body in Coroutine startup ist abgearbeitet");
        for (int i = 0; i < 30000000; i++) {}
		
		obj -> exit();
        
        out.println("Exit in Coroutine startup ist abgearbeitet");
        for (int i = 0; i < 30000000; i++) {}
	}

	/* Aufsetzen einer neuen Coroutine.
	 * Der Parameter "tos" (top of stack) ist der
	 * initiale Stackpointerwert fuer die neue Coroutine
	 * ACHTUNG: tos kann NULL sein (siehe Constructor)!
	 */
	void Coroutine::setup(void* tos) {
		
        // out.println("setup in Coroutine wird aufgerufen");
        
		//wenn top of the stack = NULL, nichts machen
// 		if(tos == 0) {
//             out.println("tos == 0 in Coroutine");
// 			sp = &tos;
// 			return;
// 		}
// 		ansonsten neuen stack erstellen
// 		else {
// 			out.println("tos != 0 in Coroutine");
// 			Coroutine::setStack *newStack = (Coroutine::setStack*) tos;
//             
// 			Coroutine *neueRoutine = this;
// 			void *startAdr = (Coroutine*)&startup;
// 			
// 			newStack -> startadresse = startAdr;
// 			newStack -> routine = neueRoutine;
// 			
// 			this -> sp = newStack;
// 			
// 			return;
// 		}
        
        // neue Variante von Vincent
        
        if (!(tos)==0) {
            
            out.println("Coroutine setup wird aufgerufen und tos ist belegt");
            for (int i = 0; i < 30000000; i++) {}
            Coroutine::setStack *newStack = (Coroutine::setStack*) tos;
            
            Coroutine *neueRoutine = this;
		
			newStack -> coroutine = startup;
			newStack -> routine = neueRoutine;
			
			this -> sp = newStack;
        }
			
        
	}
