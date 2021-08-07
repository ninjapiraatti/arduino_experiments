#include "tank.h"

// Define TFT
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCK, TFT_RST);

void setup() 
{
	Serial.begin(9600);
	setup_servo();
	setup_engines();
	setup_stepper();
	setup_wifi();
	setup_tft(tft);
	setup_wifi();
}

void loop() 
{
	tft.fillScreen(ST7735_BLACK);  // Fill screen with black
	tft.setCursor(0, 0);
	Serial.println("Lol");
	//tft.println("Rotating stepper now."); 
	//delay(1000);
	//rotate_stepper(800);
	//tft.fillScreen(ST7735_BLACK);  // Print a text or value
	//delay(1500);
	turnservo(90);
	tft.println("Turning servo now."); 
	delay(1000);
	turnservo(120);
	tft.fillScreen(ST7735_BLACK);
	delay(1500);
	tft.fillRect(23, 67, 12, 18, ST7735_BLACK);
	tft.println(getMacAddress());  // Print a text or value
	delay(6000);
}
