#include "tank.h"

char ssid[] = "e33235";        // your network SSID (name)
char pass[] = "231402922";    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;                           // your network key Index number (needed only for WEP)
int status = WL_IDLE_STATUS;
const int GMT = 2; //change this to adapt it to your time zone

void setup_wifi() {
	if (WiFi.status() == WL_NO_MODULE) {
		Serial.println("Communication with WiFi module failed!");
		// don't continue
		while (true);
	}
	byte mac[6];
	WiFi.macAddress(mac);
	Serial.print("MAC: ");
	printMacAddress(mac);
}

void scan_networks()
{
	Serial.println("Scanning available networks...");
	listNetworks();
	delay(1000);
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

