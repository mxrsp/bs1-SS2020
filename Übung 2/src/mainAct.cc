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
        // cout.println("Konstruktor Variante 1 wird in main aufgerufen");
        
		this->name = name;
		this->count = count;
        
        setNameActivity(name);
	}

	Hello(const char* name, PrintStream& out, void* sp, int count=10)
		: Activity(sp), cout(out)
	{
        // cout.println("Konstruktor Variante 2 wird in main aufgerufen");
        
		this->name = name;
		this->count = count;
        
        setNameActivity(name);
        
		wakeup();
	}
	
	~Hello()
	{
        cout.print("       Destruktor in main wird aufgerufen von ");
        cout.print(this -> name);
        cout.println();
	}
	
	void body()
	{
		for(int i=0; i<=count; i++) {
			cout.print("       ");
            cout.print(name);
			cout.print(" ");
			cout.print(i);
			cout.println();

            for (int i = 0; i < 15000000; i++) {}
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
    cga.blueScreen("       ANFANG");
 	Hello anton("Anton", out, 1); // anton benutzt den Stack von main
    out.println("       Anton wurde erzeugt");
 	Hello berta("Berta", out, &stack0[1023], 2);
    out.println("       Berta wurde erzeugt");
    anton.body();
    out.println("       Body von Anton ist fertig");
    for (int i = 0; i < 25000000; i++) {}
    out.println("       ENDE");
    for (int i = 0; i < 15000000; i++) {}
// 	Hello caesar("Caesar", out, &stack1[1024], 15);
}
