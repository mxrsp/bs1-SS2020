#include "sync/KernelSemaphore.h"


void KernelSemaphore :: wait(){
	//wenn kein Platz mehr warten
	if(this->counter <= 0){
		Activity* active = (Activity *) scheduler.active();
		this->queue.enqueue(active);
		active->sleep();
	}else{
		//ansonsten signalisieren das platz da ist
		this->counter--;
	}
}

void KernelSemaphore :: signal(){
	Activity* wait =(Activity*) this->queue.dequeue();
	if(wait == 0){

		this->counter++;
	}else{
		wait->wakeup();

	}
}
