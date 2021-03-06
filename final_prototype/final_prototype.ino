#include <Wire.h>
#include <VL53L1X.h>
#include <Servo.h>
#include "led_panel.h"

#define PIN_SERVO_LEFT 5
#define PIN_SERVO_RIGHT 6
#define SENSOR_STATUS_VALID 0
#define RANGE_TRESHOLD_MM 2000

#define PIN_LED 7
#define LED_COUNT 14

#define LED_DISPLAY_I2C_ADDRESS 128

#define SERVO_LEFT_POS_OPEN 70
#define SERVO_LEFT_POS_CLOSED 0

#define SERVO_RIGHT_POS_OPEN 0
#define SERVO_RIGHT_POS_CLOSED 70

#define WING_STATE_UNDEF -1
#define WING_STATE_OPEN 1
#define WING_STATE_CLOSED 2

Servo servo_left;
Servo servo_right;
VL53L1X sensor;
uint8_t wingState = WING_STATE_UNDEF;
LEDPanel panel(PIN_LED, LED_COUNT);

void setup() {
  Serial.begin(115200);
  Wire.begin();
  Wire.setClock(400000);  // use 400 kHz I2C

  sensor.setTimeout(500);
  if (!sensor.init()) {
    Serial.println("Failed to detect and initialize sensor!");
    while (1);
  }
  
  // Use long distance mode and allow up to 50000 us (50 ms) for a measurement.
  // You can change these settings to adjust the performance of the sensor, but
  // the minimum timing budget is 20 ms for short distance mode and 33 ms for
  // medium and long distance modes. See the VL53L1X datasheet for more
  // information on range and timing limits.
  sensor.setDistanceMode(VL53L1X::Long);
  sensor.setMeasurementTimingBudget(120000);

  // Start continuous readings at a rate of one measurement every 50 ms (the
  // inter-measurement period). This period should be at least as long as the
  // timing budget.
  sensor.startContinuous(120);

  panel.init();

  servo_left.attach(PIN_SERVO_LEFT);
  servo_right.attach(PIN_SERVO_RIGHT);
  setWingState(WING_STATE_CLOSED);
}

void loop() {
  panel.update();

  if (sensor.dataReady()) {
    sensor.read(false); //read without blocking
    Serial.println(sensor.ranging_data.range_mm);
    if (sensor.ranging_data.range_status == 0 && sensor.ranging_data.range_mm <= RANGE_TRESHOLD_MM) {
      sendToSlave(1);
      setWingState(WING_STATE_OPEN);
      panel.activate();
    } else {
      sendToSlave(0);
      setWingState(WING_STATE_CLOSED);
      panel.deactivate();
    }
    sensor.read(false); //read without blocking
  }
}

void sendToSlave(byte b) {
  Wire.beginTransmission(LED_DISPLAY_I2C_ADDRESS);
  Wire.write(b);
  Wire.endTransmission();
}

void setWingState(uint8_t newState) {
  if (wingState != newState) {
    wingState = newState;
    if (wingState == WING_STATE_OPEN) {
      servo_left.write(SERVO_LEFT_POS_OPEN);
      servo_right.write(SERVO_RIGHT_POS_OPEN);
    } else {
      servo_left.write(SERVO_LEFT_POS_CLOSED);
      servo_right.write(SERVO_RIGHT_POS_CLOSED);
    }
  }
}
