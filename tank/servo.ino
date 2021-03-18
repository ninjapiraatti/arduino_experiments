#include "tank.h"

// Define number of steps per rotation:
Servo servo;
int angle = 0;

void setup_servo() {
	servo.attach(PIN_SRV);
	servo.write(angle);
}

void turnservo(int angle) {
	servo.write(angle); 
}