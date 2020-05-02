/*
 * Coroutine.cc
 *
 *  Created on: 14.05.2019
 *      Author: Tom
 */
#include "thread/Coroutine.h"
/*Eine Coroutine muss alle anderen Coroutinen auch kennen
 Sonst sind es Prozeduren
 Jede Coroutine kennt ihren Nachfolger
 */
void Coroutine :: setup(void *tos) {

	/* Aufsetzen einer neuen Coroutine.
	 * Der Parameter "tos" (top of stack) ist der
	 * initiale Stackpointerwert fuer die neue Coroutine
	 * ACHTUNG: tos kann NULL sein (siehe Constructor)!
	 */
	if (tos != 0) {

		Coroutine::setups *set = (Coroutine::setups *) tos;

		//setzt 'set' auf erstes Element
		set = set - sizeof(setups);

		//initialisieren
		set->edi = 0;
		set->esi = 0;
		set->ebx = 0;
		set->basepointer = 0;
		set->start = &Coroutine::startup;
		set->jumpback = 0;
		set->rut = this;
		this->sp = set;


	}else{}
}

void Coroutine :: startup(Coroutine *obj){
	monitor.leave();
	obj->body();
	obj->exit();

}

