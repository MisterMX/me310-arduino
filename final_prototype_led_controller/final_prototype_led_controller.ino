
#include <LedControl.h>   //LedControl library: https://www.electronoobs.com/ledcontrol.php

#define MAX_DEVICES 6
#define PIXEL_PER_DEVICE 8
#define ROW_LENGTH ((MAX_DEVICES * PIXEL_PER_DEVICE) / 2)
#define COLUMN_COUNT (MAX_DEVICES * PIXEL_PER_DEVICE)

#define PIN_CLK   12  // or SCK
#define PIN_DATA  11  // or MOSI
#define PIN_CS    10  // or SS
#define PIN_SIGNAL 4

#define STATE_NONE 0
#define STATE_SIGN 1
#define STATE_BOX 2

LedControl lc= LedControl(PIN_DATA, PIN_CLK, PIN_CS, MAX_DEVICES);

//uint8_t pixels_box[8] = { 1, 2, 4, 8, 16, 32, 64, 128 };
uint8_t pixels_sign[48]  = { 0, 0, 0, 0, 0x80, 0xC0, 0x60, 0x30, 0x18, 0x0C, 0x06, 0xFB, 0xFB, 0x06, 0x0C, 0x18, 0x30,0x60, 0xC0, 0x80, 0, 0, 0, 0,
                           0xF8, 0xFC, 0xC6, 0xC3, 0xC1, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xDB, 0xDB, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC1, 0xC3, 0xC6, 0xFC, 0xF8};

uint8_t currentState = STATE_NONE;

void setup()
{
  pinMode(PIN_SIGNAL, INPUT);
  
  for (int x=0; x<MAX_DEVICES; x++)
  {
    lc.shutdown(x,false);       //The MAX72XX is in power-saving mode on startup
    lc.setIntensity(x,8);       // Set the brightness to default value
    lc.clearDisplay(x);         // and clear the display
  }
}

void loop() {
  if (digitalRead(PIN_SIGNAL) == HIGH) {
    if (currentState != STATE_SIGN) {
      drawSign();
      currentState = STATE_SIGN;
    }
  } else {
    if (currentState != STATE_BOX) {
      drawBox();
      currentState = STATE_BOX;
    }
  }
}

void drawBox() {
  for (uint16_t  col=0; col < COLUMN_COUNT; col++) {
    if (col % ROW_LENGTH == 0 ||
       col % ROW_LENGTH == ROW_LENGTH - 1) {
      setColumn(col, 0xFF);
    } else if (col < COLUMN_COUNT / 2 ) {
      setColumn(col, 0x01);
    } else {
      setColumn(col, 0x80);
    }
  }
}

void drawSign() {
  for (uint16_t  col=0; col < COLUMN_COUNT; col++) {
    setColumn(col, pixels_sign[col]);
  }
}

void setColumn(uint16_t c, uint8_t val) {
  uint16_t deviceCol = PIXEL_PER_DEVICE - 1 - c % 8;
  uint16_t deviceNum = c / PIXEL_PER_DEVICE;
  
  lc.setColumn(deviceNum, deviceCol, val);
}
