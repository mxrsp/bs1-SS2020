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
        this -> channel.write("\n", 1);
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
            
            ausgabeVonDec((int)x, base);
        
        } else if (base == BINARY) {
            
            ausgabeVonBin(x , base);
            
        } else if (base == HEX) {
            
            ausgabeVonHex(x, base);
        }
    }
    
    void PrintStream::ausgabeVonDec(int eingabe, int base) {
        
        int laenge = getLaenge(eingabe);
        int schleife = laenge;
        int teiler;
        
        for (int i = 0; i < schleife; i++) {
                if (eingabe >= base) {
                    teiler = potenz(base, (laenge-1));
                    int outputChar = eingabe / teiler;
                    ausgabe(outputChar);
                    eingabe = eingabe % teiler;
                    laenge--;
                } else {
                    this -> ausgabe(eingabe);
                }
        }
    }
    
    void PrintStream::ausgabeVonBin(unsigned eingabe, int base) {
            int array [33];
            
            int size = 0;
            
            this -> print("0b");
            
            while (eingabe > 0) {
                int ergebnis = eingabe % base;
                array[size] = ergebnis;
                eingabe = eingabe / base;
                size++;
            }
            
            for (int i = 1; i < size+1; i++) {
                int output = array[size-i];
                ausgabe(output);
            }
    
    }
    
    void PrintStream::ausgabeVonHex(int eingabe, int base) {
        const char* output = "0123456789ABCDEF";
        
         this -> print("0x");
            
            while (eingabe >= base) {
                int i = 1;
                int ergebnis = getTeiler(eingabe, base, i);
                this -> print(output[ergebnis]);
                eingabe = eingabe % (potenz(base,i));
            }
            
            if (eingabe < base) {
                this -> print(output[eingabe]);
            }
    }
    
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
    
    // ausgeben von einem einzigen int
    void PrintStream::ausgabe(int x) {
        if (x < 10) {
            char c = '0' + x;
            this -> print(c);
        }
    }
    
    int PrintStream::potenz(unsigned a, int b) {
        if (b == 0) {
            return 1;
        } else {
            return a * (potenz(a,(b-1)));
        }
    }
    
    int PrintStream::getLaenge(int x) {
        int stellen = 10;
        int zaehler = 1;
        
        while (x > stellen) {
            stellen = stellen * 10;
            zaehler++;
        }
        
        return zaehler;    
    }
    
	// Zeigertypen werden immer zur Basis 16 ausgegeben!
	void PrintStream::print(void* p) {
        
        unsigned ausgabe = (unsigned)p;
        
        this -> print(ausgabe, HEX);
    }

    
 
