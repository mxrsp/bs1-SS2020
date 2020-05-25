#include "device/PIT.h"

PIT::PIT () : intervall(23866), steuerregister(PIT::CONTROL_PORT), datenregister(PIT::DATA_PORT) {} //intervall()

PIT::PIT (int us) : intervall(us), steuerregister(PIT::CONTROL_PORT), datenregister(PIT::DATA_PORT) {}

void PIT::interval (int us) {
    
    /*
        00110100 (rechts nach links lesen)
        -> Binäre Zählung + Modus 2 + nieder- und hoeherwertiges Zaehlerbyte + Zaehler 0
     */
    this->steuerregister.write(0x34);
    
    this->intervall = us;
    // "us" Mikrosekunden zur Systemzeit (Ticks)
    int interruptCount = ((unsigned) this->intervall) * TIME_BASE; //Ein Intervall bei 10000 us = ein kommpletter Uhrdurchgang = ca 8 Sekunden
    // Schreiben nun auf die 16 Bits
    this->datenregister.write(interruptCount);
    this->datenregister.write(interruptCount >> 8);
}

