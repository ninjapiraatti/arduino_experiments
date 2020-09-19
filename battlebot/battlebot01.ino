#include <Servo.h>
#include <Dabble.h>

#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
// Define Pins
#define PIN_JOY_X A0
#define PIN_JOY_Y A1
#define PIN_SERVO 10
#define PIN_E1 6
#define PIN_E2 9
#define PIN_RX 2
#define PIN_TX 3

Servo seppo;

unsigned long time;
unsigned long settime;
float cm;

void setup()
{
 Serial.begin(9600);
 Dabble.begin(9600);
 seppo.attach(10);
 seppo.write(90); 
}

/*
void turnright(int time)
{
    analogWrite(PIN_ENA, MAX_THROTTLE);
    analogWrite(PIN_ENB, MAX_THROTTLE);
    digitalWrite(PIN_E1, HIGH);
    digitalWrite(PIN_E2, LOW);
    digitalWrite(PIN_E3, HIGH);
    digitalWrite(PIN_E4, LOW);
    delay(time);
}

void turnleft(int time)
{
    analogWrite(PIN_ENA, MAX_THROTTLE);
    analogWrite(PIN_ENB, MAX_THROTTLE);
    digitalWrite(PIN_E1, LOW);
    digitalWrite(PIN_E2, HIGH);
    digitalWrite(PIN_E3, LOW);
    digitalWrite(PIN_E4, HIGH);
    delay(time);
}

void goforward()
{
    analogWrite(PIN_ENA, MIN_THROTTLE);
    analogWrite(PIN_ENB, MAX_THROTTLE);
    digitalWrite(PIN_E1, LOW);
    digitalWrite(PIN_E2, HIGH);
    digitalWrite(PIN_E3, HIGH);
    digitalWrite(PIN_E4, LOW);
}

void gobackward(int time)
{
    analogWrite(PIN_ENA, MAX_THROTTLE);
    analogWrite(PIN_ENB, MAX_THROTTLE);
    digitalWrite(PIN_E1, HIGH);
    digitalWrite(PIN_E2, LOW);
    digitalWrite(PIN_E3, LOW);
    digitalWrite(PIN_E4, HIGH);
    delay(time);
}
*/

void loop()
{                    
   Dabble.processInput();             //this function is used to refresh data obtained from smartphone.Hence calling this function is mandatory in order to get data properly from your mobile.
  Serial.print("KeyPressed: ");
  if (GamePad.isUpPressed())
  {
    Serial.print("UP");
  }

  if (GamePad.isDownPressed())
  {
    Serial.print("DOWN");
  }

  if (GamePad.isLeftPressed())
  {
    Serial.print("Left");
  }

  if (GamePad.isRightPressed())
  {
    Serial.print("Right");
  }

  if (GamePad.isSquarePressed())
  {
    Serial.print("Square");
  }

  if (GamePad.isCirclePressed())
  {
    Serial.print("Circle");
  }

  if (GamePad.isCrossPressed())
  {
    Serial.print("Cross");
  }

  if (GamePad.isTrianglePressed())
  {
    Serial.print("Triangle");
  }

  if (GamePad.isStartPressed())
  {
    Serial.print("Start");
  }

  if (GamePad.isSelectPressed())
  {
    Serial.print("Select");
  }
  Serial.print('\t');

  int a = GamePad.getAngle();
  Serial.print("Angle: ");
  Serial.print(a);
  Serial.print('\t');
  int b = GamePad.getRadius();
  Serial.print("Radius: ");
  Serial.print(b);
  Serial.print('\t');
  float c = GamePad.getXaxisData();
  Serial.print("x_axis: ");
  Serial.print(c);
  Serial.print('\t');
  float d = GamePad.getYaxisData();
  Serial.print("y_axis: ");
  Serial.println(d);

 //Serial.print(joystickXVal);                //print the value from A1
 //Serial.print(" = input from joystick | ");  //print "=input from joystick" next to the value
 //Serial.print(joystickXVal / 5.668);       //print a from A1 calculated, scaled value
 //Serial.println(" = output to servo");      //print "=output to servo" next to the value
 seppo.write((c + 7) * 11);
}