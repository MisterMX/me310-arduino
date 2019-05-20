#include "Wire.h"
extern "C" { 
  #include "utility/twi.h"  // from Wire library, so we can do bus scanning
}
#include <VL53L1X.h>

#define I2C_ADDR_MIN 8
#define I2C_ADDR_MAX 119
#define I2C_MAX_DEVICE_COUNT 4

class SensorController {
  public:
    SensorController();
    void init();
    bool dataReady();
    long getDistanceMm();

  private:
    void scanI2C();
    void i2CDeviceFound(byte address);

    uint8_t sensorCount = 0;
    VL53L1X* sensors[I2C_MAX_DEVICE_COUNT];
};
