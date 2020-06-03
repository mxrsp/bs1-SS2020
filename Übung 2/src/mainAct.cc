// Testprogramm fuer kooperative Threads

#include "device/CgaChannel.h"
#include "io/PrintStream.h"
#include "thread/Activity.h"
#include "thread/ActivityScheduler.h"

// Hello: Eine kooperative Aktivitaet
//
// Anmerkung: Diese Klasse dient
// zu Testzwecken und der Einfacheit halber sind
// alle Methoden dieser Klasse ausnahmsweise inline deklariert
// Das sollte normalerweise *nicht* der Fall sein!
class Hello: public Activity {
public:
	Hello(const char* name, PrintStream& out, int count=10)
		: cout(out)
	{
        
		this->name = name;
		this->count = count;
        
        setNameActivity(name);
	}

	Hello(const char* name, PrintStream& out, void* sp, int count=10)
		: Activity(sp), cout(out)
	{
        
		this->name = name;
		this->count = count;
        
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
		for(int i=0; i<=count; i++) {
            cout.print(name);
			cout.print(" ");
			cout.print(i);
			cout.println();
            
			yield(); 
		}
	}

private:
	const char* name;
	PrintStream& cout;
	int count;
};

//////////////////////////////////////////////////////////////////////////
// Die Systemobjekte von Co-Stubs

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
 	Hello anton("Anton", out, 6); // anton benutzt den Stack von main
 	Hello berta("Berta", out, &stack0[1024], 4);
    Hello caesar("Caesar", out, &stack1[1024], 2);
    anton.body();
}
