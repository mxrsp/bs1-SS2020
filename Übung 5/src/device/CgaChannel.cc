#include "io/OutputChannel.h"
#include "device/CgaScreen.h"
#include "device/CgaAttr.h"
#include "device/CgaChannel.h"
#include "io/PrintStream.h"

extern PrintStream out;

/*
 * CgaChannel:	Diese Klasse implementiert einen Ausgabekanal
 *		fuer den CGA-Bildschirm
 *
 *		Sie *muss* die 'write' Methode implementieren,
 *		und alle write() Aufrufe geeignet auf den CgaScreen abbilden.
 *
 *      Man beachte:
 *		Unter den auszugebenden Zeichen befinden
 *		sich sogenannte Steuerzeichen, die geeignet
 *		zu interpretieren sind.
 *
 *		Es reicht fuer diese Uebung, wenn Ihr die
 *		Steuerzeichen '\n' (newline, NL) und '\r' (Carriage Return, CR)
 *		interpretiert.
 *		Bei CR ist der Cursor auf den Anfang der aktuellen Zeile
 *		zu setzen. Bei NL wird der Cursor auf den Anfang
 *		der naechsten Zeile gesetzt.
 */


	// Ausgabekanal mit Standardattributen
	CgaChannel::CgaChannel() : CgaScreen() 
    {   
    }

	// Ausgabekanal mit spezifischen Attributen
	CgaChannel::CgaChannel(const CgaAttr& attr): CgaScreen(attr)
    {        
    }

	// Die von OutputChannel deklarierte Ausgaberoutine
	int CgaChannel::write(const char* data, int size) {
        
        int column, row;    // Festlegen von Spalte und Reihe
        getCursor(column, row);      // get Cursorposition
        
        for (int i = 0; i < size; i++) {
            
            if (data[i] == '\n') {                 
               setCursor(0, row + 1);       // wenn \n erkannt -> ganz links neue Zeile                                  
            } else if (data[i] == '\r') {
               setCursor(0, row);           // wenn \r erkannt -> ganz links der aktuellen Zeile
            } else {
               this -> show(data[i]);
            }
            
            getCursor(column,row);     // Cursor nach Aktion aktualisieren
        }
        
        return size;
    }

	// Bluescreen mit eigener Fehlermeldung
	void CgaChannel::blueScreen(const char* error) {
        
        CgaScreen :: clear();
        
        CgaAttr blue = CgaAttr(); 
        
        blue.setBackground(CgaAttr :: BLUE);
        blue.setForeground(CgaAttr :: WHITE);
        blue.setBlinkState(false);
        
        for (int i = 0; i < CgaScreen::ROWS * CgaScreen:: COLUMNS; i++) {
            screen[i].setAttr(blue);
            screen[i].setChar(' ');
        }
          
        int size = 0;
        
        while (error[size] != 0) {    // solange kein "Nullpointer"
            size++;                // Größe wird inkrementiert     
        }
        
        setCursor(2,2);
        
        this -> setAttr(blue);
        write(error, size);
        
        write("\n",1);   // Zeilenumbruch am Ende
    }


 
