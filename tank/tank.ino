#include <DHT_U.h>
#include <DHT.h>

#include "tank.h"
#include "arduino_secrets.h"

// Define wifi
WiFiClient wifiClient;

// Define TFT
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCK, TFT_RST);

void setup() 
{
	int wifiStatus = 2;
	Serial.begin(9600);
	setup_tft(tft);
	tft.fillScreen(ST7735_BLACK);  // Fill screen with black
	tft.setCursor(0, 0);
	tft.setTextColor(ST7735_WHITE);
	tft.println("Henlo. Booting up:");
	tft.setCursor(0, 10);
	tft.print("WiFi:");
	if (setup_wifi(tft) == 0) {
		animationSuccess(tft, 100, 10, 100);
	} else {
		animationFailure(tft, 100, 10, 100);
	}
	tft.setCursor(0, 20);
	tft.print("MQTT:");
	if (setup_mqtt(tft) == 0) {
		animationSuccess(tft, 100, 20, 100);
	} else {
		animationFailure(tft, 100, 20, 100);
	}
	setup_servo();
	setup_engines();
	setup_stepper();
	tft.setCursor(0, 30);
	tft.print("DHT :");
	if (setup_temperature(tft) == 0) {
		animationSuccess(tft, 100, 30, 100);
	} else {
		animationSuccess(tft, 100, 30, 100);
	}
	delay(2000);
	tft.fillScreen(ST7735_BLACK);  // Fill screen with black
}

void loop() 
{
	poll_mqtt(tft);
	turnservo(0);
	tft.fillScreen(ST7735_BLACK);  // Fill screen with black
	tft.setCursor(0, 0);
	//Serial.println("Lol");
	//tft.println("Rotating stepper now."); 
	//delay(1000);
	//rotate_stepper(800);
	//tft.fillScreen(ST7735_BLACK);  // Print a text or value
	//delay(1500);
	//Fturnservo(90);
	//tft.println("Turning servo now."); 
	delay(1500);
	tft.fillScreen(ST7735_BLACK);
	delay(500);
	tft.fillRect(23, 67, 12, 18, ST7735_BLACK);
	tft.println(getWifiQuality());  // Print a text or value
	delay(10000);
}
