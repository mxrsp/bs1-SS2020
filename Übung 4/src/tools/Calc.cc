#include "tools/Calc.h"

#include "device/CgaChannel.h" // ermöglicht Kontrolle über Cursor
#include "device/Keyboard.h" // ermöglicht Eingaben durch Tastatur
#include "io/PrintStream.h" // ermöglicht Linefeeds und Ausgabe von Zahlen
#include "interrupts/IntLock.h"

extern CgaChannel cga;
extern PrintStream out;

Calculator::Calculator()
{
    init();
}

Calculator::Calculator(void* sp)
    : Activity(sp)
{
    init();
    wakeup();
}

void Calculator::init()
{
    clearBuffer();
    cga.clear();
}

void Calculator::body() {
    
    int index = 0;
    char c;
		Key key;
		do{
			key = keyboard.read();
            if (key.isAscii()) {
                c = key.getValue();
                buffer[index] = c;
                index++;
                out.print(c);
            }
		}while(c!='x'); // solange ESC nicht gedrückt
    
}

void Calculator::insert(char c) {
}

void Calculator::enter() {

}

void Calculator::moveLeft() {
	int column, row;
	
	cga.getCursor(column, row);
	
	if(column == 0 && row > 0) {
		cga.setCursor(79, row - 1);
	} else if(row > 0){
		cga.setCursor(column - 1, row);
	} else {
		return;
	}
}

void Calculator::moveRight() {
	int column, row;
	
	cga.getCursor(column, row);
	
	if(column > 79) {
		out.println();
	} else {
		cga.setCursor(column + 1, row);
	}
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
    // Alle Zeichen nullen und Null-Byte hinter der höchsten Stelle setzen
    for (unsigned i=0; i<=EXPR_SIZE_MAX; ++i)
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
