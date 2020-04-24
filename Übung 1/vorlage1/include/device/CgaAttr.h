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
	};


public:
	/** 	Diese Aufzählung enthält die CGA-Farben als Farbkonstanten
	 *	Tragt hier *alle* CGA Farben mit den richtigen Werten ein
	 */
	enum Color {
	};


	/** Konstruktor. Erzeugt ein CgaAttr-Objekt mit den uebergebenen Werten für
	  * Vorder- und Hintergrundfarbe. Werden keine Parameter uebergeben,
	  * so werden die Defaultwerte (Vordergrund weiss, Hintergrund schwarz, Blinken deaktiviert)
	  * verwendet.
	  */
	CgaAttr(Color fg=WHITE, Color bg=BLACK, bool blink=false)
	{
	}

	// setzen der Schriftfarbe
	void setForeground(Color col)
	{
	}

	// setzen der Hintergrundfarbe
	void setBackground(Color col)
	{
	}

	// setzen blinkender/nicht blinkender Text
	void setBlinkState(bool blink)
	{
	}

	// setzen aller Attribute
	void setAttr(CgaAttr attr)
	{
	}

	// ermitteln der Schriftfarbe
	Color getForeground()
	{
	}

	// ermitteln der Hintergrundfarbe
	Color getBackground()
	{
	}

	// ermitteln ob Blink-Flag gesetzt ist
	bool getBlinkState()
	{
	}

private:


};

#endif
