#ifndef CORNER_SCANNER_H
#define CORNER_SCANNER_H

#include <Adafruit_NeoPixel.h>

#define UINT32 unsigned long
#define UINT16 unsigned int
#define PIN int

const UINT32 UINT_32_MAX = 0UL - 1UL;
const UINT16 UINT_16_MAX = 0 - 1;

class CornerScanner {
  public:
    CornerScanner(PIN trigger, PIN echo, PIN led, int ledPixelCount);
    void begin();
    void update();

  private:
    UINT32 getEchoInMicroseconds();
    UINT32 getDistanceInMilimeters();
    void turnStripOn();
    void turnStripOff();
    PIN _echo;
    PIN _trigger;
    UINT16 _step;
    Adafruit_NeoPixel* _ledStrip;
    int _ledPixelCount;
    bool _isTurnedOn;
};
#endif
