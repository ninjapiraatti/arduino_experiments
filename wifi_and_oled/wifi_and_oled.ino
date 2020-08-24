#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP8266WiFi.h>

const char* ssid     = "e33235";         // The SSID (name) of the Wi-Fi network you want to connect to
const char* password = "231402922";     // The password of the Wi-Fi network

// Rotary stuff
#define CLK 14
#define DT 12
#define SW 16
int counter = 0;
int currentStateCLK;
int lastStateCLK;
String currentDir ="";
unsigned long lastButtonPress = 0;

// RGB LED
//#define ledR 3
//#define ledG 4
//#define ledB 5


Adafruit_SSD1306 display = Adafruit_SSD1306(128, 32, &Wire);

// OLED FeatherWing buttons map to different pins depending on board:
#if defined(ESP8266)
  #define BUTTON_A  0
  #define BUTTON_B 16
  #define BUTTON_C  2
#endif

int pin = 0;
int i = 0;

void setup() {

    // Rotary encoder

    //pinMode(CLK,INPUT);
    //pinMode(DT,INPUT);
    //pinMode(SW, INPUT_PULLUP);

    // initialize GPIO 2 as an output.
    pinMode(pin, OUTPUT);
    Wire.begin(); 
    Serial.begin(115200);
    WiFi.begin(ssid, password);

    // Oled stuff

    Serial.println("OLED FeatherWing test");
    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Address 0x3C for 128x32

    Serial.println("OLED begun");

    // Show image buffer on the display hardware.
    // Since the buffer is intialized with an Adafruit splashscreen
    // internally, this will display the splashscreen.
    display.display();
    delay(1000);

    // Clear the buffer.
    display.clearDisplay();
    display.display();

    Serial.println("IO test");

    // text display tests
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0,0);
    display.print("Connecting to SSID\n'adafruit':");
    display.print("connected!");
    display.println("IP: 10.0.1.23");
    display.println("Sending val #0");
    display.setCursor(0,0);
    display.display(); // actually display all of the above
}

void checkForRotary() {
   while(inrotary == 1) {
        // Read the current state of CLK
        currentStateCLK = digitalRead(CLK);
       
        // If last and current state of CLK are different, then pulse occurred
        // React to only 1 state change to avoid double count
        if (currentStateCLK != lastStateCLK  && currentStateCLK == 1){
        // If the DT state is different than the CLK state then
        // the encoder is rotating CCW so decrement
            if (digitalRead(DT) != currentStateCLK) {
                counter --;
                currentDir ="CCW";
            } else {
            // Encoder is rotating CW so increment
            counter ++;
            currentDir ="CW";
            }
            display.clearDisplay();
            display.setCursor(0,0);
            display.print(currentDir);
            display.print(" | ");
            display.println(counter);
            display.display();
            delay(100);
        }

        // Remember last CLK state
        lastStateCLK = currentStateCLK;

        // Read the button state
        int btnState = digitalRead(SW);

        //If we detect LOW signal, button is pressed
        if (btnState == LOW) {
        //if 50ms have passed since last LOW pulse, it means that the
        //button has been pressed, released and pressed again
            if (millis() - lastButtonPress > 50) {
                    display.clearDisplay();
                    display.setCursor(0,0);
                    display.println("Button pressed!");
                    display.display();
                    delay(100);
            }
            else {
                display.clearDisplay();
                    display.setCursor(0,0);
                    display.println("Press a button.");
                    display.display();
                    delay(100);
            }
            // Remember last button press event
            lastButtonPress = millis();
        }
        // Put in a slight delay to help debounce the reading
        delay(1);
    }
}

void wifiStatus() {
    while (WiFi.status() != WL_CONNECTED) { // Wait for the Wi-Fi to connect
        display.print(++i); Serial.print(' ');
        display.display();
        display.setCursor(0,0);
        delay(100);
        display.clearDisplay();
    }
    display.clearDisplay();
    display.setCursor(0,0);
    display.println("We has connection.");  
    display.println("IP address:");
    display.println(WiFi.localIP()); 
    display.display();
    delay(100);
}

void loop() {
    checkForRotary();
    delay(1000);
    wifiStatus();
}