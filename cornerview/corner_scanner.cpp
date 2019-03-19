#include "corner_scanner.h"

#define FILTER_WINDOW_SIZE 5
#define LED_TRIGGER_DISTANCE 1000
#define MAX_WAIT_TIME 50000

CornerScanner::CornerScanner(PIN trigger, PIN echo, PIN led, int ledPixelCount) {
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);

  _trigger = trigger;
  _echo = echo;
  _ledStrip = new Adafruit_NeoPixel(ledPixelCount, led, NEO_GRB + NEO_KHZ800);
  _ledPixelCount = ledPixelCount;
  _isTurnedOn = false;
}

void CornerScanner::begin() {
  _ledStrip->begin();
  _ledStrip->show();
}

void CornerScanner::update() {
  UINT32 value = getDistanceInMilimeters();
  Serial.println(value);
  if (value < LED_TRIGGER_DISTANCE) {
    turnStripOn();
  } else {
    turnStripOff();
  }
}

UINT32 CornerScanner::getEchoInMicroseconds()
{
  digitalWrite(_trigger, LOW);
  delayMicroseconds(5);
  digitalWrite(_trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(_trigger, LOW);
  // Why don't I just use? "return pulseIn(_echo, HIGH);"
  // Arduino Primo doesn't have access to pulseIn.

  while (digitalRead(_echo) == LOW);

  UINT32 pulseStart = micros();
  UINT32 waitedTime = 0;

  do {
    waitedTime = micros() - pulseStart;
  } while (waitedTime < MAX_WAIT_TIME && digitalRead(_echo) == HIGH);

  return waitedTime < MAX_WAIT_TIME ? waitedTime : UINT_32_MAX;
}

UINT32 CornerScanner::getDistanceInMilimeters() {
  UINT32 echoMs = getEchoInMicroseconds();
  UINT32 distance = (echoMs / 2) * 0.332;

  return distance;
}

void CornerScanner::turnStripOn() {
  if (!_isTurnedOn) {
    _ledStrip->fill(_ledStrip->Color(255, 255, 0), 0, _ledPixelCount);
    _ledStrip->show();
    _isTurnedOn = true;
  }
}

void CornerScanner::turnStripOff() {
  if (_isTurnedOn) {
    _ledStrip->fill(_ledStrip->Color(0, 0, 0), 0, _ledPixelCount);
    _ledStrip->show();
    _isTurnedOn = false;
  }
}
