#include "Wire.h"

#define I2C_ADDR_MIN 0
#define I2C_ADDR_MAX 128
#define I2C_MAX_DEVICE_COUNT 4

// Bad code af...
#define LED_DISPLAY_I2C_ADDRESS 52
#define MATRIX_I2C_ADDRESS 51

struct RegisteredSensor {
  public:
    VL53L1X* sensor;
    uint8_t tcaIndex;
    uint8_t i2cAddress;
};

class SensorController {
  public:
    SensorController();
    void init();
    bool dataReady();
    long getDistanceMm();

  private:
    void scanI2C();
    void i2CDeviceFound(uint8_t tcaIndex, uint8_t i2cAddress);
    void tcaselect(uint8_t iDevice);

    uint8_t sensorCount = 0;
    RegisteredSensor sensors[I2C_MAX_DEVICE_COUNT];
};
