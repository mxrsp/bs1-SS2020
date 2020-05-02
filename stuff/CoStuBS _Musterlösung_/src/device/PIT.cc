/*
 * PIT.cc
 *
 *  Created on: 24.05.2019
 *      Author: Tom
 */
#include "device/PIT.h"

PIT::PIT(int us) : intervals (us) ,control(PIT::CONTROL_PORT), data(PIT::DATA_PORT) {

}
//23866 ist die zweit die für 20 ms intervalle benötigt wird
PIT::PIT() :  intervals (23866) ,control(PIT::CONTROL_PORT), data(PIT::DATA_PORT) {

}

void PIT::interval(int us) {



	if (us < 0) {
		us = -us;
	}

	if (us > 0) {
		this->intervals = us;
		int count = (us*1000)/838;
		this->control.write(0x34);
		this->data.write(count & 0xFF);
		this->data.write(count >> 8);
	}

}

int PIT :: getInterval(){

	return this->intervals;
}


