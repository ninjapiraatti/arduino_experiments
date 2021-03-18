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
