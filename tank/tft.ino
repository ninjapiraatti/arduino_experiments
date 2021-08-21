#include "tank.h"

void setup_tft(Adafruit_ST7735 tft) {
	tft.initR(INITR_BLACKTAB);  // Initialize a ST7735S chip, black tab
	tft.fillScreen(ST7735_BLACK);  // Fill screen with black
	tft.setTextWrap(false);
	tft.setRotation(1);
	tft.setCursor(0, 0);  // Set position (x,y)
	tft.setTextColor(ST7735_WHITE);  // Set color of text. First is the color of text and after is color of background
	tft.setTextSize(1);  // Set text size. Goes from 0 (the smallest) to 20 (very big)
	tft.println("Hello");  // Print a text or value
	tft.setTextSize(0);  // Set text size. We are using custom font so you should always set text size as 0
	tft.setCursor(0, 50);  // Set position (x,y)
	tft.setTextColor(ST7735_RED);  // Set color of text. We are using custom font so there is no background color supported
	tft.println("World!");  // Print a text or value
	tft.setCursor(0, 70);
	tft.setTextColor(ST7735_GREEN);  // Set color of text. We are using custom font so there is no background color supported
	tft.println("If you can read this, tft works");  // Print a text or value
	delay(1000);
	tft.fillScreen(ST7735_BLACK); 
}

void showMessage(char *msg, int milliseconds, bool resetscreen) {
	if (resetscreen == true) {
		tft.fillScreen(ST7735_BLACK);
		tft.setCursor(0, 0);
	}
	tft.setTextColor(ST7735_WHITE);
	tft.print(msg);
	delay(milliseconds);
}