//#include <hcsr04.h>
#include <Adafruit_NeoPixel.h>
#include "MedianFilterLib.h"
#include "corner_scanner.h"

#define LED_PIXEL_COUNT 26

#define SCAN1_TRIG 13
#define SCAN1_ECHO 12
#define SCAN1_LED 11

#define SCAN2_TRIG 10
#define SCAN2_ECHO 9
#define SCAN2_LED 8

CornerScanner cornerScanner1(SCAN1_TRIG, SCAN1_ECHO, SCAN1_LED, LED_PIXEL_COUNT);
//CornerScanner cornerScanner2(SCAN2_TRIG, SCAN2_ECHO, SCAN2_LED, LED_PIXEL_COUNT);

void setup() {
  Serial.begin(9600);

  cornerScanner1.begin();
  //cornerScanner2.begin();
}

void loop() {
  cornerScanner1.update();
  //cornerScanner2.update();
  delay(300);
}
