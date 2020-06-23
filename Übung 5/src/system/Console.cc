
#include"system/Console.h"

/**
 *  Console:	Die Systemkonsole
 */

	Console :: Console(InputChannel& input, OutputChannel& output)
    : input(input), output(output), semaphore(Semaphore()){
        
    }

	/** 	Konsole reservieren
	 */
	void Console :: attach() {
        semaphore.wait();
    }

	/** 	Konsole wieder freigeben
	 */
	void Console :: detach() {
        semaphore.signal();
    }

	/** 	Daten auf der Console ausgeben
	 */
	int Console ::  write(const char* data, int size) {
        return (this -> output.write(data,size));
    }

	/** 	Jedes von der Tastatur eingelesene Zeichen
	 * 	soll auf dem Bildschirm dargestellt werden (Echo Funktion!)
	 * 	Wenn ein '\n' erkannt wurde oder bereits "size" Zeichen
	 *	gelesen wurden, ist eine Zeile zuende und read() kehrt zurueck.
	 *	Alle gelesenen Ascii-zeichen sind in den Puffer einzutragen
	 *	und zaehlen als gueltiges Zeichen!
	 */
	int Console :: read(char* data, int size) {
        int index = 0;
        
        char puffer = 0;
        
        while ((index < size) && (puffer != '\n')) {
            puffer = data[index];
            index++;
        }
        
        return index;
        
        // return (this -> write(data, index));
    }

	/** 	Liefert das n�chste Zeichen aus dem Eingabepuffer zur�ck.
	 */
	char Console :: read() {
        char puffer;
        
        puffer = input.read(&puffer, 1);
        
        return puffer;
    }

