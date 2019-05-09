// Program to exercise the MD_MAX72XX library
//
// Uses the graphics functions to animate a pair of eyes on 2 matrix modules.
// Eyes are coordinated to work together.
// Eyes are created to fill all available modules.
//
//
#include <MD_MAX72xx.h>

// Define the number of devices we have in the chain and the hardware interface
#define HARDWARE_TYPE MD_MAX72XX::ICSTATION_HW
#define TRANSFORM_TYPE MD_MAX72XX::TFUD 
#define MAX_DEVICES 6
#define PIXEL_PER_DEVICE 8
#define ROW_LENGTH ((MAX_DEVICES * PIXEL_PER_DEVICE) / 2)

#define PIN_CLK   12  // or SCK
#define PIN_DATA  11  // or MOSI
#define PIN_CS    10  // or SS

MD_MAX72XX matrix = MD_MAX72XX(HARDWARE_TYPE, PIN_DATA, PIN_CLK, PIN_CS, MAX_DEVICES);

uint8_t pixels[] = { 1, 2, 4, 8, 16, 32, 64, 128 };
/*
uint8_t pixels_sign[]  = { 0, 0, 0, 0, 0, 0, 0x80, 0x40, 0x20, 0x10, 0x08, 0xE4, 0xE4, 0x08, 0x10, 0x20,0x40, 0x80, 0, 0, 0, 0, 0, 0,
                           0x20, 0x30, 0x28, 0x24, 0x22, 0x21, 0x20, 0x20, 0x20, 0x20, 0x20, 0x2F, 0x2F, 0x20, 0x20, 0x20, 0x20, 0x20, 0x21, 0x22, 0x24, 0x28, 0x30, 0x20};

/*
uint8_t pixels_sign[]  = { 0, 0, 0, 0, 0, 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0xF2, 0xF2, 0x04, 0x08, 0x10, 0x20,0x40, 0x80, 0, 0, 0, 0, 0,
                           0x30, 0x28, 0x24, 0x22, 0x21, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x2F, 0x2F, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x21, 0x22, 0x24, 0x28, 0x30};
                           */
/*
uint8_t pixels_sign[]  = { 0, 0, 0, 0, 0, 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0xFA, 0xFA, 0x04, 0x08, 0x10, 0x20,0x40, 0x80, 0, 0, 0, 0, 0,
                           0x70, 0x48, 0x44, 0x42, 0x41, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x5B, 0x5B, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x41, 0x42, 0x44, 0x48, 0x70};
                           */

uint8_t pixels_sign[]  = { 0, 0, 0, 0, 0x80, 0xC0, 0x60, 0x30, 0x18, 0x0C, 0x06, 0xFB, 0xFB, 0x06, 0x0C, 0x18, 0x30,0x60, 0xC0, 0x80, 0, 0, 0, 0,
                           0xF8, 0xFC, 0xC6, 0xC3, 0xC1, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xDB, 0xDB, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC1, 0xC3, 0xC6, 0xFC, 0xF8};

void setup()
{
  Serial.begin(115200);
  matrix.begin();
  matrix.clear();
  //matrix.clear();

  Serial.println(matrix.getColumnCount());
  //drawSign();
  //drawBox();
  fillAll();
}

void drawSign() {
  for (uint16_t  col=0; col < matrix.getColumnCount(); col++) {
    setColumn(col, pixels_sign[col]);
  }
  matrix.control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
}

void fillAll() {
  for (uint16_t  col=0; col < matrix.getColumnCount(); col++) {
    setColumn(col, pixels[col % 8]);
  }
  matrix.control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
}

void drawBox() {
  for (uint16_t  col=0; col < matrix.getColumnCount(); col++) {
    if (col % ROW_LENGTH == 0 ||
       col % ROW_LENGTH == ROW_LENGTH - 1) {
      setColumn(col, 0xFF);
    } else if (col < matrix.getColumnCount() / 2 ) {
      setColumn(col, 0x01);
    } else {
      setColumn(col, 0x80);
    }
  }
  matrix.control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
}

void setColumn(uint16_t c, uint8_t val) {
  uint16_t deviceCol = 7 - c % 8;
  uint16_t deviceNum = c / 8;
  
  matrix.setColumn(deviceNum * 8 + deviceCol, val);
}

void loop()
{
  
}
