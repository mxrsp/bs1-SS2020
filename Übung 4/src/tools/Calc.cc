#include "tools/Calc.h"

#include "device/CgaChannel.h" // ermöglicht Kontrolle über Cursor
#include "device/Keyboard.h" // ermöglicht Eingaben durch Tastatur
#include "io/PrintStream.h" // ermöglicht Linefeeds und Ausgabe von Zahlen
#include "interrupts/IntLock.h"
#include "device/CodeTable.h"

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
    
    int result = 0;
    unsigned fehlercode;
    
    int column, row;
    
//     char eingabe [32] = "4 / 2";
//     char* in = eingabe;
//     
//     fehlercode = interp.eval(in, result);
//     if (fehlercode == 0) {
//         out.print("   ");
//         out.print(result);
//         out.println();
//     } else {
//         printErrorMsg(fehlercode);
//     }
//     
//     out.println("FERTIG");
    
    
    int index = 0;
    char c;
		Key key;
		do{
            cga.getCursor(column, row);
			key = keyboard.read();
            c = key.getValue();
            if (key.isAscii()) {
                if (c == '\n') {
                    enter();
                    char* input = buffer;
                    fehlercode = interp.eval(input, result);
                    if (fehlercode == 0) {
                        out.print(" = ");
                        out.print(result);
                        result = 0;
                        enter();
                    } else {
                        printErrorMsg(fehlercode);
                        enter();
                    }
                    index = 0;
                } else if (c == 0) {
                    out.print("ESC wurde gedrückt");
                } else if ((c == '\b') && (index > 0)) {
                    cga.setCursor(column-1,row);
                    out.print(" ");
                    cga.setCursor(column-1,row);
                    buffer[index] = 0;
                    index--;
                } else if (index < EXPR_SIZE_MAX){   
                    buffer[index] = c;
                    index++;
                    out.print(c);
                } 
            } else {
                if (c == CodeTable::LEFT) {
                    moveLeft();
                } else if (c == CodeTable :: RIGHT) {
                    moveRight();
                }
            }
		}while(c!='x'); // solange ESC nicht gedrückt
    
}

void Calculator::insert(char c) {
}

void Calculator::enter() {
    out.println();
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
	
	if(column > 79 && row == 25) {
		out.println();
	} else if(column > 79){
		cga.setCursor(0, row + 1);
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
