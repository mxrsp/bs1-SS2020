#include "device/Clock.h"
#include "interrupts/InterruptVector.h"
#include "io/PrintStream.h"
#include "device/CgaChannel.h"
#include "sync/KernelLock.h"

// normalerweise:
extern CgaChannel screen;
extern PrintStream out;

// Ticken zeigen:
// CgaChannel cga;
// PrintStream out(cga);

extern PIT pit;

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

bool Clock::prologue () {
    
    KernelLock lock;
    
    
    //Bestätigen des Interrupts
    pic.ack(PIC::PIT);
    return true;
}

void Clock::epilogue () {
    scheduler.checkSlice();
}

void Clock::informationPropeller() {
    screen.setCursor(3,3);
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
        screen.setCursor(0,0);
        out.print("/");
    } else if (second % 4  == 1) {
        screen.setCursor(0,0);
        out.print("-");
    } else if (second % 4 == 2) {
        screen.setCursor(0,0);
        out.print("\\");
    } else if (second % 4 == 3) {
        screen.setCursor(0,0);
        out.print("|");
    }
    
    out.print("       ");
    out.print(handleCount);
    out.println(" - Interrupt-Counter");
}

