#include "device/PIT.h"

PIT::PIT () : steuerregister(PIT::CONTROL_PORT), datenregister(PIT::DATA_PORT) {}

PIT::PIT (int us) : intervall(us), steuerregister(PIT::CONTROL_PORT), datenregister(PIT::DATA_PORT) {}

void PIT::interval (int us) {
    
    /*
        00110100 = 52 (rechts nach links lesen)
        -> Binäre Zählung + Modus 2 + nieder- und hoeherwertiges Zaehlerbyte + Zaehler 0
    */
    this->steuerregister.write(0x34);
    
    this->intervall = us;
    // "us" Mikrosekunden zur Systemzeit (Ticks)
    
    int nanoSekundenEingabe = this -> intervall * 1000;
    
    int interruptCount = nanoSekundenEingabe / TIME_BASE;
    // Nanosekunden geteilt durch Nanosekunden = keine Einheit
    // -> genau das, was wir als Startzählwert brauchen
    
    // Bitmaske verwenden!
    // Schreiben nun auf die 16 Bits
    this->datenregister.write(interruptCount);
    this->datenregister.write(interruptCount >> 8);
}

