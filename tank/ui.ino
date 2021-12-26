#include "tank.h"

void animationPending(Adafruit_ST7735 tft, int x, int y, int time) {
	delay(time / 10);
	tft.fillRect(x, y, 10, 10, 0x0000);
	delay(time / 10);
	tft.fillRect(x + 1, y + 1, 2, 2, 0xFFA0);
	delay(time / 10);
	tft.fillRect(x + 1, y + 1, 3, 3, 0xFFA0);
	delay(time / 10);
	tft.fillRect(x + 1, y + 1, 4, 4, 0xFFA0);
	delay(time / 10);
	tft.fillRect(x + 1, y + 1, 5, 5, 0xFFA0);
	delay(time / 10);
	tft.fillRect(x + 1, y + 1, 6, 6, 0xFFA0);
	delay(time / 10);
	tft.fillRect(x + 1, y + 1, 7, 7, 0xFFA0);
	delay(time / 10);
	tft.fillRect(x + 1, y + 1, 8, 8, 0xFFA0);
	delay(time / 10);
}

void animationSuccess(Adafruit_ST7735 tft, int x, int y, int time) {
	delay(time / 10);
	tft.fillRect(x, y, 10, 10, 0x0000);
	delay(time / 10);
	tft.fillRect(x + 1, y + 1, 2, 2, 0x07F6);
	delay(time / 10);
	tft.fillRect(x + 1, y + 1, 3, 3, 0x07F6);
	delay(time / 10);
	tft.fillRect(x + 1, y + 1, 4, 4, 0x07F6);
	delay(time / 10);
	tft.fillRect(x + 1, y + 1, 5, 5, 0x07F6);
	delay(time / 10);
	tft.fillRect(x + 1, y + 1, 6, 6, 0x07F6);
	delay(time / 10);
	tft.fillRect(x + 1, y + 1, 7, 7, 0x07F6);
	delay(time / 10);
	tft.fillRect(x + 1, y + 1, 8, 8, 0x07F6);
	delay(time / 10);
}

void animationFailure(Adafruit_ST7735 tft, int x, int y, int time) {
	delay(time / 10);
	tft.fillRect(x, y, 10, 10, 0x0000);
	delay(time / 10);
	tft.fillRect(x + 1, y + 1, 2, 2, 0xF80C);
	delay(time / 10);
	tft.fillRect(x + 1, y + 1, 3, 3, 0xF80C);
	delay(time / 10);
	tft.fillRect(x + 1, y + 1, 4, 4, 0xF80C);
	delay(time / 10);
	tft.fillRect(x + 1, y + 1, 5, 5, 0xF80C);
	delay(time / 10);
	tft.fillRect(x + 1, y + 1, 6, 6, 0xF80C);
	delay(time / 10);
	tft.fillRect(x + 1, y + 1, 7, 7, 0xF80C);
	delay(time / 10);
	tft.fillRect(x + 1, y + 1, 8, 8, 0xF80C);
	delay(time / 10);
}