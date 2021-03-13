// This code is largely adapted from https://randomnerdtutorials.com/esp8266-dht11dht22-temperature-and-humidity-web-server-with-arduino-ide/

//#include <LiquidCrystal.h>
#include <DHT.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ESP8266WiFi.h>

// LEDS
#define LED_1 D0
#define LED_2 D1
#define LED_3 D4
#define LED_4 D5
#define LED_5 D6
#define LED_6 D7

// LCD

// Set dht12 i2c comunication on default Wire pin
#define DHTPIN D3
#define DHTTYPE    DHT11     // DHT 11

DHT dht(DHTPIN, DHTTYPE);
//LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const char* ssid = "TP-LINK_ABE16A";
const char* password = "";

// current temperature & humidity, updated in loop()
float t = 0.0;
float h = 0.0;

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

unsigned long previousMillis = 0;    // will store last time DHT was updated
const long interval = 1000; // Updates DHT readings every 1 seconds

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.7.2/css/all.css" integrity="sha384-fnmOCqbTlWIlj8LyTjo7mOUStjsKC4pOpQbqyi7RrhN7udi9RwhKkMHpvLbHG9Sr" crossorigin="anonymous">
  <style>
    html {
     font-family: Arial;
     display: inline-block;
     margin: 0px auto;
     text-align: center;
    }
    h2 { font-size: 3.0rem; }
    p { font-size: 3.0rem; }
    .units { font-size: 1.2rem; }
    .dht-labels{
      font-size: 1.5rem;
      vertical-align:middle;
      padding-bottom: 15px;
    }
  </style>
</head>
<body>
  <h2>ESP8266 DHT Server</h2>
  <p>
    <i class="fas fa-thermometer-half" style="color:#059e8a;"></i> 
    <span class="dht-labels">Temperature</span> 
    <span id="temperature">%TEMPERATURE%</span>
    <sup class="units">&deg;C</sup>
  </p>
  <p>
    <i class="fas fa-tint" style="color:#00add6;"></i> 
    <span class="dht-labels">Humidity</span>
    <span id="humidity">%HUMIDITY%</span>
    <sup class="units">%</sup>
  </p>
</body>
<script>
setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("temperature").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/temperature", true);
  xhttp.send();
}, 10000 ) ;
setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("humidity").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/humidity", true);
  xhttp.send();
}, 10000 ) ;
</script>
</html>)rawliteral";

// Replaces placeholder with DHT values
String processor(const String& var){
  //Serial.println(var);
  if(var == "TEMPERATURE"){
    return String(t);
  }
  else if(var == "HUMIDITY"){
    return String(h);
  }
  return String();
}

void setup()
{
	Serial.begin(115200);
	// Start sensor
	dht.begin();
    pinMode(LED_1, OUTPUT);
    pinMode(LED_2, OUTPUT);
    pinMode(LED_3, OUTPUT);
    pinMode(LED_4, OUTPUT);
    pinMode(LED_5, OUTPUT);
    pinMode(LED_6, OUTPUT);

    // Connect to Wi-Fi
    WiFi.begin(ssid, password);
    Serial.println("Connecting to WiFi");
    while (WiFi.status() != WL_CONNECTED) {
        Serial.println(".");
        digitalWrite(LED_2, HIGH);
        delay(200);
        digitalWrite(LED_2, LOW);
        digitalWrite(LED_4, HIGH);
        delay(200);
        digitalWrite(LED_4, LOW);
        digitalWrite(LED_6, HIGH);
        delay(200);
        digitalWrite(LED_6, LOW);
    }

    // Print ESP8266 Local IP Address
    Serial.println(WiFi.localIP());

    // Route for root / web page
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send_P(200, "text/html", index_html, processor);
    });
    server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send_P(200, "text/plain", String(t).c_str());
    });
    server.on("/humidity", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send_P(200, "text/plain", String(h).c_str());
    });

    // Start server
    server.begin();
}

void loop(){  
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
        // save the last time you updated the DHT values
        previousMillis = currentMillis;
        // Read temperature as Celsius (the default)
        float newT = dht.readTemperature();
        // Read temperature as Fahrenheit (isFahrenheit = true)
        //float newT = dht.readTemperature(true);
        // if temperature read failed, don't change t value
        if (isnan(newT)) {
            Serial.println("Failed to read from DHT sensor!");
        }
        else {
            t = newT;
            Serial.println(t);
        }
        // Read Humidity
        float newH = dht.readHumidity();
        // if humidity read failed, don't change h value 
        if (isnan(newH)) {
            Serial.println("Failed to read from DHT sensor!");
        }
        else {
            h = newH;
            Serial.println(h);
        }
        digitalWrite(LED_1, HIGH);
        digitalWrite(LED_3, HIGH);
        digitalWrite(LED_5, HIGH);
        delay(100);
        digitalWrite(LED_1, LOW);
        digitalWrite(LED_3, LOW);
        digitalWrite(LED_5, LOW);
        delay(2000);
    }
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println(".");
        digitalWrite(LED_2, HIGH);
        delay(200);
        digitalWrite(LED_2, LOW);
        digitalWrite(LED_4, HIGH);
        delay(200);
        digitalWrite(LED_4, LOW);
        digitalWrite(LED_6, HIGH);
        delay(200);
        digitalWrite(LED_6, LOW);
    }
    else
    {
        Serial.println(WiFi.localIP());
    }
}