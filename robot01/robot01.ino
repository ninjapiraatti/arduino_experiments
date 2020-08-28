
// Define Pins
#define PIN_E1 3
#define PIN_E2 4
#define PIN_E3 5
#define PIN_E4 6
#define PIN_ENA 9
#define PIN_ENB 10
#define TRIG_PIN 7
#define ECHO_PIN 8
#define MAX_DIST 23200
#define MAX_THROTTLE 200
#define MIN_THROTTLE 120
#define PING_INTERVAL 20

unsigned long time;
unsigned long settime;
float cm;

void setup() 
{
    pinMode(PIN_E1, OUTPUT);
    pinMode(PIN_E2, OUTPUT);
    pinMode(PIN_E3, OUTPUT);
    pinMode(PIN_E4, OUTPUT);
    pinMode(PIN_ENA, OUTPUT);
    pinMode(PIN_ENB, OUTPUT);

    // The Trigger pin will tell the sensor to range find
    pinMode(TRIG_PIN, OUTPUT);
    digitalWrite(TRIG_PIN, LOW);

    //Set Echo pin as input to measure the duration of 
    //pulses coming back from the distance sensor
    pinMode(ECHO_PIN, INPUT);

    // We'll use the serial monitor to view the sensor output
    Serial.begin(9600);

}

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

void stopengines(int time)
{
    analogWrite(PIN_ENA, 0);
    analogWrite(PIN_ENB, 0);
    delay(time);
}

int wavefunction()
{
    float wave = millis()/2000.0;
    int value = 100.0 + 50 * sin( wave * 2.0 * PI  );
    return (value);
}

float ping()
{
    unsigned long t1;
    unsigned long t2;
    unsigned long pulse_width;
    float cm;
    float inches;

    // Hold the trigger pin high for at least 10 us
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    // Wait for pulse on echo pin
    while ( digitalRead(ECHO_PIN) == 0 );

    // Measure how long the echo pin was held high (pulse width)
    // Note: the micros() counter will overflow after ~70 min
    t1 = micros();
    while ( digitalRead(ECHO_PIN) == 1);
    t2 = micros();
    pulse_width = t2 - t1;

    // Calculate distance in centimeters and inches. The constants
    // are found in the datasheet, and calculated from the assumed speed
    //of sound in air at sea level (~340 m/s).
    cm = pulse_width / 58.0;
    inches = pulse_width / 148.0;

    // Print out results
    if ( pulse_width > MAX_DIST) {
        Serial.println("MAX DIST");
    } 
    else {
        Serial.print(cm);
        Serial.print(" cm \t");
        Serial.print(inches);
        Serial.println(" in");
    }
    return (cm);
}

void loop() 
{
    if (cm < MAX_DIST && cm > 50.0)
        settime = millis();
    time =  millis();
    if (time % PING_INTERVAL == 0)
        cm = ping();
    if (cm > 50.0 && (millis() - settime < 5000)) {
        goforward();
    }
    else if (cm > 15.0)
    {
        stopengines(10);
        turnleft(100);
        stopengines(800);
        turnright(200);
        stopengines(800);
        turnleft(300);
        stopengines(500);
        cm = ping();
    }
    else {
        gobackward(400);
        turnleft(200);
        cm = ping();
    }
}