#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP8266WiFi.h>

// Rotary definitions and variables
#define CLK 14
#define DT 12
#define SW 13 // Didn't work on pin 16 for some reason. Reserved for some NodeMCU function? The onboard led lit up from this input

// RGB LED
#define LED_R 3
#define LED_G 0
#define LED_B 2

// MENU DEFS
#define MENU_MIN 1
#define MENU_MAX 3

struct option {
    char    *name;
    int     (*action)(void);
};

struct menu {
    char    *name;
    int     i;
    option  optn;
};

// Oled declaration
Adafruit_SSD1306 display = Adafruit_SSD1306(128, 32, &Wire);

int currentStateCLK;
int lastStateCLK;
String currentDir ="";
unsigned long lastButtonPress = 0;
int btnState = digitalRead(SW);
const char* ssid     = "e33235";         // The SSID (name) of the Wi-Fi network you want to connect to
const char* password = "231402922";     // The password of the Wi-Fi network

int scrollMessage(void) {
    display.clearDisplay();
    display.setCursor(0,0);
    display.println("Lorem ipsum dolor sit amet viela vahan lisaa tekstia jotta skrolli nakyy.");
    display.display();
    display.startscrollleft(0x00, 0x0F);
    delay(5000);
    display.stopscroll();
}

int ledBlue(void) {
    analogWrite(LED_G, 255);
    return (0);
}

int wifiStatus() {
    int i = 1000;
    while (WiFi.status() != WL_CONNECTED) { // Wait for the Wi-Fi to connect
        display.println("Trying to connect...");
        display.print(--i); Serial.print(' ');
        display.display();
        display.setCursor(0,0);
        display.clearDisplay();
        if (i == 0) {
            display.setCursor(0,0);
            display.clearDisplay();
            display.println("Failed to connect.");
            display.display();
            delay(2000);
            return (0);
        }
    }
    display.clearDisplay();
    display.setCursor(0,0);
    display.println("We has connection.");  
    display.println("IP address:");
    display.println(WiFi.localIP()); 
    display.display();
    return (1);
}

option ledoption = {"Led Option", ledBlue};
option displayoption = {"Display Option", scrollMessage};
option wifioption = {"Wifi Option", wifiStatus};

menu currentmenu;
menu menuoption;
int menu_digit = 0;
menu menu_main = {"Main menu", 1, NULL};
menu menu_leds = {"Leds", 2, ledoption};
menu menu_display = {"Display", 3, displayoption};
menu menu_interwebs = {"Interwebs", 4, wifioption};


void setup() {
    // Rotary encoder
    pinMode(CLK,INPUT);
    pinMode(DT,INPUT);
    pinMode(SW, INPUT_PULLUP);

    // RGB led
    pinMode(LED_R, OUTPUT);
    pinMode(LED_G, OUTPUT);
    pinMode(LED_B, OUTPUT);
    analogWrite(LED_R, 0);
    analogWrite(LED_G, 0);
    analogWrite(LED_B, 0);

    Wire.begin(); 
    Serial.begin(9600);
    WiFi.begin(ssid, password);

    // Oled init
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

void rotaryMenu() {
    millis();
    // Set current menu to main
    currentmenu = menu_main;
    // Read the current state of CLK
    currentStateCLK = digitalRead(CLK);

    // Read the button state
    btnState = digitalRead(SW);
    // If last and current state of CLK are different, then pulse occurred
    // React to only 1 state change to avoid double count
    if (currentStateCLK != lastStateCLK  && currentStateCLK == 1){
    // If the DT state is different than the CLK state then
    // the encoder is rotating CCW so decrement
        if (digitalRead(DT) != currentStateCLK) {
            menu_digit--;
        } else {
        // Encoder is rotating CW so increment
            menu_digit++;
        }
        if (menu_digit > MENU_MAX)
            menu_digit = MENU_MIN;
        if (menu_digit < MENU_MIN)
            menu_digit = MENU_MAX;
        if (menu_digit == 1)
            menuoption = menu_leds;
        if (menu_digit == 2)
            menuoption = menu_display;
        if (menu_digit == 3)
            menuoption = menu_interwebs;
        display.clearDisplay();
        display.setCursor(0,0);
        display.print("Bs: ");
        display.print(btnState);
        display.print(" | ");
        display.print(menu_digit);
        display.print(": ");
        display.print(menuoption.name);
        display.display();
        delay(10);
    }

    // Remember last CLK state
    lastStateCLK = currentStateCLK;

    //If we detect LOW signal, button is pressed
    if (btnState == LOW) {
    //if 50ms have passed since last LOW pulse, it means that the
    //button has been pressed, released and pressed again
        if (millis() - lastButtonPress > 50) {
                display.clearDisplay();
                display.setCursor(0,0);
                display.print("Button pressed ");
                display.println(btnState);
                display.print("Menu: ");
                display.println(menuoption.name);
                display.display();
                menuoption.optn.action();
        }
        // Remember last button press event
        lastButtonPress = millis();
    }
    // Put in a slight delay to help debounce the reading
    delay(1);
}

void loop() {
    rotaryMenu();
}