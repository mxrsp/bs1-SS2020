#include "user/Hello.h"

#include "user/Environment.h"
#include "sync/KernelLock.h"
#include "interrupts/IntLock.h"

Hello::Hello(const char* name, int runs, int slice, void* sp)
	: Thread(sp, slice)
{
	this->name = name;
	this->runs = runs;

	out.print(name);
	out.println(" is created!");
	start();
}

Hello::~Hello()
{
	console.attach();
	out.print("Waiting for termination of ");
	out.println(name);
	console.detach();
	join();
	console.attach();
	out.print(name);
	out.println(" is terminated");
	console.detach();
}

void Hello::run()
{
    // out.print("neues Hello ist dran -> ");
    // out.print(name);
    // out.println();
	console.attach();
	out.print(name);
	out.println(" is running ");
	console.detach();

    // KernelLock lock;
    // IntLock ilock;
    
	for (int i = 0; i < runs; i++) {
        // out.print("Aktiver Prozess: ");
        // out.print(name);
        // out.println();
		console.attach(); // Konsole reservieren
        
        // out.println("TEST vor Einlesen");

		out.print(name);
		out.print("> ");
        
		int size = console.read(line, LINE_SIZE);
        
        // out.println("TEST nach Einlesen");

		out.print("got: ");
		out.print(size);
		out.print(" ");

		line[size-1] = '\0'; // '\n' durch '\0' ersetzen

		// jetzt koennen wir die Zeile ausgeben
		out.println(line);
        
        // out.println("Eingabe beendet!");

		console.detach(); // und freigeben
	}

	console.attach();
	out.print(name);
	out.println(" finished");
	console.detach();
}
