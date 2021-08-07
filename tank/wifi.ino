#include "tank.h"

char ssid[] = "4G-Gateway-EF11";        // your network SSID (name)
char pass[] = "M6EQEH92A7G";    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;                           // your network key Index number (needed only for WEP)
int status = WL_IDLE_STATUS;
const int GMT = 2; //change this to adapt it to your time zone
WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);
// MQTT
const char broker[] = "hairdresser.cloudmqtt.com";
int        port     = 16995;
const char topic[]  = "test";
const char topic2[]  = "real_unique_topic_2";
const char topic3[]  = "real_unique_topic_3";

void setup_wifi() {
	Serial.println("Trying to setup wifi.");
	if (WiFi.status() == WL_NO_MODULE) {
		Serial.println("Communication with WiFi module failed!");
		// don't continue
		while (true);
	}
	byte mac[6];
	WiFi.macAddress(mac);
	Serial.print("MAC: ");
	printMacAddress(mac);
	scan_networks();
	if (!mqttClient.connect(broker, port)) {
		Serial.print("MQTT connection failed! Error code = ");
		Serial.println(mqttClient.connectError());

		while (1);
	}
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

char *getWifiQuality() {
	return ("Lol again.");
}

void poll_mqtt() {
	mqttClient.beginMessage(topic);
    mqttClient.print("hei");
    mqttClient.endMessage();

    mqttClient.beginMessage(topic2);
    mqttClient.print("heitaas");
    mqttClient.endMessage();

    mqttClient.beginMessage(topic3);
    mqttClient.print("heiviela");
    mqttClient.endMessage();
	mqttClient.poll();
}

