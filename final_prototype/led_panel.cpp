#include "led_panel.h"

LEDPanel::LEDPanel(int ledPin, int pixelCount) {
    this->ledPin = ledPin;
    this->pixelCount = pixelCount;
    this->strip = Adafruit_NeoPixel(pixelCount, ledPin, NEO_GRB + NEO_KHZ800);
    this->offColor = this->strip.Color(0, 0, 0);
    this->onColor = this->strip.Color(255, 0, 0);
    this->fadeColor = this->strip.Color(255, 0, 0, 125);
}

LEDPanel::init() {
    strip.begin();
    strip.show();
}

LEDPanel::update() {
  if (isActive) {
    long currentTime = millis();

    long elapsedTime = currentTime - lastFrameTimeMs;
    if (elapsedTime >= timePerFrameMs) {
      fragmentPosition = fragmentPosition >= pixelCount
        ? 0
        : fragmentPosition + 1;
      
      render();

      lastFrameTimeMs = currentTime;
    }
  }
}

LEDPanel::render() {
  //int maxPixel = max(this->pixelCount, this->fragmentOffset + fragmentLength + 1);
  //this->strip.fill(this->offColor, 0, this->pixelCount);
  /*
  for (int i = 0; i < maxPixel; i++) {
    this->strip.setPixelColor(i, this->onColor);
  }
  */

  for (int i = 0; i < pixelCount; i++) {
    /*
    if (i == fragmentPosition - 1) {
      strip.setPixelColor(i, fadeColor);
    } else if (i == fragmentPosition) {
      strip.setPixelColor(i, onColor);
    } else if (i == fragmentPosition + 1) {
      strip.setPixelColor(i, fadeColor);
    } else {
      strip.setPixelColor(i, offColor);
    }
    */

    if (i < fragmentPosition) {
      strip.setPixelColor(i, onColor);
    } else {
      strip.setPixelColor(i, offColor);
    }
  }
  
  strip.show();
}

LEDPanel::reset() {
  fragmentPosition = 0;
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