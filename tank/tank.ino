
#include <Stepper.h>
// Define Pins
#define PIN_IN1 10
#define PIN_IN2 9
#define PIN_IN3 8
#define PIN_IN4 7
#define PIN_ST1 6
#define PIN_ST2 5
#define PIN_ST3 4
#define PIN_ST4 3
#define PIN_ENA A0
#define PIN_ENB A1
#define MAX_THROTTLE 255
#define MIN_THROTTLE 120

// Define number of steps per rotation:
const int stepsPerRevolution = 2048;

Stepper myStepper = Stepper(stepsPerRevolution, PIN_ST1, PIN_ST3, PIN_ST2, PIN_ST4); // Why are they in this order I do not know

void setup() 
{
  pinMode(PIN_IN1, OUTPUT);
  pinMode(PIN_IN2, OUTPUT);
  pinMode(PIN_IN3, OUTPUT);
  pinMode(PIN_IN4, OUTPUT);
  pinMode(PIN_ST1, OUTPUT);
  pinMode(PIN_ST2, OUTPUT);
  pinMode(PIN_ST3, OUTPUT);
  pinMode(PIN_ST4, OUTPUT);
  pinMode(PIN_ENA, OUTPUT);
  pinMode(PIN_ENB, OUTPUT);
  myStepper.setSpeed(15);

  // We'll use the serial monitor to view the sensor output
  Serial.begin(9600);

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
  myStepper.step(1000); 
  delay(time);
}

void stopengines(int time)
{
  analogWrite(PIN_ENA, 0);
  analogWrite(PIN_ENB, 0);
  delay(time);
}

void loop() 
{
  Serial.print("Engine loop begin\n");
  gobackward(1000);
  stopengines(10);
  turnleft(100);
  stopengines(800);
  turnright(200);
  stopengines(800);
  turnleft(300);
  stopengines(500);
}
