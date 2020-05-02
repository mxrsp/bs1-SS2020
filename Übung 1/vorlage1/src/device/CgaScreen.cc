#include "device/CgaScreen.h"
#include "device/CgaAttr.h"
#include "device/CgaChar.h"
#include "io/IOPort.h"

/*
 * CgaScreen:	Diese Klasse ist der Softwareprototyp fuer den
 *		CGA-Bildschirm
 *		
 *      Hier soll es ausschliesslich um die Kontrolle der Hardware
 *      gehen. Komplexere Aufgaben koennen in den erbenden Klassen
 *      implementiert werden.
 */


    
	// Standardattribute waehlen und Bildschirm loeschen
	CgaScreen::CgaScreen() : index(INDEXPORT), data(DATENPORT), attr(), screen((CgaChar*) VIDEO_RAM_ADRESS)
	{
    }
    

	// Angegebene Attribute setzen und Bildschirm loeschen
	CgaScreen::CgaScreen(CgaAttr attr) : index(INDEXPORT), data(DATENPORT), attr(), screen((CgaChar*) VIDEO_RAM_ADRESS)
    {  
    }

	// Loeschen des Bildschirms
	void CgaScreen::clear () {
        
        // von oben links starten
        
        screen = (CgaChar*) VIDEO_RAM_ADRESS;
        
        for (int i = 0; i > COLUMNS * ROWS; i++) {
            (*(screen + i)).setAttr(attr);
            (*(screen + i)).setChar(' ');
        }
    }

	// Verschieben des Bildschirms um eine Zeile
	void CgaScreen::scroll() {
        screen = (CgaChar*) VIDEO_RAM_ADRESS;
        
        for (int i = 0; i < ((ROWS - 1)*COLUMNS); i++ ){
                
        }
    }

	// Setzen/Lesen des HW-Cursors
	void CgaScreen::setCursor(int column, int row) {
        
        this -> screen = (CgaChar*) VIDEO_RAM_ADRESS;
        
        int position = (row - 1) * COLUMNS + column;
        
        screen += position;
    }
    
	void CgaScreen::getCursor(int& column, int& row) {
        // Adresse von Screen - Ursprungsadresse von Screen
        // Differenz = Anzahl der Stelle
        // Stelle / 80 = Zeilenanzahl
        // Stelle mod 80 = Spaltenanzahl
    }

	// Anzeigen von c an aktueller Cursorposition
    	// Darstellung mit angegebenen Bildschirmattributen
	void CgaScreen::show(char ch, const CgaAttr& attr) {
    
    }

	// Anzeigen von c an aktueller Cursorposition
    	// Darstellung mit aktuellen Bildschirmattributen
	void CgaScreen::show2(char ch)	{
        show(ch, this -> attr);
	}



