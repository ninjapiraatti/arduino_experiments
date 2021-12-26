#include "tank.h"

DHT dht(PIN_TEMPERATURE, DHT11);

int setup_temperature(Adafruit_ST7735 tft) {
	animationPending(tft, 100, 30, 100);
	dht.begin();
}

void getHumidity () {
	float newH = dht.readHumidity();
	Serial.println(newH);
	data.humidity = newH;
}