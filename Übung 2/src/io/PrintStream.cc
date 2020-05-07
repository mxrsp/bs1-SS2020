#include "io/PrintStream.h"
#include "io/OutputChannel.h"

/*
 * PrintStream:	Diese Klasse ist aehnlich der Java-PrintStream Klasse
 *		Sie konvertiert u.A. numerische Werte in sichtbare Zeichen
 *		und gibt Sie auf dem im Konstruktor spezifizierten
 *		Ausgabekanal aus.
 *		Daraus ergeben sich 2 Teilaufgaben:
 *
 *		1. Die Feststellung der Ziffern einer Zahl
 *		2. Die Umwandlung der Ziffern in darstellbare Zeichen
 *
 *		Man beachte, dass diese Klasse unabhaengig
 *		von dem tatsaechlich verwendeten Ausgabekanal arbeitet.
 *
 *		Anmerkung: Diese Klasse werden wir spaeter noch in
 *		C++ konforme Ausgabe umwandeln.
 */


	PrintStream::PrintStream(OutputChannel* chan): channel(*chan) {
    }
    
    
	PrintStream::PrintStream(OutputChannel& chan): channel(chan) {
    }

    	// Ausgabe eines mit einem NULL-Byte terminierten Strings
	void PrintStream::print(const char* str) {
        int i = 0;
        char start = str[0];
        
        while (start != 0) {    // solange kein "Nullpointer"
            i++;                // Größe wird inkrementiert
            start = str[i];     
        }
        
        this -> channel.write(str, i); // Ausgabe des Strings
    }
    
	void PrintStream::print(char ch) {
        this -> channel.write(ch);
    }

	// Ausgabe eines Strings mit anschliessendem Zeilenvorschub
	void PrintStream::println(const char* str){
        this -> print(str);
        this -> println();      // Zeilenumbruch
    }

	// Zeilenvorschub
	void PrintStream::println() {
        this -> channel.write("\n", 1); // "\n" hat die Länge 1
    }

	// numerische Werte werden zur Basis 'base' Ausgegeben
	// implementiere die Basen 2, 10 und 16
	void PrintStream::print(int x, int base) {
        
        if (x < 0) {
                x = x * (-1);
                this -> print('-');     // Minus wird ausgegeben, da Zahl negativ ist
        }
        
        this -> print((unsigned)x, base);
        
    }
    
	void PrintStream::print(unsigned x, int base) {
        
        if (base == DECIMAL){
            
            ausgabeVonDECundBIN(x, base);
        
        } else if (base == BINARY) {
            
            this -> print("0b");
            
            ausgabeVonDECundBIN(x , base);
            
        } else if (base == HEX) {
            
            this -> print("0x");
            
            ausgabeVonHex(x, base);
        }
    }
    
    void PrintStream::ausgabeVonDECundBIN(unsigned eingabe, int base) {
            int array [33];     // maximale größe = 33 Bits
            
            int size = 0;
            
            if (base == 10) {
                if (eingabe == 0) {
                    ausgabe(0);
                }
            }
            
            while (eingabe > 0) {
                int ergebnis = eingabe % base;     
                array[size] = ergebnis;         // eingabe mod 2 in array gespeichert
                eingabe = eingabe / base;       
                size++;                     // stelle im Aray wird erhöht
            }
            
            for (int i = 1; i < size+1; i++) {
                int output = array[size-i];     // array wird rückwärts ausgegeben
                ausgabe(output);
            }
    
    }
    
    void PrintStream::ausgabeVonHex(int eingabe, int base) {
        const char* output = "0123456789ABCDEF";        // alle Möglichkeiten für HexZahlen
            
            while (eingabe >= base) {
                int i = 1;
                int ergebnis = getTeiler(eingabe, base, i);     // i =  größter Exponent
                this -> print(output[ergebnis]);                // ausgabe 
                eingabe = eingabe % (potenz(base,i));           // eingabe wird auf Rest verringert
            }
            
            if (eingabe < base) {                   // wenn Eingabe kleiner als 16
                this -> print(output[eingabe]);     // einfach ausgeben
            }
    }
    
    // größtmöglicher Teiler für HexZahlen wird gesucht und in i geschrieben
    int PrintStream::getTeiler(int eingabe, int base, int& i) {
        int zwischenspeicher = eingabe;
        while (eingabe > 0) {
            eingabe = eingabe / (potenz(base,i));
            if (eingabe < 16) {
                return eingabe;
            } else {
                i++;
                eingabe = zwischenspeicher;
            }
        }
        return 0;
    }
    
    // ausgeben von einem einstelligen int
    void PrintStream::ausgabe(int x) {
        if (x < 10) {
            char c = '0' + x;
            this -> print(c);
        }
    }
    // gibt a^b zurück
    int PrintStream::potenz(unsigned a, int b) {
        if (b == 0) {
            return 1;
        } else {
            return a * (potenz(a,(b-1)));
        }
    }
    
	// Zeigertypen werden immer zur Basis 16 ausgegeben!
	void PrintStream::print(void* p) {
        
        unsigned ausgabe = (unsigned)p;
        
        this -> print(ausgabe, HEX);
    }
