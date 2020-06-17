#ifndef BoundedBuffer_h
#define BoundedBuffer_h

#include"thread/Activity.h"
#include"thread/ActivityScheduler.h"
#include"lib/Queue.h"
#include"interrupts/IntLock.h"

extern ActivityScheduler scheduler;

/** Diese Klasse stellt einen begrenzten synchronisierten
 *  Puffer dar, welcher von Interruptbehandlungsroutinen
 *  gefüllt werden kann.
 *
 *  Die Klasse ist eine Templateklasse. Das bedeutet für euch
 *  erstmal nur, das ihr alle Methoden hier im Header implementieren
 *  müsst.
 */
template<typename T,unsigned size>
class BoundedBuffer {
public:

	BoundedBuffer()
	{
        for (unsigned i = 0; i < size; i++) {
            this -> buffer[i] = T();
        }
        this -> inPointer = 0;
        this -> outPointer = 0;
	}

	/** Diese Methode wird vom Interrupthandler aufgerufen, um
	 *  ein etwas in den Puffer zu schreiben. Ist der Puffer voll,
	 *  werden die zu schreibenden Daten verworfen.
	 *  Prozesse die auf eine Eingabe warten müssen hier geweckt werden.
	 */
	void add(T& elem)
	{   
        while(keyboardListSize != 0) {
            Activity* rapunzel = (Activity*) keyboardList.dequeue();
            keyboardListSize--;
            rapunzel -> wakeup();
        }
        
        if (!bufferIsFull()){
            this -> buffer[inPointer] = elem;
            elemInBuffer++;
            incInPointer();
        }
    }

	/** Diese Methode wird von Prozessen aufgerufen, um Daten aus dem
	 *  Puffer zu lesen. Ist dieser leer wird der lesende Prozess schlafen
	 *  gelegt. Achtet hier besonders auf die Synchronisierung.
	 */
	T get()
	{
        IntLock lock;
        
        Activity* active = (Activity*) scheduler.active();
        
        if (bufferIsEmpty()) {
            keyboardList.enqueue(active);
            keyboardListSize++;
            scheduler.suspend();
        }
        
        T output = this -> buffer[outPointer];
        elemInBuffer--;
        incOutPointer();
        
        return output;
	}

private:
	T buffer[size];
    
    Queue keyboardList;
    int keyboardListSize = 0;
    
    // zeigt auf erstes freies Element im Array
    unsigned inPointer;
    
    // zeigt auf erstes belegtes Element im Array
    unsigned outPointer;
    
    unsigned elemInBuffer = 0;
    
    
	void incInPointer() {
        this -> inPointer = (this -> inPointer + 1) % size;
    }
    
    void incOutPointer() {
        this -> outPointer = (this -> outPointer + 1) % size;
    }
    
    bool bufferIsEmpty() {
        return (elemInBuffer == 0);
    }
    
    bool bufferIsFull() {
        return (elemInBuffer == size);
    }
};

#endif

