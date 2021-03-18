#include "tank.h"

// Define TFT
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCK, TFT_RST);

void setup() 
{
	setup_servo();
	setup_engines();
	setup_stepper();
	setup_wifi();
	tft.initR(INITR_BLACKTAB);  // Initialize a ST7735S chip, black tab
	tft.fillScreen(ST7735_BLACK);  // Fill screen with black
	tft.setTextWrap(false);
	tft.setRotation(1);
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
