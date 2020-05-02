/*
 * Clock.cc
 *
 *  Created on: 24.05.2019
 *      Author: Tom
 */
#include "device/Clock.h"

//CgaChannel cga;		  // unser CGA-Ausgabekanal benötigt für Propeller, sonst nicht
//PrintStream out(cga);

Clock::Clock() :Gate(Timer), tickAmount(0){
	this->tickAmount = 0;
}

Clock::Clock(int us) :	Gate(Timer), tickAmount(0){
	this->tickAmount = 0;
	windup(us);

}

void Clock::windup(int us) {
	this->tickAmount = 0;
	if (us > 0xFFFF) {
	pit.interval(0xFFFF);
	} else {
	pit.interval(us);
	}
	pic.enable(PIC::PIT);

}

bool Clock::prologue() {

	this->tickAmount++;
	pic.ack(PIC::PIT);
	return true;

}
void Clock::epilogue() {


	scheduler.checkslice();


}


//Propeller -> nicht löschen!!!!!!!!!

 	//Anzahl an zwanziger Milisek!
	//int second = tickAmount ;
/*
	if ((second) % 4 == 0) {
		cga.setCursorBegin();
		out.print("|");

	} else

	if ((second) % 4  == 1) {
		cga.setCursorBegin();
		out.print("/");

	} else

	if ((second) % 4 == 2) {
		cga.setCursorBegin();
		out.print("-");

	} else
		if ((second) % 4 == 3) {
		cga.setCursorBegin();
		out.print("\\");

	}
*/


