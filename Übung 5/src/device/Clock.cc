#include "device/Clock.h"
#include "interrupts/InterruptVector.h"
#include "io/PrintStream.h"
#include "device/CgaChannel.h"

// normalerweise:
extern CgaChannel cga;
extern PrintStream out;

// Ticken zeigen:
// CgaChannel cga;
// PrintStream out(cga);

PIT pit;

Clock::Clock () : Gate(Timer), handleCount(0) {
}

Clock::Clock (int us) : Gate(Timer), handleCount(0) {
    windup(us);
}

void Clock::windup (int us) {
    
    // aufrufHandleProSekunde = 1000 / (us / 1000);
    // 1 000 Millisekunden / (x Mikrosekunden / 1000)
    
    //informationPropeller();
    
    //maximal 16 Bit, also 65536 (0xFFF) möglich Werte
    if (us > 0xFFFF) {
        us = 0xFFFF;
    }
    
    pit.interval(us);
    pic.enable(PIC::PIT);
    
    /*
     enable => anstellen
     disable => abstellen
     ack => behandeln
    */
}
//handle entfällt, sobald prologue und epilogue implementiert wurden
void Clock::handle () {
    
    pic.ack(PIC::PIT); //Bestätigen des Interrupts
    
    scheduler.checkSlice();
    
    // propellerAction();
    
}
//TODO
bool Clock::prologue() {
	return true;
}
//TODO
void Clock::epilogue() {
	
}

void Clock::informationPropeller() {
    cga.setCursor(3,3);
    out.print(aufrufHandleProSekunde);
    out.println(" mal wird handle pro Sekunde aufgerufen");
}

void Clock::propellerAction() {
    
    // Kurzes Warten, wenn Uhr eine Umdrehung geschafft hat
    if (handleCount % (8 * aufrufHandleProSekunde) == 0) {
        out.wait();
    }
    
    //Propeller Teller
    int second = (int) handleCount / aufrufHandleProSekunde;
    
    // handle wird 50 mal pro Sekunde aufgerufen
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
    
    out.print("       ");
    out.print(handleCount);
    out.println(" - Interrupt-Counter");
}

