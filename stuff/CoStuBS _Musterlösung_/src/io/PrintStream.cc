#include "io/PrintStream.h"
#include "io/OutputChannel.h"
/*
 * PrintStream:	Diese Klasse ist aehnlich der Java-PrintStream Klasse
 *		Sie konvertiert u.A. numerische Werte in sichtbare Zeichen
 *		und gibt Sie auf dem im Konstruktor spezifizierten
 *		Ausgabekanal aus.
 *		Daraus ergeben sich 2 Teilaufgaben:
 *
 *		1. Die Feststellung der Ziffern einer Zahl
 *		2. Die Umwandlung der Ziffern in darstellbare Zeichen
 *
 *		Man beachte, dass diese Klasse unabhaengig
 *		von dem tatsaechlich verwendeten Ausgabekanal arbeitet.
 *
 *		Anmerkung: Diese Klasse werden wir spaeter noch in
 *		C++ konforme Ausgabe umwandeln.
 */

PrintStream::PrintStream(OutputChannel* chan) :
		channel(*chan) {
}
PrintStream::PrintStream(OutputChannel& chan) :
		channel(chan) {
}

// Ausgabe eines mit einem NULL-Byte terminierten Strings
//while solange bis 0-Byte zum beendigen kommt
void PrintStream::print(const char* str) {
	int i = 0;
	while (str[i] != '\0') {


			this->channel.write(str[i]);
			i++;

	}
}

void PrintStream::print(char ch) {
	this->channel.write(ch);
}

// Ausgabe eines Strings mit anschliessendem Zeilenvorschub
void PrintStream::println(const char* str) {
	print(str);
	print('\n');
}

// Zeilenvorschub
void PrintStream::println() {
	print('\n');
}

// numerische Werte werden zur Basis 'base' Ausgegeben
// implementiere die Basen 2, 10 und 16
void PrintStream::print(int x, int base) {
	// int max 32 bit groﬂ

	if (base == (int) DECIMAL || base == (int) BINARY || base == (int) HEX) {
		if (x < 0) {
			print('-');
			x = -x;
		}
		print((unsigned) x, base);

	} else {

		print("keine definierte Basis");

	}

}

void PrintStream::print(unsigned x, int base) {
	int num[32];
	if (base == DECIMAL) {
		print(" ");

	}

	if (base == HEX) {
		print("0x");

	}

	if (base == BINARY) {
		print("0b");

	}
	if (x == 0) {
		print('0');
	}

	if (base == (int) DECIMAL || base == (int) BINARY || base == (int) HEX) {

		int i = 31;
		while (x != 0) {
			num[i] = (x % base) + 48; // ASCII 48 = 0, 57 = 9;
			x = x / base;
			i--;

		}
		i++;
		int x1 = 0;
		for (; i < 32; i++) {
			x1 = num[i] - 48; // von ascii bereinigen
			if (x1 < 10) {
				this->channel.write((char) num[i]);
			}
			if (x1 == 10) {
				print('a');
			}
			if (x1 == 11) {
				print('b');
			}
			if (x1 == 12) {
				print('c');
			}
			if (x1 == 13) {
				print('d');
			}
			if (x1 == 14) {
				print('e');
			}
			if (x1 == 15) {
				print('f');
			}

		}

	} else {

		print("keine definierte Basis");
		return;
	}

}

// Zeigertypen werden immer zur Basis 16 ausgegeben!
void PrintStream::print(void* p) {
	//getting value from zeiger
	int x = (unsigned int) p;
	print(x, 16);
}

