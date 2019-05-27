
#include <Wire.h>
#include <Servo.h>
#include <MD_MAX72xx.h>
#include "led_panel.h"

#define PIN_LED 12
#define LED_COUNT 14

#define PIN_SERVO_LEFT 10
#define PIN_SERVO_RIGHT 11

#define SERVO_LEFT_POS_OPEN 70
#define SERVO_LEFT_POS_CLOSED 0

#define SERVO_RIGHT_POS_OPEN 0
#define SERVO_RIGHT_POS_CLOSED 70

#define WING_STATE_UNDEF -1
#define WING_STATE_OPEN 1
#define WING_STATE_CLOSED 2

#define I2C_ADDRESS 52

#define MAX_DEVICES 6
#define PIXEL_PER_DEVICE 8
#define ROW_LENGTH ((MAX_DEVICES * PIXEL_PER_DEVICE) / 2)
#define COLUMN_COUNT (MAX_DEVICES * PIXEL_PER_DEVICE)
#define HARDWARE_TYPE MD_MAX72XX::PAROLA_HW

#define PIN_CLK  7
#define PIN_DATA 6
#define PIN_CS   5  // or SS

#define STATE_NONE 0
#define STATE_SIGN 1
#define STATE_BOX 2

MD_MAX72XX lc = MD_MAX72XX(HARDWARE_TYPE, PIN_DATA, PIN_CLK, PIN_CS, MAX_DEVICES);
uint8_t pixels_sign[48]  = { 0, 0, 0, 0, 0x80, 0xC0, 0x60, 0x30, 0x18, 0x0C, 0x06, 0xFB, 0xFB, 0x06, 0x0C, 0x18, 0x30,0x60, 0xC0, 0x80, 0, 0, 0, 0,
                           0xF8, 0xFC, 0xC6, 0xC3, 0xC1, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xDB, 0xDB, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC1, 0xC3, 0xC6, 0xFC, 0xF8};

LEDPanel panel(PIN_LED, LED_COUNT);

Servo servo_left;
Servo servo_right;
uint8_t wingState = WING_STATE_UNDEF;
uint8_t currentState = STATE_NONE;

void setup()
{
  //Wire.begin(I2C_ADDRESS);
  //Wire.setClock(400000);  // use 400 kHz I2C
  //Wire.onReceive(onReceive);

  panel.init();
  lc.begin();
  
  servo_left.attach(PIN_SERVO_LEFT);
  servo_right.attach(PIN_SERVO_RIGHT);
  
  setWingState(WING_STATE_CLOSED);

  panel.activate();
}

void loop() {
  panel.update();
}

void onReceive(int howMany) {
  if (howMany >= 1) {
    char c = Wire.read();
    if (c == 1) {
      setWingState(WING_STATE_OPEN);
      setState(STATE_SIGN);
      panel.activate();
    } else {
      setWingState(WING_STATE_CLOSED);
      setState(STATE_BOX);
      panel.deactivate();
    }
  }
}

void setWingState(uint8_t newState) {
  if (wingState != newState) {
    wingState = newState;
    if (wingState == WING_STATE_OPEN) {
      servo_left.write(SERVO_LEFT_POS_OPEN);
      servo_right.write(SERVO_RIGHT_POS_OPEN);
      //panel.activate();
    } else {
      servo_left.write(SERVO_LEFT_POS_CLOSED);
      servo_right.write(SERVO_RIGHT_POS_CLOSED);
      //panel.deactivate();
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
