#include "device/Clock.h"
#include "device/CgaChannel.h"
#include "io/PrintStream.h"
#include "interrupts/InterruptVector.h"


//extern PrintStream out;

CgaChannel cga;
PrintStream out(cga);

PIT pit;

Clock::Clock () : Gate(Timer), timeByTicks(0) {}

Clock::Clock (int us) : Gate(Timer), timeByTicks(0) {
    out.println("   Eine Clock wird erzeugt");
    out.wait();
    
    windup(us);
}

void Clock::windup (int us) {
    
    //maximal 16 Bit, also 65536 (0xFFF) möglich Werte
    if (us > 0xFFFF) {
        us = 0xFFFF;
    }

    this->timeByTicks = 0;
    pit.interval(us);
    pic.enable(PIC::PIT);
    
    /*
     enable => anstellen
     disable => abstellen
     ack => behandeln
    */
}

void Clock::handle () {
    
    pic.ack(PIC::PIT); //Bestätigen des Interrupts
    this->timeByTicks++; //Mitzaehlen der Uhrticks
    
    
    propellerAction();
    
    out.print("       ");
    out.print(this->timeByTicks);
    out.println(" - so oft tickt die Uhr");
    out.wait();

    scheduler.checkSlice();
}

void Clock::propellerAction() {
        //Propeller Teller
    int second = timeByTicks;
    
    if (second % 4 == 0) {
        cga.setCursor(0,0);
        out.print("/");
        
    } else if (second % 4  == 1) {
        cga.setCursor(0,0);
        out.print("-");
        
    } else if (second % 4 == 2) {
        cga.setCursor(0,0);
        out.print("\\");
        
    } else if (second % 4 == 3) {
        cga.setCursor(0,0);
        out.print("|");
    }
}

