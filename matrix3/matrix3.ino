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

void setup()
{
  Serial.begin(115200);
  matrix.begin();
  matrix.clear();
  //matrix.clear();

  Serial.println(matrix.getColumnCount());
  for (uint16_t  col=0; col < matrix.getColumnCount(); col++) {
   if (col % ROW_LENGTH == 0 ||
       col % ROW_LENGTH == ROW_LENGTH - 1) {
     setColumn(col, 0xFF);
   } else if (col < matrix.getColumnCount() / 2 ) {
    setColumn(col, 0x01);
   } else {
    setColumn(col, 0x80);
   }
   
    
    //setColumn(col, pixels[col % 8]);
    //matrix.setColumn(col, 0x01);
  }
  
  /*
  for (uint8_t col=0; col < matrix.getColumnCount(); col++)
  {
    matrix.setColumn(col, 0xff);
    //delay(DELAYTIME/MAX_DEVICES);
    //mx.setColumn(col, 0x00);
}
*/
  //matrix.transform(TRANSFORM_TYPE);
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
