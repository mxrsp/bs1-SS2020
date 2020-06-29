
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
        int ret = this -> output.write(data,size);
        return (ret);
        
        // return (this -> output.write(data,size));
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
        
        while ((index < size) && (!(puffer == '\n'))) {
            puffer = this -> read();
            
            // out.print(puffer);
            output.write(puffer);
            data[index] = puffer;
            
            // puffer = data[index];
            index++;
            // for (int i = 0; i < 10000000; i++);
        }
        
        return index;
    }

	/** 	Liefert das n�chste Zeichen aus dem Eingabepuffer zur�ck.
	 */
	char Console :: read() {
        char puffer;
        
        puffer = input.read(&puffer, 1);
        
        return puffer;
    }

