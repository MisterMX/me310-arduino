#include <VL53L1X.h>
extern "C" { 
  #include "utility/twi.h"  // from Wire library, so we can do bus scanning
}
#include "SensorController.h"

#define TCAADDR 0x70

SensorController::SensorController() {
}

void SensorController::init() {
  scanI2C();
}

void SensorController::scanI2C() {
  for (uint8_t t=0; t<8; t++) {
    tcaselect(t);
    Serial.print("TCA Port #"); Serial.println(t);
 
    for (uint8_t addr = 0; addr <= 127; addr++) {
      if (addr == TCAADDR || addr == LED_DISPLAY_I2C_ADDRESS || addr == MATRIX_I2C_ADDRESS) {
        continue;
      }

      uint8_t data;
      if (! twi_writeTo(addr, &data, 0, 1, 1)) {
         Serial.print("Found I2C 0x");  Serial.println(addr, HEX);
         i2CDeviceFound(t, addr);
      }
    }
  }
  
  Serial.println("\ndone");
  Serial.print("Registered ");
  Serial.print(sensorCount);
  Serial.println(" sensor(s)");
}

void SensorController::i2CDeviceFound(uint8_t tcaIndex, uint8_t i2cAddress) {
  if (sensorCount >= I2C_MAX_DEVICE_COUNT) {
    return;
  }

  VL53L1X* sensor = new VL53L1X();
  sensor->setAddress(i2cAddress);
  sensor->setTimeout(2000);
  if (sensor->init()) {
    Serial.println("Success");
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

    RegisteredSensor registered;
    registered.sensor = sensor;
    registered.tcaIndex = tcaIndex;
    registered.i2cAddress = i2cAddress;

    sensors[sensorCount] = registered;
    
    sensorCount++;
  }
}

bool SensorController::dataReady() {
  for (uint8_t i = 0; i < sensorCount; i++) {
    RegisteredSensor registered = sensors[i];
    VL53L1X* sensor = registered.sensor;
    
    tcaselect(registered.tcaIndex);
    if (sensor->dataReady()) {
      return true;
    }
  }

  return false;
}

long SensorController::getDistanceMm() {
  long nearestDistance = 1000000;
  for (uint8_t i = 0; i < sensorCount; i++) {
    RegisteredSensor registered = sensors[i];
    VL53L1X* sensor = registered.sensor;

    tcaselect(registered.tcaIndex);
    
    if (sensor->dataReady()) {
      uint16_t distance = sensor->readRangeContinuousMillimeters(false); // read without blocking
      nearestDistance = min(nearestDistance, distance);
    }
  }

  return nearestDistance;
}

void SensorController::tcaselect(uint8_t i) {
  if (i > 7) return;

  Wire.beginTransmission(TCAADDR);
  Wire.write(1 << i);
  Wire.endTransmission();
}
