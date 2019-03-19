#include <Adafruit_NeoPixel.h>

int PIXEL_COUNT = 24;
int PIXEL_PIN = 6;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

bool filling = true;
int filledPixels = 0;

int curIndex = 0;

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void updateFilling() {
  if (filling) {
    if (curIndex == PIXEL_COUNT - filledPixels - 1) {
      filledPixels++;
      curIndex = 0;

      if (filledPixels == PIXEL_COUNT - 1) {
        filling = false;
      }
    } else {
      curIndex++;
    }
  } else {
    
  }
}

void loop() {
  // Unset previously moving pixel
  strip.setPixelColor(curIndex, filling ? strip.Color(0,0,0) : strip.Color(100,50,0));

  updateFilling();

  // Set new pixels
  strip.setPixelColor(curIndex, filling ? strip.Color(100,50,0) : strip.Color(0,0,0));

  for (int i = 1; i <= filledPixels; i++) {
    strip.setPixelColor(PIXEL_COUNT - i, strip.Color(200,0,200));
  }
  
  strip.show();
  delay(100);
}
