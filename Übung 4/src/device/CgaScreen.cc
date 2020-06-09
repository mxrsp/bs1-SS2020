#include "device/CgaScreen.h"
#include "device/CgaAttr.h"
#include "device/CgaChar.h"
#include "io/IOPort.h"
#include "io/PrintStream.h"


/*
 * CgaScreen:	Diese Klasse ist der Softwareprototyp fuer den
 *		CGA-Bildschirm
 *		
 *      Hier soll es ausschliesslich um die Kontrolle der Hardware
 *      gehen. Komplexere Aufgaben koennen in den erbenden Klassen
 *      implementiert werden.
 */


    
	/*Standardattribute waehlen und Bildschirm loeschen
	 Wir erstellen einen CgaScreen. Diesem wird ein Standartattribut übergeben. Außerdem weisen wir IOPORT8 index die addresse des indexports zu. Außerdem wird dem data port die adresse des Datenports zugewiesen. Zusätzlich wird der screen gesetzt, der die Video ram addresse übergeben bekommt.
	*/
	CgaScreen::CgaScreen() : attr(), index(INDEXPORT), data(DATENPORT), screen((CgaChar*) VIDEO_RAM_ADRESS)
	{ 
        
        //wir setzen den cursor an die stelle (0,0) auf dem bildschirm
        setCursor(0, 0);
        
        //bildschirm wird gecleared
        clear();
    }
    

	/* Angegebene Attribute setzen und Bildschirm loeschen
        Wir erstellen einen CgaScreen. Diesem wird ein gegebenes atrribut übergeben, welches gesetzt wird. Außerdem weisen wir IOPORT8 index die addresse des indexports zu. Außerdem wird dem data port die adresse des Datenports zugewiesen. Zusätzlich wird der screen gesetzt, der die Video ram addresse übergeben bekommt.
	*/
	CgaScreen::CgaScreen(CgaAttr attr) : attr(attr), index(INDEXPORT), data(DATENPORT), screen((CgaChar*) VIDEO_RAM_ADRESS)
    {  
        //wir setzen den cursor an die stelle (0,0) auf dem bildschirm
        setCursor(0, 0);
        
         //bildschirm wird gecleared
        clear();
    }

	// Loeschen des Bildschirms
	void CgaScreen::clear () {
       
        screen = (CgaChar*) VIDEO_RAM_ADRESS;
        
        //erstellt einen cgachar mit standartattributen und setzt diese leer
        
        CgaChar leer = CgaChar();
        leer.setChar(' ');
        
        //zeigt die unterste zeile als leere zeile an
        for (int i = 0; i < ROWS*COLUMNS; i++) {
            screen[i] = leer;
        }
        
        setCursor(0,0);
    }

	// Verschieben des Bildschirms um eine Zeile
	void CgaScreen::scroll() {
        
        //setzen den screen auf die adresse des videorams
        int currentPos;
		int nextPos;
        
		//setCursor(0,0);
        currentPos = 0;
        nextPos = currentPos + COLUMNS;
        
		
        //wir verschieben jede zeile um eine zeile nach oben
        for (int i = 0; i < ((ROWS - 1)*COLUMNS); i++){
            screen[i] = screen[nextPos];
            nextPos += 1;
        }
        
        //erstellt einen cgachar mit standartattributen und setzt diese leer
        
        CgaChar leer = CgaChar();
        leer.setAttr(attr);
        leer.setChar(' ');
        
        //zeigt die unterste zeile als leere zeile an
        for (int i = (ROWS-1)*COLUMNS; i < ROWS*COLUMNS; i++) {
            screen[i] = leer;
        }
       
		setCursor(0, 24);
    }

    // Setzen Cursor durch einen index
    //setzt den cursor an die byte stelle (0 - 2000)
    void CgaScreen::setCursorInt(int i) {
        
        int x = i / COLUMNS;
        int y = i % COLUMNS;
        
        setCursor(y,x);
    }
    
	// Setzen/Lesen des HW-Cursors
	void CgaScreen::setCursor(int column, int row) {
        
        //die position ergibt sichaus der anzahl der zeilen * spalten + spalten
        unsigned position = row * COLUMNS + column;
        
        //setzt den index auf die stelle des registers low(14)
        this -> index.write(LOW);
        //schreibt den wert von position an die stelle, auf die index zeigt
        this -> data.write(position);
        //setzt den index auf die stelle des registers high(15)
        this -> index.write(HIGH);
        //schreibt den wert von position an die stelle, auf die index zeigt um 8 verschoben
        this -> data.write((position >> 8));
        
    }
    //gibt die stelle(bytes 0 - 2000) zurück, an der sich der cursor momentan befindet
    int CgaScreen::getCursorInt() {
        CgaChar* ursprungsadresse = (CgaChar*) VIDEO_RAM_ADRESS;
        
        int stelle = screen - ursprungsadresse;
        
        return stelle;
    }
    
    //gibt die stelle zurück, wo sich der cursor momentan befindet
	void CgaScreen::getCursor(int& column, int& row) {
        
        //setzen high und low auf 0
        int high, low = 0;
        
		//deklarieren stelle
        unsigned stelle;
        
        //setzen den index auf das low register
        this -> index.write(LOW);
        //speichern auf low die daten, die auf dem low register stehen
        low = data.read();        
        //setzen den index auf das high register
        this -> index.write(HIGH);
        //speichern auf high die daten, die auf dem high register stehen
        high = data.read();
        
        //verschieben high um 8 bits nach links
        high = high << 8;  
        
        //stelle ergibt sich aus der oder verknüpfung von high und low
        stelle = high | low; // finaler Positionsindex
        
        //die reihe ergibt sich aus der stelle / zeilen
        row = stelle / COLUMNS;
        
        //spalte ergibt sich aus dem rest von stelle / zeilen
        column = stelle % COLUMNS;
    }

	// Anzeigen von c an aktueller Cursorposition
    	// Darstellung mit angegebenen Bildschirmattributen
	void CgaScreen::show(char ch, const CgaAttr& attr) {
        int column = 0;
        int row = 0;
        
        //geben die aktulle cursor position zurück

        getCursor(column, row);
        //wenn mehr spalten als möglich, dann wird in die neue zeile an stelle 0 gesprungen
        

        if (column >= COLUMNS) {
            
            setCursor(0, row + 1);
            getCursor(column, row);
            
            if (row >= ROWS) {
                scroll();
                getCursor(column, row);
            }
        }

        if (row >= ROWS) {
            scroll();
            getCursor(column, row);

        }
        
        //wenn mehr zeilen als möglich, wird gescrollt

        int stelle = row * COLUMNS + column;

		//setzen attribut und char
        screen[stelle].setChar(ch);
        screen[stelle].setAttr(attr);        
        
		//setzen cursor an nächste spalten position
        setCursor(column+1, row);
    }

	// Anzeigen von c an aktueller Cursorposition
    // Darstellung mit aktuellen Bildschirmattributen
	void CgaScreen::show(char ch)	{
        show(ch, this -> attr);
	}
