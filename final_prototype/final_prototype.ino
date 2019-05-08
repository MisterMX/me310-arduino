#include <Wire.h>
#include <VL53L1X.h>
#include <Servo.h>
#include "MedianFilterLib.h"
#include "led_panel.h"

#define PIN_SERVO 6
#define SENSOR_STATUS_VALID 0
#define RANGE_TRESHOLD_MM 150

#define PIN_LED 7
#define LED_COUNT 23

#define SERVO_POS_OPEN 80
#define SERVO_POS_CLOSED 0

Servo servo;
VL53L1X sensor;
int pos = 0;
LEDPanel panel(PIN_LED, LED_COUNT);

void setup() {
  servo.attach(PIN_SERVO);
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
  sensor.setMeasurementTimingBudget(50000);

  // Start continuous readings at a rate of one measurement every 50 ms (the
  // inter-measurement period). This period should be at least as long as the
  // timing budget.
  sensor.startContinuous(50);

  panel.init();
}

void loop() {
  panel.update();
  
  if (sensor.dataReady()) {
    sensor.read(false); //read without blocking
    Serial.println(sensor.ranging_data.range_mm);
    if (sensor.ranging_data.range_mm <= RANGE_TRESHOLD_MM) {
      setServoPos(SERVO_POS_OPEN);
      panel.activate();
    } else {
      setServoPos(SERVO_POS_CLOSED);
      panel.deactivate();
    }
    sensor.read(false); //read without blocking
  }
}

void setServoPos(int newPos) {
  if (pos != newPos) {
    pos = newPos;
    servo.write(pos);
  }
}
