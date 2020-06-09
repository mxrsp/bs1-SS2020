#include "device/CgaChar.h"

/*
 * CgaChar:
 * 
 *	Diese Klasse stellt den Prototyp eines
 *	Zeichens des Bildschirms dar.
 *	Dieses besteht aus darstellbarem Zeichen
 *	und Darstellungsattributen.
 */
	// setzen des Zeichens
	void CgaChar::setChar(char c) {
        this -> c = c;
    }
    
	// auslesen des Zeichens
	char CgaChar::getChar() {
        return this -> c;
    }
	
	// setzen der Darstellungsattribure
	void CgaChar::setAttr(const CgaAttr& attr) {
        this -> attribut = attr;
    }
	
	// auslesen der Darstellungsattribute
	CgaAttr CgaChar::getAttr() {
       return this -> attribut;
    }

