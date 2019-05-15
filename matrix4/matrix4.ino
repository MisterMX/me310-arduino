#include "LedControl.h"

#define MAX_DEVICES 6

#define PIN_CLK   12  // or SCK
#define PIN_DATA  11  // or MOSI
#define PIN_CS    10  // or SS

/* Create a new LedControl variable.
 * We use pins 12,11 and 10 on the Arduino for the SPI interface
 * Pin 12 is connected to the DATA IN-pin of the first MAX7221
 * Pin 11 is connected to the CLK-pin of the first MAX7221
 * Pin 10 is connected to the LOAD(/CS)-pin of the first MAX7221
 * There will only be a single MAX7221 attached to the arduino 
 */  
LedControl matrix = LedControl(PIN_DATA, PIN_CLK, PIN_CS, MAX_DEVICES);

void setup() {
/*
   The MAX72XX is in power-saving mode on startup,
   we have to do a wakeup call
   */
  matrix.shutdown(0,false);
  /* Set the brightness to a medium values */
  matrix.setIntensity(0,8);
  /* and clear the display */
matrix.clearDisplay(0);
  
  // put your setup code here, to run once:
  matrix.setColumn(0, 2, 0xFF);
}

void loop() {
  // put your main code here, to run repeatedly:

}
