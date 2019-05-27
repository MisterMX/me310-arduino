#include <MD_MAX72xx.h>
#include <SPI.h>
#include <Wire.h>

#define MAX_DEVICES 6
#define PIXEL_PER_DEVICE 8
#define ROW_LENGTH ((MAX_DEVICES * PIXEL_PER_DEVICE) / 2)
#define COLUMN_COUNT (MAX_DEVICES * PIXEL_PER_DEVICE)

#define PIN_CLK  12
#define PIN_DATA 11
#define PIN_CS   10  // or SS

#define STATE_NONE 0
#define STATE_SIGN 1
#define STATE_BOX 2

#define I2C_ADDRESS 51

#define HARDWARE_TYPE MD_MAX72XX::PAROLA_HW

MD_MAX72XX lc = MD_MAX72XX(HARDWARE_TYPE, PIN_DATA, PIN_CLK, PIN_CS, MAX_DEVICES);

uint8_t pixels_sign[48]  = { 0, 0, 0, 0, 0x80, 0xC0, 0x60, 0x30, 0x18, 0x0C, 0x06, 0xFB, 0xFB, 0x06, 0x0C, 0x18, 0x30,0x60, 0xC0, 0x80, 0, 0, 0, 0,
                           0xF8, 0xFC, 0xC6, 0xC3, 0xC1, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xDB, 0xDB, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC1, 0xC3, 0xC6, 0xFC, 0xF8};

uint8_t currentState = STATE_NONE;

void setup()
{
  Wire.begin(I2C_ADDRESS);
  Wire.setClock(400000);  // use 400 kHz I2C
  Wire.onReceive(onReceive);

  lc.begin();
  setState(STATE_BOX);
}

void loop() { }

void onReceive(int howMany) {
  if (howMany >= 1) {
    char c = Wire.read();
    if (c == 1) {
      setState(STATE_SIGN);
    } else {
      setState(STATE_BOX);
    }
  }
}

void setState(uint8_t newState) {
  if (newState != currentState) {
    switch(newState) {
      case STATE_SIGN:
        drawSign();
        break;

      case STATE_BOX:
        drawBox();
        break;
    }

    currentState = newState;
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
  lc.control(MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);
  for (uint16_t  col=0; col < COLUMN_COUNT; col++) {
    setColumn(col, pixels_sign[col]);
  }
  lc.control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
}

void setColumn(uint16_t c, uint8_t val) {
  lc.control(MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);
  uint16_t deviceCol = PIXEL_PER_DEVICE - 1 - c % 8;
  uint16_t deviceNum = c / PIXEL_PER_DEVICE;
  
  lc.setColumn(deviceNum * PIXEL_PER_DEVICE + deviceCol, val);
  lc.control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
}
