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

class CgaAttr
{
  private:
	enum AttrMaskAndShifts
	{
		shift_fg = 0,
		mask_fg = 0x0F,

		shift_bg = 4,
		mask_bg = 0x07,

		shift_blink = 7,
		mask_blink = 0x01
	};

  public:
	/** 	Diese Aufz�hlung enth�lt die CGA-Farben als Farbkonstanten
	 *	Tragt hier *alle* CGA Farben mit den richtigen Werten ein
	 */
	enum Color
	{
		BLACK = 0x0,
		BLUE = 0x1,
		BROWN = 0x6,
		CYAN = 0x3,
		GRAY = 0x8,
		GREEN = 0x2,
		LIGHT_BLUE = 0x9,
		LIGHT_CYAN = 0xB,
		LIGHT_GRAY = 0x7,
		LIGHT_GREEN = 0xA,
		LIGHT_MAGENTA = 0xD,
		LIGHT_RED = 0xC,
		MAGENTA = 0x5,
		RED = 0x4,
		WHITE = 0xF,
		YELLOW = 0xE
	};

	/** Konstruktor. Erzeugt ein CgaAttr-Objekt mit den uebergebenen Werten f�r
	  * Vorder- und Hintergrundfarbe. Werden keine Parameter uebergeben,
	  * so werden die Defaultwerte (Vordergrund weiss, Hintergrund schwarz, Blinken deaktiviert)
	  * verwendet.
	  */
	CgaAttr(Color fg = WHITE, Color bg = BLACK, bool blink = false)
	{
		setBlinkState(blink);
		setBackground(bg);
		setForeground(fg);
	}

	// setzen der Schriftfarbe
	void setForeground(Color col)
	{
		//erst Vordergrund "zurücksetzen"
		this->bites &= ~(mask_fg << shift_fg);
		this->bites |= (col << shift_fg) & (mask_fg << shift_fg);
	}

	// setzen der Hintergrundfarbe
	void setBackground(Color col)
	{
		//erst Hintergrund "zurücksetzen"
		this->bites &= ~(mask_bg << shift_bg);
		this->bites |= (col << shift_bg) & (mask_bg << shift_bg);
	}

	// setzen blinkender/nicht blinkender Text
	void setBlinkState(bool blink)
	{
		this->bites &= ~(mask_blink << shift_blink);
		this->bites |= (blink << shift_blink) & (mask_blink << shift_blink);
	}

	// setzen aller Attribute
	void setAttr(CgaAttr attr)
	{
		//this->bites = 0;
		bool blink = attr.getBlinkState();
		Color bg = attr.getBackground();
		Color fg = attr.getForeground();
		setForeground(fg);
		setBlinkState(blink);
		setBackground(bg);
	}

	// ermitteln der Schriftfarbe
	Color getForeground()
	{
		return (Color)((bites & mask_fg) >> shift_fg);
	}

	// ermitteln der Hintergrundfarbe
	Color getBackground()
	{
		return (Color)((bites & (mask_bg << shift_bg)) >> shift_bg);
	}

	// ermitteln ob Blink-Flag gesetzt ist
	bool getBlinkState()
	{
		return (bool)((bites & (mask_blink << shift_blink)) >> shift_blink);
	}

  private:
	char bites;
};

#endif
