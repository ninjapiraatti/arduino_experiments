#include "tank.h"
#include "arduino_secrets.h"

// MQTT Callback function
void callback(char* topic, byte* payload, unsigned int length) {
  // handle message arrived
}

// Define wifi
WiFiClient wifiClient;

// Define TFT
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCK, TFT_RST);

// Define MQTT
PubSubClient mqttclient(TANKKI_URL, TANKKI_PORT, callback, wifiClient);

void setup() 
{
	Serial.begin(9600);
	setup_tft(tft);
	setup_wifi();
	setup_mqtt();
	setup_servo();
	setup_engines();
	setup_stepper();
}

void loop() 
{
	tft.fillScreen(ST7735_BLACK);  // Fill screen with black
	tft.setCursor(0, 0);
	//Serial.println("Lol");
	//tft.println("Rotating stepper now."); 
	//delay(1000);
	//rotate_stepper(800);
	//tft.fillScreen(ST7735_BLACK);  // Print a text or value
	//delay(1500);
	turnservo(90);
	//tft.println("Turning servo now."); 
	delay(500);
	turnservo(120);
	tft.fillScreen(ST7735_BLACK);
	delay(500);
	tft.fillRect(23, 67, 12, 18, ST7735_BLACK);
	tft.println(getWifiQuality());  // Print a text or value
	delay(500);
	poll_mqtt();
}
