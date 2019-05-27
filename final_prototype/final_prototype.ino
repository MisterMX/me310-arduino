#include <Wire.h>
#include <VL53L1X.h>
#include <Servo.h>
#include "SensorController.h"

#define PIN_SERVO_LEFT 5
#define PIN_SERVO_RIGHT 6
#define SENSOR_STATUS_VALID 0
#define RANGE_TRESHOLD_MM 2000

#define PIN_LED 7
#define LED_COUNT 14

#define SERVO_LEFT_POS_OPEN 70
#define SERVO_LEFT_POS_CLOSED 0

#define SERVO_RIGHT_POS_OPEN 0
#define SERVO_RIGHT_POS_CLOSED 70

#define WING_STATE_UNDEF -1
#define WING_STATE_OPEN 1
#define WING_STATE_CLOSED 2

SensorController sensor;
uint8_t wingState = WING_STATE_UNDEF;

void setup() {
  Serial.begin(115200);
  delay(3000);
  Serial.println("Setup");
  
  Wire.begin();
  Wire.setClock(400000);  // use 400 kHz I2C
  
  sensor.init();
}

void loop() {
  if (sensor.dataReady()) {
    long currentDistance = sensor.getDistanceMm();
    Serial.println(currentDistance);
    if (currentDistance <= RANGE_TRESHOLD_MM) {
      sendToSlave(1);
    } else {
      sendToSlave(0);
    }
  }
}

void sendToSlave(byte b) {
  Wire.beginTransmission(LED_DISPLAY_I2C_ADDRESS);
  Wire.write(b);
  Wire.endTransmission();
  Wire.beginTransmission(MATRIX_I2C_ADDRESS);
  Wire.write(b);
  Wire.endTransmission();
}
