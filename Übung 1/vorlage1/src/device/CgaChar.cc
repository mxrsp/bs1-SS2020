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

	// setzen des Zeichens
	void setChar(char c) {
        this -> c = c;
    }
    
	// auslesen des Zeichens
	char getChar() {
        return this -> c;
    }
	
	// setzen der Darstellungsattribure
	void setAttr(const CgaAttr& attr) {
        this -> attribut = attr;
    }
	
	// auslesen der Darstellungsattribute
	CgaAttr getAttr() {
       return this -> attribut;
    }

private:
    char c;
    CgaAttr attribut;

};

#endif
