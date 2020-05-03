#include "io/OutputChannel.h"
#include "device/CgaScreen.h"
#include "device/CgaAttr.h"
#include "device/CgaChannel.h"

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
        
        for (int i = 0; i < size; i++) {
            char outputChar = data[i];
            int column, row = 0;    // Festlegen von Spalte und Reihe
            
            if (outputChar == '\n') {                 
               this -> getCursor(column, row);      // get Cursorposition
               this -> setCursor(0, row + 1);       // wenn \n erkannt -> ganz links neue Zeile                                  
            } else if (outputChar == '\r') {
               this -> setCursor(0, row);           // wenn \r erkannt -> ganz links der aktuellen Zeile
               this -> getCursor(column, row);      // get Cursorposition
            } else {           
               this -> show(outputChar);
            }
        }
        
        return size;
    }

	// Bluescreen mit eigener Fehlermeldung
	void CgaChannel::blueScreen(const char* error) {
        
        CgaAttr attr = CgaAttr(); 
        
        attr.setBackground(CgaAttr :: BLUE);
        attr.setForeground(CgaAttr :: WHITE);
        attr.setBlinkState(false);
        
        for (int i = 0; i < 5; i++) {
            this -> show(error[i], attr);
        }
    }


 
