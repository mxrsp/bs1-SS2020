/*
 * Activity.cc
 *
 *  Created on: 14.05.2019
 *      Author: Tom
 */

#include "thread/Activity.h"
#include "thread/ActivityScheduler.h"


	/* Aufsetzen eines Threads, der initiale Zustand ist "Blocked",
	 * da der Thread erst laufen darf, wenn der spezielle Konstruktor
	 * der abgeleiteten Klasse abgearbeitet ist. Die Aktivierung
	 * erfolgt von der abgeleiteten Klasse mittels "wakeup".
	*/
	Activity :: Activity(void* tos, int slices) : Schedulable(slices),Coroutine(tos),state(BLOCKED){


	}

	/* Verpacken des aktuellen Kontrollflusses als Thread.
	 * Wird nur für den Hauptkontrollfluss "main" benötigt.
	 * Es wird hier kein Stack initialisiert.
	 * Beachte das Activity wegen der Vererbungsbeziehung von
	 * Coroutine abstrakt ist. Bei Bedarf muss "body" direkt
	 * aufgerufen werden.
	 */
	Activity :: Activity(int slices) : Schedulable(slices),Coroutine(),state(BLOCKED){
		this->state = READY;
		scheduler.start(this);




	}

	/* Im Destruktor muss ein explizites Terminieren dieser Aktivitaet erfolgen.
	 * Das muss geschehen, da aufgrund der Aufrufreihenfolge von
	 * Destruktoren bereits der abgeleitete Teil des Activity-Objekts zerstoert
	 * wurde und diese Aktivitaet daher keine Laufzeit mehr erhalten darf.
	 * Das Warten auf die Beendigung (mittels join()) muss im Destruktor der
	 * von Activity am weitesten abgeleiteten Klasse erfolgen.
	 */
	Activity :: ~Activity(){

		this->exit();
	}


	/* Veranlasst den Scheduler, diese Aktivitaet zu suspendieren.
	 */
	void Activity :: sleep(){
		scheduler.suspend();
	}

	/* Veranlasst den Scheduler, diese Aktivitaet aufzuwecken.
	 */
	void Activity :: wakeup(){
		//es können nur Blockierte Activitys aufgeweckt werden
		if(this->isBlocked()){
		this->state = READY;
		scheduler.schedule((Schedulable *)this);
		}
	}

	/* Diese Aktivitaet gibt die CPU vorruebergehend ab.
	 */
	void Activity :: yield(){

		scheduler.reschedule();
	}

	/* Diese Aktivitaet wird terminiert. Hier muss eine eventuell
	 * auf die Beendigung wartende Aktivität geweckt werden.
	 */
	void Activity :: exit(){

		if(sleeper != 0){
			Activity* wakedup = sleeper;
			sleeper = 0;
			wakedup->wakeup();


		}
		scheduler.kill(this);
		//kommt nur hierhin wenn Prozess fertig -> Prozess beenden, neuen anfangen



	}

	/* Der aktuelle Prozess wird solange schlafen gelegt, bis der
	 * Prozess auf dem join aufgerufen wird beendet ist. Das
	 * Wecken des wartenden Prozesses übernimmt exit.
	 */
	void Activity :: join(){

		Activity *x = (Activity *)scheduler.active();
		sleeper = x;
		if(this->isZombie() || x== this){
			return;
		}else{
		x->sleep();
		}



	}




