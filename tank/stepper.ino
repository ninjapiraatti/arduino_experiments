#include "tank.h"

const int stepsPerRevolution = 2048;
Stepper myStepper = Stepper(stepsPerRevolution, PIN_ST1, PIN_ST3, PIN_ST2, PIN_ST4);

void setup_stepper() {
	pinMode(PIN_ST1, OUTPUT);
	pinMode(PIN_ST2, OUTPUT);
	pinMode(PIN_ST3, OUTPUT);
	pinMode(PIN_ST4, OUTPUT);
	myStepper.setSpeed(15);
}

void rotate_stepper(int time) {
	myStepper.step(time);
}