#ifndef CgaScreen_h
#define CgaScreen_h
#include "CgaAttr.h"
#include "CgaChar.h"
#include "../io/IOPort.h"

/*
 * CgaScreen:	Diese Klasse ist der Softwareprototyp fuer den
 *		CGA-Bildschirm
 *		
 *      Hier soll es ausschliesslich um die Kontrolle der Hardware
 *      gehen. Komplexere Aufgaben koennen in den erbenden Klassen
 *      implementiert werden.
 */


class CgaScreen {
	private:

		// Die I/O-Ports des Grafikcontrollers
		enum Ports {
			IDX = 0x3d4,
			DAX = 0x3d5
		};

		// Die Kommandos zum Cursor setzen
		enum Cursor {
			LOW = 15,
			HIGH = 14 ,
			 CursorStart=0xb8000,
			 ROW=0 ,
			 COLUMN=0
		};

		// Die Adresse des Video RAMs
		enum Video {
			//START = 0xb8000,
			//END = 0xc8000
			startVideo = 0xb8000 ,
			end = startVideo + 4000
		};

	public:

		// Die Bildschirmdimensionen
		enum Screen {
			ROWS = 25,
			COLUMNS = 80,
			ALL = ROWS * COLUMNS
		};

		// Standardattribute waehlen und Bildschirm loeschen
		CgaScreen();


		// Angegebene Attribute setzen und Bildschirm loeschen
		explicit CgaScreen(CgaAttr attr);



			//mee
			/**
			for(int i=0; i< 25;i++){
							for (int k = 0; k < 80; k++){
								//setting every adress and its neighbour to 0 which means
								//no sign and black
								0 = &adress[i][k];
								attr.bg = &adress[i][k+1] ;

							}

						}


			 */



	// Loeschen des Bildschirms mit Attr
	void clear ();

	// Verschieben des Bildschirms um eine Zeile
	void scroll();

	// Setzen/Lesen der globalen Bildschirmattribute
	void setAttr(const CgaAttr& attr);


	void getAttr(CgaAttr& attr);

	// Setzen/Lesen des HW-Cursors
	void setCursor(int column, int row);
	void getCursor(int& column, int& row);


	// Anzeigen von c an aktueller Cursorposition
    	// Darstellung mit angegebenen Bildschirmattributen
	void show(char ch, const CgaAttr& attr);

	// Anzeigen von c an aktueller Cursorposition
    	// Darstellung mit aktuellen Bildschirmattributen
	void show(char ch);

	void setCursorNewLine();
	void setCursorBegin();


protected:
	IOPort8 ind;
	IOPort8 data;
	int cursorX;
	int cursorY;
	CgaAttr attribut;
	CgaChar *screen;
	unsigned int cursor_adress;

};


#endif
