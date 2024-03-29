#include "tank.h"

int keyIndex = 0;
int status = WL_IDLE_STATUS;
const int GMT = 2; //change this to adapt it to your time zone

int setup_wifi(Adafruit_ST7735 tft) {
	Serial.println("Trying to setup wifi.");
	animationPending(tft, 100, 10, 500);
	if (WiFi.status() == WL_NO_MODULE) {
		Serial.println("Communication with WiFi module failed!");
		// don't continue
		// while (true);
		return (-1);
	}
	byte mac[6];
	WiFi.macAddress(mac);
	Serial.print("MAC: ");
	printMacAddress(mac);
	scan_networks(tft);
	if (WiFi.begin(SSID, PASS) != WL_CONNECTED) {
		return (-1);
	}
	return (0);
}

void scan_networks(Adafruit_ST7735 tft)
{
	Serial.println("Scanning available networks...");
	listNetworks();
	animationPending(tft, 100, 10, 500);
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

char *getWifiQuality() {
	//return ("Lol again.");
}

