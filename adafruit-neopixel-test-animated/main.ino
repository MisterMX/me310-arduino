#include <Adafruit_NeoPixel.h>

#define COLOR uint32_t

int PIXEL_COUNT = 100;
int PIXEL_PIN = 6;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

bool isActive = false;

COLOR offColor = strip.Color(0, 0, 0);
COLOR onColor = strip.Color(255, 140, 0);

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  for (int i = 0; i < PIXEL_COUNT; i++) {
    if ((i % 2 != 0) != isActive) {
      strip.setPixelColor(i, offColor);
    } else {
      strip.setPixelColor(i, onColor);
    } 
  }
  
  strip.show();

  isActive = !isActive;
  delay(500);
}
