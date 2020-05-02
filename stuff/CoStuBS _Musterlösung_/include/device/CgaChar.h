#ifndef CgaChar_h
#define CgaChar_h

#include "device/CgaAttr.h"

/*
 * CgaChar:
 * 
 *	Diese Klasse stellt den Prototyp eines
 *	Zeichens des Bildschirms dar.
 *	Dieses besteht aus darstellbarem Zeichen
 *	und Darstellungsattributen.
 */


class CgaChar {

public:
	CgaChar(char c, CgaAttr atri){
		this->c = c;
		this->atri = atri;
	}
	// setzen des Zeichens
	void setChar(char c){
		this->c = c;

	}
	
	// auslesen des Zeichens
	char getChar(){
		return this->c;
	}
	
	// setzen der Darstellungsattribure
	void setAttr(const CgaAttr& attr){
		this->atri = attr;

	}
	
	// auslesen der Darstellungsattribute
	CgaAttr getAttr(){
		return atri;

	}

private:
	char c;
	CgaAttr atri;

};

#endif

