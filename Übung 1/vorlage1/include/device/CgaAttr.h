#ifndef CgaAttr_h
#define CgaAttr_h

/*
 * CgaAttr: 	Softwareprototyp fuer CGA Darstellungsattribute
 *		Hier braucht man Bitoperationen!
 *
 *		Da *alle* Operationen sehr einfach und kurz sind,
 *		duerft Ihr sie direkt in der Klasse
 *		als inline Methoden deklarieren.
 */

class CgaAttr {
private:
	enum AttrMaskAndShifts {
        
        FGPOSITION = 0,
        BGPOSITION = 4,
        BLPOSITION = 7,
        
        FGNUMBITS = 4,
        BGNUMBITS = 3,
        BLNUMBITS = 1
        
//         CLEARALL = 0; //Leeren den gesamten Byte -> 00000000
//         CLEARFG = 240; //Löschen die Vordergrundfarbe -> 11110000
//         CLEARBG = 143; //Löschen die Hintergrundfarbe -> 10001111
//         CLEARBL = 127; //Löschen den Blinker -> 01111111
        
	};


public:
	/** 	Diese Aufzählung enthält die CGA-Farben als Farbkonstanten
	 *	Tragt hier *alle* CGA Farben mit den richtigen Werten ein
	 */
	enum Color {
        
        BLACK = 0,
        BLUE = 1,
        GREEN = 2,
        CYAN = 3,
        RED = 4,
        MAGENTA = 5,
        BROWN = 6,
        LIGHT_GRAY = 7,
        GRAY = 8,
        LIGHT_BLUE = 9,
        LIGHT_GREEN = 10,
        LIGHT_CYAN = 11,
        LIGHT_RED = 12,
        LIGHT_MAGENTA = 13,
        YELLOW = 14,
        WHITE = 15,
        
        /*
         * Wichtig:
         * Betrachtet wird nur der zweite Byte (1 Byte = 8 Bits)
         * Bits 0 - 3 = Vordergrundfarbe
         * Bits 4 - 6 = Hintergrundfarbe
         * Bit 7 = Blinker
         * Gelesen wird dabei von rechts nach links!
         * ACHTUNG! Die Hintergrundfarbe kann maximal 3 Bits speichern, weswegen nur die Farben 0 bis 7 genutzt werden können
         */ 
	};


	/** Konstruktor. Erzeugt ein CgaAttr-Objekt mit den uebergebenen Werten für
	  * Vorder- und Hintergrundfarbe. Werden keine Parameter uebergeben,
	  * so werden die Defaultwerte (Vordergrund weiss, Hintergrund schwarz, Blinken deaktiviert)
	  * verwendet.
	  */
	CgaAttr(Color fg=WHITE, Color bg=BLACK, bool blink=false)
    {
        if ((int) bg > 7) {     
            bg = BLACK;                          
        }                                        
        
        this -> bitInformation = ((blink | bg) << BGPOSITION ) | fg;
	}

	// setzen der Schriftfarbe
	void setForeground(Color col)
	{
        int zwischenwert = (this -> bitInformation) &= ~(FGNUMBITS << FGPOSITION);
        
        // Man kann auch damit clearen: this -> bitInformation & CLEARFG;
        
        this -> bitInformation = zwischenwert | (col << FGPOSITION);
	}

	// setzen der Hintergrundfarbe
	void setBackground(Color col)
	{
        if (col > 7) {
            col = Color(col);
        }
        
        int zwischenwert = (this -> bitInformation) &= ~(BGNUMBITS << BGPOSITION);
        
        this -> bitInformation = zwischenwert | (col << BGPOSITION);
	}

	// setzen blinkender/nicht blinkender Text
	void setBlinkState(bool blink)
	{
        int zwischenwert = (this -> bitInformation) &= ~(BLNUMBITS << BLPOSITION);
        
        this -> bitInformation = zwischenwert | (blink << BLPOSITION);
	}

	// setzen aller Attribute
	void setAttr(CgaAttr attr)
	{
        this -> bitInformation = attr.bitInformation; // verstehe ich noch nicht
	}

	// ermitteln der Schriftfarbe
	Color getForeground()
	{
        int foregroundColor = (this -> bitInformation) &= ~((BGNUMBITS + BLNUMBITS) << BGPOSITION);
        
        return (Color) foregroundColor;
	}

	// ermitteln der Hintergrundfarbe
	Color getBackground()
	{
        int backgroundColor = (this -> bitInformation) &= ~(BLNUMBITS << BLPOSITION);
        int backgroundColor2 = backgroundColor >> FGNUMBITS;
        
        return (Color) backgroundColor2;
	}

	// ermitteln ob Blink-Flag gesetzt ist
	bool getBlinkState()
	{
        int blinkState = (this -> bitInformation) >> (FGNUMBITS + BGNUMBITS);
        
        return (bool) blinkState;
	}

private:
    
    int bitInformation;
    
};

#endif
