/*==================================================================================
	Filename:	Goniometer.ino
	Version :	Draft A
	Author	:	Roger Thompson
	Date	: 	26-September-2022
==================================================================================*/

/*************************************************************************************
DESCRIPTION
===========

The goniometer is a simple turntable with an optical rotary encoder directly coupled
to its spindle. The rotary encoder produces 600 pulses/revolution.

This simple sketch creates an instance of the Class Goniometer, and then prints out
the angle of rotation at 200ms intervals.

*************************************************************************************/

#include "Goniometer.hpp"

// Create an instance of Class Goniometer
Goniometer myGoniometer(16, 17, 5);

void setup() {
	Serial.begin(115200);
	myGoniometer.begin();
	Serial.print("Goniometer set-up is complete");
}


void loop() {
	Serial.println(myGoniometer.readDegrees());
	delay(200);
}
