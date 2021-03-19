#include "tank.h"

// Define TFT
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCK, TFT_RST);

void setup() 
{
	setup_servo();
	setup_engines();
	setup_stepper();
	setup_wifi();
	setup_tft(tft);
	Serial.begin(9600);
}

void loop() 
{
	tft.fillScreen(ST7735_BLACK);  // Fill screen with black
	tft.setCursor(0, 0);
	tft.println("Henlo");  // Print a text or value
	//rotate_stepper(200);
	//delay(500);
	//turnservo(150);
	//delay(500);
	//turnservo(0);
	tft.fillRect(23, 67, 12, 18, ST7735_BLACK);
	tft.println("Hello");  // Print a text or value
	delay(2000);
}
