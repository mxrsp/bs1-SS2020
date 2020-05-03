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
	CgaScreen::CgaScreen() : attr(), index(INDEXPORT), data(DATENPORT), screen((CgaChar*) VIDEO_RAM_ADRESS)
	{ 
        setCursor(0, 0);
        
        clear();
    }
    

	// Angegebene Attribute setzen und Bildschirm loeschen
	CgaScreen::CgaScreen(CgaAttr attr) : attr(attr), index(INDEXPORT), data(DATENPORT), screen((CgaChar*) VIDEO_RAM_ADRESS)
    {  
        setCursor(0, 0);
        
        clear();
    }

	// Loeschen des Bildschirms
	void CgaScreen::clear () {
        
        // von oben links starten
        
        screen = (CgaChar*) VIDEO_RAM_ADRESS;
        
        this -> attr.setBackground(CgaAttr::BLACK);
        
        for (int i = 0; i > COLUMNS * ROWS; i++) {
            screen[i].setAttr(attr);
            screen[i].setChar(' ');
            setCursorInt(i);
            show(screen[i].getChar(), screen[i].getAttr());
        }
        
        setCursor(0, 0);
    }

	// Verschieben des Bildschirms um eine Zeile
	void CgaScreen::scroll() {
        screen = (CgaChar*) VIDEO_RAM_ADRESS;
        
        CgaChar leer = CgaChar();
        leer.setAttr(CgaAttr());
        leer.setChar(' ');
        
        for (int i = 0; i < ((ROWS - 1)*COLUMNS); i++ ){
            screen[i] = screen[(i + COLUMNS)];
        }
        
        // Huhu             Hallo
        // Hallo            Tach
        // Tach             ---
        
        for (int i = (ROWS-1)*COLUMNS; i < ROWS*COLUMNS; i++) {
            screen[i] = leer;
        }
    }

    // Setzen Cursor durch einen int
    void CgaScreen::setCursorInt(int i) {
        
        int x = i / COLUMNS;
        int y = i % COLUMNS;
        
        setCursor(x,y);
    }
    
	// Setzen/Lesen des HW-Cursors
	void CgaScreen::setCursor(int column, int row) {
        
        this -> screen = (CgaChar*) VIDEO_RAM_ADRESS;
        
        int position = (row - 1) * COLUMNS + column;
        
        screen += position;
    }
    
    int CgaScreen::getCursorInt() {
        CgaChar* ursprungsadresse = (CgaChar*) VIDEO_RAM_ADRESS;
        
        int stelle = screen - ursprungsadresse;
        
        return stelle;
    }
    
	void CgaScreen::getCursor(int& column, int& row) {
        CgaChar* ursprungsadresse = (CgaChar*) VIDEO_RAM_ADRESS;
        
        int stelle = screen - ursprungsadresse;
        
        row = stelle / COLUMNS;
        
        column = stelle % COLUMNS;
    }

	// Anzeigen von c an aktueller Cursorposition
    	// Darstellung mit angegebenen Bildschirmattributen
	void CgaScreen::show(char ch, const CgaAttr& attr) {
        int column = 0;
        int row = 0;
        
        getCursor(column, row);
        
        if (column >= COLUMNS) {
            setCursor(0, row + 1);
        }
        
        if (row >= ROWS) {
            scroll();
        }
        
        CgaChar output = CgaChar();
        
        output.setAttr(attr);
        output.setChar(ch);
        
        screen[getCursorInt()] = output;
    }

	// Anzeigen von c an aktueller Cursorposition
    	// Darstellung mit aktuellen Bildschirmattributen
	void CgaScreen::show(char ch)	{
        show(ch, this -> attr);
	}
