/*==================================================================================
	Filename:	Goniometer.hpp
	Version :	Draft A
	Author	:	Roger Thompson
	Date	: 	26-September-2022
==================================================================================*/

/*************************************************************************************
DESCRIPTION

This sketch defines a Class Goniometer, which facilitates the counting of the
pulses from the rotary encoder and converts the count to the number of degrees of arc
through which the goniometer turntable has been rotated.

The goniometer is a simple turntable with an optical rotary encoder directly coupled
to its spindle. The rotary encoder produces 600 pulses/revolution.

The rotary encoder is a 4-wire device and its connecting cable is terminated with a
FIVE pin plug which is wired in a way that makes its orientation unambiguous.

Connections to the ESP32
=========================

Rotary Encoder					Plug Pin         ESP32 Connection
--------------              	--------         ----------------
Red Wire						Pin 1			+5V pin
xxxxxxxxxxxxxxxxxxxxxxxxxxx		Pin 2        	no connection.  (orientation indicator)
Black Wire						Pin 3			Ground pin
White Wire (A-phase pulses)		Pin 4			GPIO pin for COUNT (default = 16)
Green WIre (B-phase pulses)		Pin 5			GPIO pin for DIRECTION (default = 17)

In addition, a press-button switch is wired between Ground and a GPIO pin
(default GPIO 5) to reset the count to zero at any time when the button is pressed

*************************************************************************************/


//--------------------------------------------------------------------------------------
// Include guard
#ifndef GONIOMETER_HPP
#define GONIOMETER_HPP
//--------------------------------------------------------------------------------------

class Goniometer {
	// declare static variables
	static volatile long count;  // count of the number of pulses (+ve = clockwise)
	static int countPin, directionPin, resetPin;
public:
	// Default constructor using default GPIO pin assignments
	Goniometer() {
		count = 0;  // set goniometer count to zero at start
		countPin = 16;
		directionPin = 17;
		resetPin = 5;
	}

	// Constructor with alternative GPIO pin assignments
	Goniometer(int cntPin, int dirPin, int resPin) {
			count = 0;  // set goniometer count to zero at start
			countPin = cntPin;
			directionPin = dirPin;
			resetPin = resPin;
		}

	// method to start the goniometer
	void begin(){
		pinMode(countPin, INPUT_PULLUP);
		pinMode(directionPin, INPUT_PULLUP);
		pinMode(resetPin, INPUT_PULLUP);
		attachInterrupt(digitalPinToInterrupt(countPin), isrPulseCount, RISING);
		attachInterrupt(digitalPinToInterrupt(resetPin), isrReset, FALLING);
	}

	//method to read the rotary encoder COUNT and return the value in degrees of arc
	int readDegrees() {
		return (int(count * 0.6));
	}

	// interrupt service routine for countPin
	static void isrPulseCount(void){
	if(digitalRead(directionPin))
				count--;
			else
				count++;
	}

	// interrupt service routine for resetPin
	static void isrReset(void){
		count = 0;
	}

}; // end of Class Goniometer


// define static variables used by the Goniometer class
volatile long Goniometer::count; // define
int Goniometer::countPin;
int Goniometer::directionPin;
int Goniometer::resetPin;

//-------------------------------------------------------------------------------------
#endif
