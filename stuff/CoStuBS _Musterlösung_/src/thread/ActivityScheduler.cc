/*
 * ActivityScheduler.h
 *
 *  Created on: 14.05.2019
 *      Author: Tom
 */
#include "thread/ActivityScheduler.h"
#include "io/PrintStream.h"
#include "interrupts/IntLock.h"
#include "device/Clock.h"
#include "device/CPU.h"
#include "sync/KernelLock.h"
extern CPU cpu;
extern Clock clock;
/* Initialisieren der ersten Aktivität, des Schedulers
 * und des Dispatchers.
 * Wird nur einmal aufgerufen.
 */
void ActivityScheduler::start(Activity* act) {


	act->changeTo(Activity::RUNNING);	//Prozess starten
	init((Coroutine *)act);					//neuen Prozess initialisieren
	isblocked = false;
}

/* Suspendieren des aktiven Prozesses
 * Der korrekte Ausfuehrungszustand ist zu setzen
 * und danach der naechste lauffaehige Prozess zu aktivieren.
 */
void ActivityScheduler::suspend() {

	Activity *x = (Activity *) this->active();
	x->changeTo(Activity::BLOCKED);
	this->reschedule();

}

/* Explizites Terminieren des angegebenen Prozesses
 * Der Prozesszustand ist korrekt zu setzen
 * und der Prozess aus der Ready-Liste des Schedulers
 * zu entfernen. Falls der aktive Prozess zerstoert wird,
 * ist dem naechsten lauffaehigen Prozess die CPU
 * zuzuteilen.
 */
void ActivityScheduler::kill(Activity *act) {

	act->changeTo(Activity::ZOMBIE);
	if(this->active() == act){
		this->reschedule();
	}else{
	this->remove((Schedulable *)act);

	}
}

/* Terminieren des aktiven Prozesses,
 * und Wechsel zum naechsten lauffaehigen Prozess
 */
void ActivityScheduler::exit() {
	KernelLock lock;
	Activity *x = (Activity *) this->active();
	x->changeTo(Activity::ZOMBIE);
	this->reschedule();

}

//startet neuen Prozess
void ActivityScheduler::activate(Schedulable *to) {

	if(this->isblocked){
		return;
	}
	Activity *act = (Activity *) this->active();

	if (to == 0) {
		if (act->isBlocked() == false || act->isZombie()) {							//wenn kein Prozess läuft
			while (to == 0) {
				this->isblocked = true;
				monitor.leave();
				cpu.halt();
				monitor.enter();
				to = (Activity*) this->readylist.dequeue();		//suche neuen

			}
			this->isblocked = false;
			if(to != 0){
				((Activity *) to )->changeTo(Activity :: RUNNING);
				dispatch((Activity *)to);
			}

		}
	} else {
		if (!(act->isBlocked()) && !(act->isZombie()) && (act->isRunning())) {					//wechsel zu neuem Prozess
			act->changeTo(Activity::READY);
			scheduler.schedule((Schedulable *)act);
		}



		((Activity *) to )->changeTo(Activity :: RUNNING);
		scheduler.dispatch((Activity *)to);
	}
}


void ActivityScheduler::wakeup(Activity *act) {

	if (act != 0 || (sizeof(this->readylist) > 0)) {

		act->changeTo(Activity::READY);
		schedule(act);

	}else{
		start(act);

	}

}


void ActivityScheduler :: checkslice(){

if(clock.ticks() == ((Activity*)this->active())->quantum()){
	clock.nullTicks();
	this->reschedule();




}

}
