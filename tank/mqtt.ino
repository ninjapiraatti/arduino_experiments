const char topic[]  = "test";
const char topic2[]  = "real_unique_topic_2";
const char topic3[]  = "real_unique_topic_3";

DynamicJsonBuffer jb;

// MQTT Callback function
void callback(char* topic, byte* payload, unsigned int length) {
	Serial.print("Message arrived [");
	Serial.print(topic);
	Serial.print("] ");
	JsonObject& root = jb.parseObject(payload);
	//   for (int i=0;i<length;i++) {
	//     tft.print((char)payload[i]);
	//   }
	root.prettyPrintTo(Serial);
	String msg = root["msg"].as<String>();
	int angle = msg.toInt();
	turnservo(angle);
	//Serial.println(root);
	Serial.println(msg);
}

// Define MQTT
PubSubClient mqttclient(TANKKI_URL, TANKKI_PORT, callback, wifiClient);

int setup_mqtt(Adafruit_ST7735 tft) {
	Serial.println("Trying to setup MQTT.");
	animationPending(tft, 100, 20, 100);
	if (mqttclient.connect("arduinoClient", TANKKI_USER, TANKKI_PASS)) {
		mqttclient.setCallback(callback);
		mqttclient.subscribe("test");
	} else {
		animationPending(tft, 100, 20, 1000);
	}
	return(0);
}

int reconnect (Adafruit_ST7735 tft) {
	while (!mqttclient.connected()) {
		Serial.print("Attempting MQTT connection...");
		// Attempt to connect
		if (mqttclient.connect("arduinoClient", TANKKI_USER, TANKKI_PASS)) {
			Serial.println("connected");
			// Once connected, publish an announcement...
			// ... and resubscribe
			mqttclient.subscribe("test");
			return (0);
		} else {
			Serial.println(" try again in 5 seconds");
			return (-1);
		}
	}
}

int poll_mqtt(Adafruit_ST7735 tft) {
	StaticJsonBuffer<300> JSONbuffer;
	JsonObject& JSONencoder = JSONbuffer.createObject();
	
	JSONencoder["device"] = "Arduino nano iot33";
	//JSONencoder["sensorType"] = "Temperature";
	JSONencoder["msg"] = "Henlo iot world";
	JsonArray& values = JSONencoder.createNestedArray("values");
	
	values.add(getHumidity());
	
	char JSONmessageBuffer[100];
	JSONencoder.printTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
	Serial.println("Sending message to MQTT topic..");
	Serial.println(JSONmessageBuffer);
	
	if (mqttclient.publish("test", JSONmessageBuffer) == true) {
		Serial.println("Success sending message");
	} else {
		Serial.println("Error sending message");
	}
	
	mqttclient.loop();
	Serial.println("-------------");
	if (!mqttclient.connected()) {
		reconnect(tft);
		return (-1);
	} else {
		tft.println("MQTT connection OK");
		return (0);
	}
}