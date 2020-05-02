
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
	CgaChannel :: CgaChannel() : CgaScreen() {
	};

	// Ausgabekanal mit spezifischen Attributen
	 CgaChannel ::  CgaChannel(const CgaAttr& attr) : CgaScreen(attr)  {
	};

	// Ausgabekanal mit Standardattributen


	// Die von OutputChannel deklarierte Ausgaberoutine
	int CgaChannel :: write(const char* data, int size)
	{
		for(int i = 0; i<size;i++){

		this->show(data[i]);
		}

		return size;
	}


	void CgaChannel :: blueScreen() {
		blueScreen("DAS SOLLTE NICHT PASSIEREN!!!");
	}

	// Bluescreen mit eigener Fehlermeldung
    void CgaChannel :: blueScreen(const char* error){
    		this->setCursorBegin();
    		CgaAttr attr = CgaAttr();
    		attr.setForeground(CgaAttr :: WHITE);
    		attr.setBackground(CgaAttr :: BLUE);
    		attr.setBlinkState(false);
    		this->attribut = attr;
    		for(int k= 0; k<ALL; k++){
    		this->show(' ',attribut);
    		}
    		this->setCursorBegin();

    		int i = getLength(error);
    		this->setCursor(5,12);
    		//clear(CgaAttr(CgaAttr ::WHITE, CgaAttr :: BLUE, false));
    		this->write(error, i);


    }

    int CgaChannel :: getLength(const char* error){
    	int i = 0;
    	while(error[i] != '\0'){
    		i++;
    	}
    	return i;
    }

	// Bluescreen mit standard Fehlermeldung








