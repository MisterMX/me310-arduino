#include <Adafruit_NeoPixel.h>

#define COLOR uint32_t
#define LED_PANEL_INITIAL_FRAGMENT_POS -5
#define LED_PANEL_FRAGMENT_OVERSET 5

class LEDPanel {
    public:
        LEDPanel(int ledPin, int pixelCount);
        init();
        update();
        activate();
        deactivate();

    private:
        render();
        reset();

        COLOR offColor;
        COLOR onColor;
        COLOR fadeColor;
        bool isActive = false;
        int ledPin;
        int pixelCount;
        int fragmentPosition = LED_PANEL_INITIAL_FRAGMENT_POS;
        int maxFragmentPosition;
        bool backward = false;
        int fragmentLength = 3;
        long timePerFrameMs = 30;
        long lastFrameTimeMs = 0;
        Adafruit_NeoPixel strip;
};
