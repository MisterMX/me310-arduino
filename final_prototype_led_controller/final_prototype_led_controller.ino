
#include <Wire.h>
#include <Servo.h>
#include "led_panel.h"

#define PIN_LED 12
#define LED_COUNT 14

#define PIN_SERVO_LEFT 10
#define PIN_SERVO_RIGHT 11

#define SERVO_LEFT_POS_OPEN 70
#define SERVO_LEFT_POS_CLOSED 0

#define SERVO_RIGHT_POS_OPEN 0
#define SERVO_RIGHT_POS_CLOSED 75

#define WING_STATE_UNDEF -1
#define WING_STATE_OPEN 1
#define WING_STATE_CLOSED 2

#define I2C_ADDRESS 52

LEDPanel panel(PIN_LED, LED_COUNT);

Servo servo_left;
Servo servo_right;
uint8_t wingState = WING_STATE_UNDEF;

void setup()
{
  Wire.begin(I2C_ADDRESS);
  Wire.setClock(400000);  // use 400 kHz I2C
  Wire.onReceive(onReceive);

  panel.init();
  
  servo_left.attach(PIN_SERVO_LEFT);
  servo_right.attach(PIN_SERVO_RIGHT);

  setWingState(WING_STATE_CLOSED);
}

void loop() {
  panel.update();
}

void onReceive(int howMany) {
  if (howMany >= 1) {
    char c = Wire.read();
    if (c == 1) {
      setWingState(WING_STATE_OPEN);
      panel.activate();
    } else {
      setWingState(WING_STATE_CLOSED);
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
