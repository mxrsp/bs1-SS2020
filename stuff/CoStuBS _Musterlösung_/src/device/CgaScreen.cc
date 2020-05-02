#include "device/CgaAttr.h"
#include "device/CgaChar.h"
#include "io/IOPort.h"
#include "device/CgaScreen.h"
/*
 * CgaScreen:	Diese Klasse ist der Softwareprototyp fuer den
 *		CGA-Bildschirm
 *
 *      Hier soll es ausschliesslich um die Kontrolle der Hardware
 *      gehen. Komplexere Aufgaben koennen in den erbenden Klassen
 *      implementiert werden.
 */

CgaScreen::CgaScreen(CgaAttr attr) :
		ind(this->IDX), data(this->DAX), attribut(attr), screen(
				(CgaChar *) this->startVideo) {
	this->cursorX = 0;
	this->cursorY = 0;
	this->cursor_adress = startVideo;

}

CgaScreen::CgaScreen() :
		ind(this->IDX), data(this->DAX), attribut(), screen(
				(CgaChar *) this->startVideo) {
	this->cursorX = 0;
	this->cursorY = 0;
	this->cursor_adress = startVideo;

}

// Loeschen des Bildschirms
void CgaScreen::clear() {

	CgaAttr old = this->attribut;


	CgaAttr x = CgaAttr();
	x.setBackground(CgaAttr::BLACK);
	this->attribut = x;

	for (int k = 0; k < ALL; k++) {
		this->screen[k].setChar(' ');
		this->screen[k].setAttr(attribut);
		this->cursor_adress = startVideo + k;

		//Set cursor in screen


		show(this->screen[k].getChar(), this->screen[k].getAttr());
	}

	//um altes attribut wieder zu laden
	this->attribut = old;

	setCursorBegin();
}

//neue seite für bildschirm
void CgaScreen::scroll() {

    //jede Zeile kopiert die Zeile direkt unter ihr
    int position;
    int positionNext;
    for (int i = 0; i < (ROWS-1); i++)
    {
    	this->cursorX = i;
        for (int j = 0; j < COLUMNS; j++)
        {
        	this->cursorY = j;
            position = i * COLUMNS + j;               //"Koordinaten" x, y
            positionNext = i * COLUMNS + j + COLUMNS; //"Koordinaten" x, y+1
            this->screen[position] = this->screen[positionNext];
        }

    }

    //letzte Zeile leeren
    CgaChar leer(' ', this->attribut);
    for (int i = 0; i < COLUMNS; i++)
    {
    	this->cursorX = 24;
    	this->cursorY = i;
        position = (COLUMNS) * (ROWS - 1) + this->cursorY;
        this->screen[position] = leer;
    }
    this->setCursor(0,24);
}

// Setzen/Lesen der globalen Bildschirmattribute
void CgaScreen::setAttr(const CgaAttr& attr) {
	this->attribut = attr;
}

void CgaScreen::getAttr(CgaAttr& attr) {
	this->attribut = attr;

}

// Setzen/Lesen des HW-Cursors
void CgaScreen::setCursor(int column, int row) {
	this->cursorX = row;
	this->cursorY = column;
	//calculating where Cursor is, based on fkt.
	this->cursor_adress = ((this->cursorX) * COLUMNS) + cursorY;

	//Set cursor in screen

	//WHY?
	this->ind.write(LOW);
	this->data.write(this->cursor_adress & 0xff);

	//WHY?
	this->ind.write(HIGH);
	this->data.write((this->cursor_adress >> 8) & 0xff);

	//setting cursor to calculated adress
	//setting ints to virtual Cursor-Adress, for better programming

	//beginning new row when at end of collumn



}
void CgaScreen::getCursor(int& column, int& row) {
	//writting actual Cursor ints to referenced space
	row = this->cursorX;
	column = this->cursorY;

}

// Anzeigen von c an aktueller Cursorposition
// Darstellung mit angegebenen Bildschirmattributen
void CgaScreen::show(char ch, const CgaAttr& attr) {


	if(this->cursorY == 79){

		this->cursorX ++;
		this->cursorY = 0;

		if(this->cursorX >= 24){
			scroll();

		}





	}else{

		this->cursorY++;
	}

	if(this->cursorX > 24){
				scroll();

			}


	//moving cursor on next field
	if (ch == '\n') {
		this->setCursorNewLine();

	} else {
		if (ch == '\r') {
			this->setCursor(0, this->cursorX);

		} else {
			CgaChar w(ch, attr);
			this->cursor_adress = this->cursorX * 80 + this->cursorY;
			this->screen[this->cursor_adress] = w;


		}

	}

}


void CgaScreen::setCursorBegin() {
	this->cursor_adress = startVideo;
	this->cursorX = 0;
	this->cursorY = 0;

}

void CgaScreen::setCursorNewLine() {
	this->cursorX++;
	setCursor(0,this->cursorX);

}

// Anzeigen von c an aktueller Cursorposition
// Darstellung mit aktuellen Bildschirmattributen
void CgaScreen::show(char ch) {

	show(ch, this->attribut);

}

