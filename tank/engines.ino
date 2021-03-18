#include "tank.h"

void setup_engines() {
	pinMode(PIN_IN1, OUTPUT);
	pinMode(PIN_IN2, OUTPUT);
	pinMode(PIN_IN3, OUTPUT);
	pinMode(PIN_IN4, OUTPUT);
	pinMode(PIN_ENA, OUTPUT);
	pinMode(PIN_ENB, OUTPUT);
}

void turnright(int time)
{
	analogWrite(PIN_ENA, MAX_THROTTLE);
	analogWrite(PIN_ENB, MAX_THROTTLE);
	digitalWrite(PIN_IN1, HIGH);
	digitalWrite(PIN_IN2, LOW);
	digitalWrite(PIN_IN3, HIGH);
	digitalWrite(PIN_IN4, LOW);
	delay(time);
}

void turnleft(int time)
{
	analogWrite(PIN_ENA, MAX_THROTTLE);
	analogWrite(PIN_ENB, MAX_THROTTLE);
	digitalWrite(PIN_IN1, LOW);
	digitalWrite(PIN_IN2, HIGH);
	digitalWrite(PIN_IN3, LOW);
	digitalWrite(PIN_IN4, HIGH);
	delay(time);
}

void goforward()
{
	analogWrite(PIN_ENA, MIN_THROTTLE);
	analogWrite(PIN_ENB, MAX_THROTTLE);
	digitalWrite(PIN_IN1, LOW);
	digitalWrite(PIN_IN2, HIGH);
	digitalWrite(PIN_IN3, HIGH);
	digitalWrite(PIN_IN4, LOW);
}

void gobackward(int time)
{
	analogWrite(PIN_ENA, MAX_THROTTLE);
	analogWrite(PIN_ENB, MAX_THROTTLE);
	digitalWrite(PIN_IN1, HIGH);
	digitalWrite(PIN_IN2, LOW);
	digitalWrite(PIN_IN3, LOW);
	digitalWrite(PIN_IN4, HIGH);
	delay(time);
}

void stopengines(int time)
{
	analogWrite(PIN_ENA, 0);
	analogWrite(PIN_ENB, 0);
	delay(time);
}