#include <LedControl.h>

#define MAX_DEVICES 6
#define PIXEL_PER_DEVICE 8
#define ROW_LENGTH ((MAX_DEVICES * PIXEL_PER_DEVICE) / 2)
#define COLUMN_COUNT (MAX_DEVICES * PIXEL_PER_DEVICE)

#define PIN_CLK   12  // or SCK
#define PIN_DATA  11  // or MOSI
#define PIN_CS    10  // or SS

#define CONTENT_CLEAR 0
#define CONTENT_BOX 1
#define CONTENT_SIGN 2
#define CONTENT_FILL 4

class LEDMatrix {
  public:
    LEDMatrix();
    void init();
    void update();
    void setContentStatus(uint8_t newStatus);

  private:
    uint8_t status = CONTENT_BOX;
    LedControl *matrix;

    long timePerFrameMs = 100;
    long lastFrameTimeMs = 0;
    
    uint8_t pixels_box[8] = { 1, 2, 4, 8, 16, 32, 64, 128 };
    uint8_t pixels_sign[48]  = { 0, 0, 0, 0, 0x80, 0xC0, 0x60, 0x30, 0x18, 0x0C, 0x06, 0xFB, 0xFB, 0x06, 0x0C, 0x18, 0x30,0x60, 0xC0, 0x80, 0, 0, 0, 0,
                           0xF8, 0xFC, 0xC6, 0xC3, 0xC1, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xDB, 0xDB, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC1, 0xC3, 0xC6, 0xFC, 0xF8};

    void drawSign();
    void drawBox();
    void fillAll();
    void drawClear();

    void setColumn(uint16_t c, uint8_t val);
};
