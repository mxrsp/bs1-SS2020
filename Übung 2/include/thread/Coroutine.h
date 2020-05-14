#ifndef Coroutine_h
#define Coroutine_h

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

#include "io/PrintStream.h"

extern PrintStream out;


/* Diese Deklaration verweist auf die von Euch zu
 * implementierende Assemblerprozedur "switchContext".
 */
extern "C" {
	void switchContext(void*& from, void*& to);
}
/* switchContext hat die Aufgabe, die Kontrolle
 * vom Stack der Coroutine "from" auf den Stack der
 * Coroutine "to" zu wechseln und damit einen Kontrolltransfer
 * zu vollziehen.
 *
 * Hinweis: Am einfachsten ist es, einfach die betreffenden Register
 * auf den aktuellen Stack zu retten (pushen) und den Stackpointer (esp)
 * danach an der Adresse auf die "from" verweist, zu sichern.
 * Nachdem das geschehen ist, wird der Stack gewechselt,
 * indem man den neuen Stackpointerwert von der Adresse
 * auf die "to" zeigt in das Stackpointerregister esp laedt.
 * Dadurch haben wir den Stack gewechselt und wir koennen nun
 * einfach alle auf diesem Stack geretteten Register wiederherstellen
 * (in umgekehrter Reihenfolge poppen). Zum Schluss fuehren
 * wir einfach eine "ret" Instruktion aus, die dazu fuehrt,
 * dass die Coroutine "to" an der Stelle weiterlaeuft,
 * an der sie das letzte mal "switchContext" aufgerufen hat.
 * Für Coroutinen die zum ersten mal aktiviert werden, muss
 * deshalb ein Stackframe existieren, was gleich aussieht mit
 * dem einer Coroutine die "switchContext" aufgerufen hat.
 */


class Coroutine {
public:

	struct setStack{
		unsigned ebx_register = 0;
		unsigned edi_register = 0;
		unsigned esi_register = 0;
		void* ebp_register = 0;
		void* startadresse;
		void* returnadresse = 0;
		Coroutine *routine;
	};
	/* Aufsetzen einer neuen Coroutine.
	*/
	Coroutine(void* tos = 0)
	{
        out.println("Konstruktor wird in Coroutine aufgerufen");
        
		setup(tos);
	}

	/* Kontrolltransfer von dieser Coroutine zu "next"
	 * Die eigentliche Arbeit erledigt "switchContext"
	 */
	void resume(Coroutine* next)
	{
        out.println("resume wird aufgerufen in Coroutine");
        
        if (next == 0) {
        out.println("next ist Null in Coroutine");
        }
        
        if (this->sp == 0) {
        out.println("Stackpointer ist Null in Coroutine");
        }
        
        for (int i = 0; i < 30000000; i++) {}
		switchContext(this->sp, next->sp);
		
        for (int i = 0; i < 15000000; i++) {}
        out.println("resume ist nun fertig in Coroutine");
	}

	/* Dies ist der Rumpf der Coroutine
	 * und muss in abgeleiteten Klassen definiert werden.
	 */
	virtual void body() = 0;

	/* Diese Methode wird aufgerufen
	 * wenn der Rumpf unserer Coroutine beendet ist
	 * und muss in abgeleiteten Klassen definiert werden.
	 */
	virtual void exit() = 0;

private:

	/* Diese Funktion hat nur die Aufgabe
	 * den Rumpf der uebergebenen Coroutine aufzurufen
	 * und nach der Rueckkehr exit() aufzurufen,
	 * um die Termination des Rumpfes bekanntzugeben.
	 * Diese Prozedur dient so als eine Bruecke zwischen der
	 * nicht objektorientierten und der objektorientierten Welt
	 * Beachte, das "startup" als "static deklariert ist
	 * und deshalb keinen impliziten "this"-Zeiger uebergeben bekommt.
	 */
	static void startup(Coroutine* obj);

	/* Aufsetzen einer neuen Coroutine.
	 * Der Parameter "tos" (top of stack) ist der
	 * initiale Stackpointerwert fuer die neue Coroutine
	 * ACHTUNG: tos kann NULL sein (siehe Constructor)!
	 */
	void setup(void* tos);

	void* sp; // Der gerettete Stackpointer

	unsigned ebx;
	unsigned edi;
	unsigned esi;
	void* ebp;
	void* startadresse;
	void* returnadresse;
	Coroutine *routine;

};

#endif
