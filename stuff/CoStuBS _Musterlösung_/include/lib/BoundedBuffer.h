#ifndef BoundedBuffer_h
#define BoundedBuffer_h

#include "lib/Queue.h"
#include "thread/ActivityScheduler.h"
/** Diese Klasse stellt einen begrenzten synchronisierten
 *  Puffer dar, welcher von Interruptbehandlungsroutinen
 *  gefüllt werden kann.
 *
 *  Die Klasse ist eine Templateklasse. Das bedeutet für euch
 *  erstmal nur, das ihr alle Methoden hier im Header implementieren
 *  müsst.
 */
template<typename T, unsigned size>
class BoundedBuffer {
public:

	BoundedBuffer() {

		count = 0;
		in = 0;
		out = 0;
		sleeping = 0;
	}

	/** Diese Methode wird vom Interrupthandler aufgerufen, um
	 *  ein etwas in den Puffer zu schreiben. Ist der Puffer voll,
	 *  werden die zu schreibenden Daten verworfen.
	 *  Prozesse die auf eine Eingabe warten müssen hier geweckt werden.
	 */
	void add(T& elem) {

		if (this->count < (int) size) {
			this->buffer[out] = elem;
			this->count++;
			this->out = (this->out+1)%size;

			if (out >= size) {
				out = 0;
			}

			if (!(this->sleeping == 0)) {
				Activity *x = this->sleeping;
				this->sleeping = 0;
				x->wakeup();

			}
		}

	}

	/** Diese Methode wird von Prozessen aufgerufen, um Daten aus dem
	 *  Puffer zu lesen. Ist dieser leer wird der lesende Prozess schlafen
	 *  gelegt. Achtet hier besonders auf die Synchronisierung.
	 */
	T get() {



		if (this->count == 0) {
			this->sleeping = (Activity *) scheduler.active();

			scheduler.suspend();
		}
		this->in= (this->in+1)%size;
		this->count--;

		if (this->in != 0) {
			this->in = 0;
			return this->buffer[this->in - 1];

		} else {
			return this->buffer[size - 1];
		}

	}

	bool isEmpty(){
		return this->count == 0;
	}

private:
	T buffer[size];
	unsigned count;
	unsigned in;
	unsigned out;
	Activity *sleeping;
};

#endif

