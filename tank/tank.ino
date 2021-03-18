
#include "tank.h"

char ssid[] = "e33235";        // your network SSID (name)
char pass[] = "231402922";    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;                           // your network key Index number (needed only for WEP)

int status = WL_IDLE_STATUS;

const int GMT = 2; //change this to adapt it to your time zone

// Define number of steps per rotation:
const int stepsPerRevolution = 2048;

// Define TFT
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCK, TFT_RST);

Servo servo;
Stepper myStepper = Stepper(stepsPerRevolution, PIN_ST1, PIN_ST3, PIN_ST2, PIN_ST4);
int angle = 0;

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
	servo.attach(PIN_SRV);
	servo.write(angle);

	tft.initR(INITR_BLACKTAB);  // Initialize a ST7735S chip, black tab
	tft.fillScreen(ST7735_BLACK);  // Fill screen with black
	tft.setTextWrap(false);
	tft.setCursor(0, 0);  // Set position (x,y)
	tft.setTextColor(ST7735_WHITE);  // Set color of text. First is the color of text and after is color of background
	tft.setTextSize(1);  // Set text size. Goes from 0 (the smallest) to 20 (very big)
	tft.println("Hello");  // Print a text or value
	// Start using a custom font:
	tft.setTextSize(0);  // Set text size. We are using custom font so you should always set text size as 0
	// Write to the display the text "World":
	tft.setCursor(0, 50);  // Set position (x,y)
	tft.setTextColor(ST7735_RED);  // Set color of text. We are using custom font so there is no background color supported
	tft.println("World!");  // Print a text or value
	// Stop using a custom font:
	tft.setFont();  // Reset to standard font, to stop using any custom font previously set

	// We'll use the serial monitor to view the sensor output
	Serial.begin(9600);
	if (WiFi.status() == WL_NO_MODULE) {
		Serial.println("Communication with WiFi module failed!");
		// don't continue
		while (true);
	}
	byte mac[6];
	WiFi.macAddress(mac);
	Serial.print("MAC: ");
	printMacAddress(mac);
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

void scan_networks()
{
	Serial.println("Scanning available networks...");
	listNetworks();
	delay(1000);
}

void listNetworks() {
	// scan for nearby networks:
	Serial.println("** Scan Networks **");
	int numSsid = WiFi.scanNetworks();
	if (numSsid == -1) {
		Serial.println("Couldn't get a wifi connection");
		while (true);
	}

	// print the list of networks seen:
	Serial.print("number of available networks:");
	Serial.println(numSsid);

	// print the network number and name for each network found:
	for (int thisNet = 0; thisNet < numSsid; thisNet++) {
		Serial.print(thisNet);
		Serial.print(") ");
		Serial.print(WiFi.SSID(thisNet));
		Serial.print("\tSignal: ");
		Serial.print(WiFi.RSSI(thisNet));
		Serial.print(" dBm");
		Serial.print("\tEncryption: ");
		printEncryptionType(WiFi.encryptionType(thisNet));
	}
}
 
void printEncryptionType(int thisType) {
	// read the encryption type and print out the name:
	switch (thisType) {
	case ENC_TYPE_WEP:
		Serial.println("WEP");
		break;
	case ENC_TYPE_TKIP:
		Serial.println("WPA");
		break;
	case ENC_TYPE_CCMP:
		Serial.println("WPA2");
		break;
	case ENC_TYPE_NONE:
		Serial.println("None");
		break;
	case ENC_TYPE_AUTO:
		Serial.println("Auto");
		break;
	case ENC_TYPE_UNKNOWN:
	default:
		Serial.println("Unknown");
		break;
	}
}
 
 
void printMacAddress(byte mac[]) {
	for (int i = 5; i >= 0; i--) {
		if (mac[i] < 16) {
			Serial.print("0");
		}
		Serial.print(mac[i], HEX);
		if (i > 0) {
			Serial.print(":");
		}
	}
	Serial.println();
}

void loop() 
{
	/*
	Serial.print("Engine loop begin\n");
	for(angle = 10; angle < 180; angle++)  
	{                                  
	servo.write(angle);   
	Serial.print("Turning servo at");
	Serial.print(angle);
	delay(15);                   
	}
	scan_networks();
	gobackward(1000);
	stopengines(10);
	turnleft(100);
	stopengines(800);
	turnright(200);
	stopengines(800);
	turnleft(300);
	stopengines(500);
	*/
	tft.fillRect(23, 67, 12, 18, ST7735_BLACK);
	tft.println("Hello");  // Print a text or value
}
