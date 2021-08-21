const char topic[]  = "test";
const char topic2[]  = "real_unique_topic_2";
const char topic3[]  = "real_unique_topic_3";



void setup_mqtt() {
	Serial.println("Trying to setup MQTT.");
	if (mqttclient.connect("arduinoClient", TANKKI_USER, TANKKI_PASS)) {
		mqttclient.subscribe("test");
		tft.println("Connected to Heroku");
		delay(5000);
	} else {
		tft.println("NO MQTT");
		delay(5000);
	}
}

void reconnect () {
	while (!mqttclient.connected()) {
		Serial.print("Attempting MQTT connection...");
		// Attempt to connect
		if (mqttclient.connect("arduinoClient", TANKKI_USER, TANKKI_PASS)) {
			Serial.println("connected");
			// Once connected, publish an announcement...
			// ... and resubscribe
			mqttclient.subscribe("test");
		} else {
			tft.fillScreen(ST7735_BLACK);  // Fill screen with black
			tft.setCursor(0, 0);
			tft.println("failed, rc=");
			tft.print(mqttclient.state());
			Serial.println(" try again in 5 seconds");
		// Wait 5 seconds before retrying
		delay(5000);
		}
	}
}

void poll_mqtt() {
	StaticJsonBuffer<300> JSONbuffer;
	JsonObject& JSONencoder = JSONbuffer.createObject();
	
	JSONencoder["device"] = "Arduino nano iot33";
	//JSONencoder["sensorType"] = "Temperature";
	JSONencoder["msg"] = "Henlo iot world";
	JsonArray& values = JSONencoder.createNestedArray("values");
	
	values.add(20);
	values.add(21);
	values.add(23);
	
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
		reconnect();
	} else {
		tft.println("MQTT connection OK");
	}
	
	delay(10000);
}