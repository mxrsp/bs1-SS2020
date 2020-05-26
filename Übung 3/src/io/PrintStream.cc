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
             
            if (x == 0) {
                    ausgabe(0);
            }
            
            ausgabeVonDECundBIN(x, base);
        
        } else if (base == BINARY) {
            
            this -> print("0b");
            
            if (x == 0) {
                    ausgabe(0);
            }
            
            ausgabeVonDECundBIN(x , base);
            
        } else if (base == HEX) {
            
            this -> print("0x");
            
            if (x == 0) {
                    ausgabe(0);
            }
            
            ausgabeVonHex(x, base);
        } else {
            this -> println("Base not supported");
        }
    }
    
    void PrintStream::ausgabeVonDECundBIN(unsigned eingabe, int base) {
            int array [33];     // maximale größe = 33 Bits
            
            int index = 0;
            
            while (eingabe > 0) {
                int ergebnis = eingabe % base;     
                array[index] = ergebnis;         // eingabe mod 2 in array gespeichert
                eingabe = eingabe / base;       
                index++;                     // stelle im Aray wird erhöht
            }
            
            for (int i = 1; i < index+1; i++) {
                int output = array[index-i];     // array wird rückwärts ausgegeben
                ausgabe(output);
            }
    
    }
    
    void PrintStream::ausgabeVonHex(unsigned eingabe, int base) {
        const char* output = "0123456789ABCDEF";        // alle Möglichkeiten für HexZahlen
            
        char array[10];
        
        int index = 0;
        
            while (eingabe > 0) {
                int ergebnis = eingabe % base;
                array[index] =  output[ergebnis];
                eingabe = eingabe / base;
                index++;
            }
            
            for (int i = 1; i < index+1; i++) {
                char output = array[index-i];     // array wird rückwärts ausgegeben
                print(output);
            }       
    }
    
    // ausgeben von einem einstelligen int
    void PrintStream::ausgabe(int x) {
        if (x < 10) {
            char c = '0' + x;
            this -> print(c);
        }
    }
    
	// Zeigertypen werden immer zur Basis 16 ausgegeben!
	void PrintStream::print(void* p) {
        
        unsigned ausgabe = (unsigned)p;
        
        this -> print(ausgabe, HEX);
    }
    
    // PrintStream wartet eine Weile zu Debuggingzwecken
    void PrintStream::wait() {
        for (int i = 0; i < 20000000; i++) {}
    }
