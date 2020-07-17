
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
        
        int i;
                
        char puffer = 0;
        
        for (i = 0; i < size; i++) {
            if (puffer == '\n') {
                return i;
            } else {
                puffer = this -> read();
                output.write(puffer);
                data[i] = puffer;
            }
        }
        
        return i;
        
    }

	/** 	Liefert das n�chste Zeichen aus dem Eingabepuffer zur�ck.
	 */
	char Console :: read() {
        char puffer;
        
        input.read(&puffer, 1);
        
        return puffer;
    }

