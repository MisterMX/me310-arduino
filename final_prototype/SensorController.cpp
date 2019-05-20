#include "SensorController.h"

SensorController::SensorController() {
}

void SensorController::init() {
  scanI2C();
}

void SensorController::scanI2C() {
  byte rc;
  byte data = 0; // not used, just an address to feed to twi_writeTo()
  for(byte addr = I2C_ADDR_MIN; addr <= I2C_ADDR_MAX && sensorCount < I2C_MAX_DEVICE_COUNT; addr++) {
    rc = twi_writeTo(addr, &data, 0, 1, 0);
    if (rc == 0) {
      i2CDeviceFound(addr);
    }
  }
}

void SensorController::i2CDeviceFound(byte address) {
  Serial.print("Found device on address ");
  Serial.println(address);

  VL53L1X* sensor = new VL53L1X();
  sensor->setTimeout(500);
  if (sensor->init()) {
    // Use long distance mode and allow up to 50000 us (50 ms) for a measurement.
    // You can change these settings to adjust the performance of the sensor, but
    // the minimum timing budget is 20 ms for short distance mode and 33 ms for
    // medium and long distance modes. See the VL53L1X datasheet for more
    // information on range and timing limits.
    sensor->setDistanceMode(VL53L1X::Long);
    sensor->setMeasurementTimingBudget(120000);

    // Start continuous readings at a rate of one measurement every 50 ms (the
    // inter-measurement period). This period should be at least as long as the
    // timing budget.
    sensor->startContinuous(120);

    sensors[sensorCount] = sensor;
    sensorCount++;
  } else {
    Serial.println("Failed to initialize.");
  }
}

bool SensorController::dataReady() {
  for (uint8_t i = 0; i < sensorCount; i++) {
    if (sensors[i]->dataReady()) {
      return true;
    }
  }

  return false;
}

long SensorController::getDistanceMm() {
  long nearestDistance = 1000000;
  for (uint8_t i = 0; i < sensorCount; i++) {
    VL53L1X* sensor = sensors[i] ;
    sensor->read(false); // read without blocking
    if (sensor->ranging_data.range_status) {
      nearestDistance = min(nearestDistance, sensor->ranging_data.range_mm);
    }
  }

  return nearestDistance;
}
