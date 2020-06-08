// Testprogramm fuer kooperative Threads

#include "device/CgaChannel.h"
#include "device/CPU.h"
#include "io/PrintStream.h"
#include "thread/Activity.h"
#include "thread/ActivityScheduler.h"
#include "device/PIC.h"
#include "device/Clock.h"
#include "interrupts/InterruptGuardian.h"
#include "interrupts/IntLock.h"


CPU cpu;
// Hello: Eine kooperative Aktivitaet
//
// Anmerkung: Diese Klasse dient
// zu Testzwecken und der Einfacheit halber sind
// alle Methoden dieser Klasse ausnahmsweise inline deklariert
// Das sollte normalerweise *nicht* der Fall sein!
class Hello: public Activity {
public:
	Hello(const char* name, PrintStream& out)
		: cout(out)
	{   
		this->name = name;
        setNameActivity(name);
	}

	Hello(const char* name, PrintStream& out, void* sp)
		: Activity(sp), cout(out)
	{
		this->name = name;
        setNameActivity(name);
		wakeup();
	}

	~Hello()
	{
         cout.print("Vor Join  von: ");
         cout.println(name);
         
		 join();
         
         cout.print("Nach Join  von: ");
         cout.println(name);
    }

	void body()
	{   
		for(int i=0; i<7; i++) {
			{
				IntLock lock;
				cout.print(name);
				cout.print(" ");
				cout.print(i);
				cout.println();
                for(int j=0; j<5000000; j++);
			}
            for(int j=0; j<10000; j++);
		}
	}

private:
	const char* name;
	PrintStream& cout;
};

//////////////////////////////////////////////////////////////////////////
// Die Systemobjekte von Co-Stubs

// CPU cpu;

InterruptGuardian interruptGuardian;
PIC pic;
Clock clock(2500);

// globale Ein-/Ausgabeobjekte
CgaChannel cga;         // unser CGA-Ausgabekanal
PrintStream out(cga);   // unseren PrintStream mit Ausgabekanal verknuepfen

// Objekte der Prozessverwaltung
ActivityScheduler scheduler;   // der Scheduler

// die Stacks fuer unsere Prozesse/Coroutinen
unsigned stack0[1024];
unsigned stack1[1024];

int main()
{
    out.println();
    
	Hello anton("Anton", out); // anton benutzt den Stack von main
	Hello berta("Berta", out, &stack0[1024]);
	Hello caesar("Caesar", out, &stack1[1024]);
    
    // Test 1
    anton.quantum(1);
    berta.quantum(1);
    caesar.quantum(100);

    // Test 2
//     anton.quantum(1);
//     berta.quantum(2);
//     caesar.quantum(3);

    // Test 3    PageFault sollte nicht auftauchen
//     anton.quantum(1);
//     berta.quantum(1);
//     caesar.quantum(100);
    
    // Test 4
//     anton.quantum(100);
//     berta.quantum(1);
//     caesar.quantum(1);
    
    // Test 5
//     anton.quantum(1);
//     berta.quantum(100);
//     caesar.quantum(1);
    
	cpu.enableInterrupts();
    
	anton.body();
}
