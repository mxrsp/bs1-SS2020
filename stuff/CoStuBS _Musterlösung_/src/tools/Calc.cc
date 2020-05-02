#include "tools/Calc.h"

#include "device/CgaChannel.h" // erm√∂glicht Kontrolle √ºber Cursor
#include "device/Keyboard.h" // erm√∂glicht Eingaben durch Tastatur
#include "io/PrintStream.h" // erm√∂glicht Linefeeds und Ausgabe von Zahlen

extern CgaChannel cga;
extern PrintStream out;

Calculator::Calculator() {
	init();
}

Calculator::Calculator(void* sp) :
		Activity(sp) {

	init();
	wakeup();
}

void Calculator::init() {
	clearBuffer();
	cga.clear();
	pos = 0;

}

void Calculator::body() {
	cga.setCursorBegin();
	out.println("begin");
	Key key;
	while (!(key.getValue() == 27)) {
		key = keyboard.read();

		if (key.getValue() == CodeTable::RIGHT) {
			moveRight();
		} else if (key.getValue() == CodeTable::LEFT) {
			moveLeft();
		} else if (key.getValue() == CodeTable::ENTER) {
			enter();
		} else if (key.getValue() == CodeTable::DEL || key.getValue() == 8) {
			del();
		} else if (key.getValue() != 27) {
			int s, z;
			cga.getCursor(s, z);

			//Zeilenl‰nge
			if (pos < EXPR_SIZE_MAX) {
				insert(key.getValue());
			}

		}

	}
	out.println("done");

}

void Calculator::insert(char c) {
	 if (c == 40 || c == 41) {
		checkPos();
		buffer[pos] = c;
		out.print(c);
		pos++;
	} else if (interp.isDigit(c)) {
		checkPos();
		buffer[pos] = c;
		out.print(c);
		pos++;
	} else if (interp.isOp(c)) {
		checkPos();
		buffer[pos] = c;
		out.print(c);
		pos++;

	} else if (interp.isChar(c)) {

		checkPos();
		buffer[pos] = c;
		out.print(c);
		pos++;

	} else if (interp.isWhitespace(c)) {
		checkPos();
		out.print(' ');
	}

	moveLeft();
	moveRight();
}

void Calculator::checkPos() {
	if (buffer[pos] != 0 && sizeof(buffer) < EXPR_SIZE_MAX) {
		//werte in Array ¸berschreiben
		for (unsigned i = sizeof(buffer); i > pos; i--) {
			buffer[i] = buffer[i - 1];
		}
		buffer[pos] = 0;
		int s, z;
		cga.getCursor(s, z);
		out.print(' ');
		//¸berschriebenes Array ausgeben
		for (unsigned i = pos + 1; i <= sizeof(buffer); i++) {
			out.print(buffer[i]);

		}

		cga.setCursor(s, z);

	}

}

void Calculator::enter() {
	int s, z;
	cga.getCursor(s, z);

	out.println();
	out.print("Ergebnis:  ");
	int result;
	unsigned status;
	status = interp.eval((char *) buffer, result); //interp. checkt ob regul‰rer ausdruck, wenn ja dann 0 sonst errorcode
	if (status == 0) {
		out.print(result);
	} else {
		printErrorMsg(status);
	}

	//buffer leeren und n‰chste Rechnung vorbereiten

	for (unsigned i = 0; i < sizeof(buffer); i++) {
		buffer[i] = 0;
		pos = 0;
	}
	out.println();

	//cursor auf neue Zeile

	cga.setCursor(0, z + 2);
	pos = 0;
	currentLine = z + 2;
}

void Calculator::moveLeft() {
	int z;
	int s;
	cga.getCursor(s, z); //laden der Werte in z und s

	if (s > 0) {
		cga.setCursor(s - 1, z);
		pos--;
	} else if (s == 0) {
		cga.setCursor(EXPR_SIZE_MAX + 1, z - 1);
		pos = EXPR_SIZE_MAX + 1;
	}

}

void Calculator::moveRight() {
	int s, z;
	cga.getCursor(s, z);

	if (s < EXPR_SIZE_MAX) {
		cga.setCursor(s + 1, z);
		pos++;
	} else {
		cga.setCursor(0, z + 1);
		pos = 0;
	}

}

void Calculator::del() {
	int s, z;
	cga.getCursor(s, z);
	cga.setCursor(s - 1, z);
	buffer[pos - 1] = ' ';
	out.print(' ');
	pos--;
	moveLeft();

}

void Calculator::renderBuffer() {
	// Cursor sichern
	int column, row;
	cga.getCursor(column, row);

	// Zeile schreiben
	cga.setCursor(0, row);
	cga.write(buffer, EXPR_SIZE_MAX);

	// Cursor wiederherstellen
	cga.setCursor(column, row);
}

void Calculator::clearBuffer() {
	// Alle Zeichen nullen und Null-Byte hinter der h√∂chsten Stelle setzen
	for (unsigned i = 0; i <= EXPR_SIZE_MAX; ++i)
		buffer[i] = 0;
}

void Calculator::printErrorMsg(unsigned code) {
	switch (code) {
	case Interpreter::UNEXP_EOT:
		out.print("Error: Unexpected end of expression!");
		break;

	case Interpreter::UNEXP_SYMBOL:
		out.print("Error: Unexpected symbol!");
		break;

	case Interpreter::ARITHM_ERROR:
		out.print("Error: Arithmetic error!");
		break;

	case Interpreter::BAD_BUFFER:
		out.print("Error: Invalid buffer!");
		break;

	default:
		break;
	}

}

