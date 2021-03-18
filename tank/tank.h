#include <Stepper.h>
#include <Servo.h>
#include <SPI.h>
#include <WiFiNINA.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>

// Define Pins
#define PIN_IN1 10
#define PIN_IN2 9
#define PIN_IN3 8
#define PIN_IN4 7

#define PIN_ST1 6
#define PIN_ST2 5
#define PIN_ST3 4
#define PIN_ST4 3

#define PIN_SRV 2

#define PIN_ENA A0
#define PIN_ENB A1

#define MAX_THROTTLE 255
#define MIN_THROTTLE 120

#define TFT_SCK 13
#define TFT_MOSI 11
#define TFT_CS 10
#define TFT_RST 9
#define TFT_DC 8