#include "user/Hello.h"

#include "user/Environment.h"
#include "sync/KernelLock.h"
#include "interrupts/IntLock.h"

extern Monitor monitor;

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
    if (monitor.isFree()) {
        // out.println("Monitor ist frei in run");
    } else {
        // out.println("Monitor ist besetzt in run"); 
    }
    
	console.attach();
	out.print(name);
	out.println(" is running ");
	console.detach();
    
	for (int i = 0; i < runs; i++) {
		console.attach(); // Konsole reservieren

		out.print(name);
		out.print("> ");
        
		int size = console.read(line, LINE_SIZE);

		out.print("got: ");
		out.print(size);
		out.print(" ");

		line[size-1] = '\0'; // '\n' durch '\0' ersetzen

		// jetzt koennen wir die Zeile ausgeben
		out.println(line);

		console.detach(); // und freigeben
	}

	console.attach();
	out.print(name);
	out.println(" finished");
	console.detach();
}
