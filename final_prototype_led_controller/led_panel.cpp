#include "led_panel.h"

LEDPanel::LEDPanel(int ledPin, int pixelCount) {
    this->ledPin = ledPin;
    this->pixelCount = pixelCount;
    this->strip = Adafruit_NeoPixel(pixelCount, ledPin, NEO_GRB + NEO_KHZ800);
    this->offColor = this->strip.Color(0, 0, 0);
    this->onColor = this->strip.Color(255, 0, 0);
    this->fadeColor = this->strip.Color(255, 0, 0, 125);
    maxFragmentPosition = pixelCount + LED_PANEL_FRAGMENT_OVERSET;
}

LEDPanel::init() {
    strip.begin();
    //strip.show();
    reset();
}

LEDPanel::update() {
  if (isActive) {
    long currentTime = millis();

    long elapsedTime = currentTime - lastFrameTimeMs;
    if (elapsedTime >= timePerFrameMs) {
      fragmentPosition = fragmentPosition > maxFragmentPosition
        ? LED_PANEL_INITIAL_FRAGMENT_POS
        : fragmentPosition + 1;
      
      render();

      lastFrameTimeMs = currentTime;
    }
  }
}

LEDPanel::render() {
  for (int i = 0; i < pixelCount; i++) {
    if (i < fragmentPosition) {
      strip.setPixelColor(i, onColor);
    } else {
      strip.setPixelColor(i, offColor);
    }
  }
  
  strip.show();
}

LEDPanel::reset() {
  fragmentPosition = LED_PANEL_INITIAL_FRAGMENT_POS;
  strip.fill(offColor, 0, pixelCount);
  strip.show();
}

LEDPanel::activate() {
  if (!isActive) {
    reset();
    isActive = true;
  }
}

LEDPanel::deactivate() {
  if (isActive) {
    reset();
    isActive = false;
  }
}
