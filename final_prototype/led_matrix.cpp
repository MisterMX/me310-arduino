#include "led_matrix.h"

LEDMatrix::LEDMatrix() {
  //matrix = new MD_MAX72XX(HARDWARE_TYPE, PIN_DATA, PIN_CLK, PIN_CS, MAX_DEVICES);
  //matrix = new MD_MAX72XX(HARDWARE_TYPE, PIN_CS, MAX_DEVICES);
  matrix = new LedControl(PIN_DATA, PIN_CLK, PIN_CS, MAX_DEVICES);
}

void LEDMatrix::init() {
  //matrix->begin();
  //matrix->clear();
  //matrix->control(MD_MAX72XX::WRAPAROUND, MD_MAX72XX::ON);
  //matrix->control(MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);

  for (int x = 0; x < MAX_DEVICES; x++) {
    matrix->shutdown(x, false);       //The MAX72XX is in power-saving mode on startup
    matrix->setIntensity(x, 8);       // Set the brightness to default value
    matrix->clearDisplay(x);         // and clear the display
  }
}

void LEDMatrix::update() {
  //matrix->update();
/*
  long currentTimeMs = millis();
  long elapsedTime = currentTimeMs - lastFrameTimeMs;
  if (elapsedTime >= timePerFrameMs) {

  switch (status) {
    case CONTENT_CLEAR:
      drawClear();
      break;

    case CONTENT_BOX:
      drawBox();
      break;

    case CONTENT_SIGN:
      drawSign();
      break;

    case CONTENT_FILL:
      fillAll();
      break;

    default:
      Serial.print("Invalid content state: ");
      Serial.println(status);
      break;
  }
  lastFrameTimeMs = currentTimeMs;
  }
  */

  switch (status) {
    case CONTENT_CLEAR:
      drawClear();
      break;

    case CONTENT_BOX:
      drawBox();
      break;

    case CONTENT_SIGN:
      drawSign();
      break;

    case CONTENT_FILL:
      fillAll();
      break;

    default:
      Serial.print("Invalid content state: ");
      Serial.println(status);
      break;
  }
}

void LEDMatrix::setContentStatus(uint8_t newStatus) {
  status = newStatus;
}

void LEDMatrix::drawSign() {
  //matrix->clear();
  //matrix->control(MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);


  for (uint16_t  col=0; col < COLUMN_COUNT; col++) {
    setColumn(col, pixels_sign[col]);
  }
  
 /*
  matrix->setRow(2,0,B00000000);     matrix->setRow(1,0,B00000000);     matrix->setRow(0,0,B00000000);
       matrix->setRow(2,1,B01111111);     matrix->setRow(1,1,B11111111);     matrix->setRow(0,1,B11111110);
       matrix->setRow(2,2,B01000000);     matrix->setRow(1,2,B00000000);     matrix->setRow(0,2,B00000010);
       matrix->setRow(2,3,B01000000);     matrix->setRow(1,3,B00000000);     matrix->setRow(0,3,B00000010);
       matrix->setRow(2,4,B01000000);     matrix->setRow(1,4,B00000000);     matrix->setRow(0,4,B00000010);
       matrix->setRow(2,5,B01000000);     matrix->setRow(1,5,B00000000);     matrix->setRow(0,5,B00000010);
       matrix->setRow(2,6,B01000000);     matrix->setRow(1,6,B00000000);     matrix->setRow(0,6,B00000010);
       matrix->setRow(2,7,B01000000);     matrix->setRow(1,7,B00000000);     matrix->setRow(0,7,B00000010);
  
       matrix->setRow(5,0,B01000000);     matrix->setRow(4,0,B00000000);     matrix->setRow(3,0,B00000010);
       matrix->setRow(5,1,B01000000);     matrix->setRow(4,1,B00000000);     matrix->setRow(3,1,B00000010);
       matrix->setRow(5,2,B01000000);     matrix->setRow(4,2,B00000000);     matrix->setRow(3,2,B00000010);
       matrix->setRow(5,3,B01000000);     matrix->setRow(4,3,B00000000);     matrix->setRow(3,3,B00000010);
       matrix->setRow(5,4,B01000000);     matrix->setRow(4,4,B00000000);     matrix->setRow(3,4,B00000010);
       matrix->setRow(5,5,B01000000);     matrix->setRow(4,5,B00000000);     matrix->setRow(3,5,B00000010);
       matrix->setRow(5,6,B01111111);     matrix->setRow(4,6,B11111111);     matrix->setRow(3,6,B11111110);
       matrix->setRow(5,7,B00000000);     matrix->setRow(4,7,B00000000);     matrix->setRow(3,7,B00000000); 
       */ 
       
  //matrix->control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);

  //status = FLAG_SIGN;
  //matrix->update();
}

void LEDMatrix::fillAll() {
  //matrix->control(MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);
  //matrix->clear();

  for (uint16_t  col=0; col < COLUMN_COUNT; col++) {
    setColumn(col, pixels_box[col % 8]);
  }
  
/*
       matrix->setRow(2,0,B00000000);     matrix->setRow(1,0,B00000000);     matrix->setRow(0,0,B00000000);
       matrix->setRow(2,1,B01111111);     matrix->setRow(1,1,B11111111);     matrix->setRow(0,1,B11111110);
       matrix->setRow(2,2,B01000000);     matrix->setRow(1,2,B00000000);     matrix->setRow(0,2,B00000010);
       matrix->setRow(2,3,B01000000);     matrix->setRow(1,3,B00000000);     matrix->setRow(0,3,B00000010);
       matrix->setRow(2,4,B01000000);     matrix->setRow(1,4,B00000000);     matrix->setRow(0,4,B00000010);
       matrix->setRow(2,5,B01000000);     matrix->setRow(1,5,B00000000);     matrix->setRow(0,5,B00000010);
       matrix->setRow(2,6,B01000000);     matrix->setRow(1,6,B00000000);     matrix->setRow(0,6,B00000010);
       matrix->setRow(2,7,B01000000);     matrix->setRow(1,7,B00000000);     matrix->setRow(0,7,B00000010);
  
       matrix->setRow(5,0,B01000000);     matrix->setRow(4,0,B00000000);     matrix->setRow(3,0,B00000010);
       matrix->setRow(5,1,B01000000);     matrix->setRow(4,1,B00000000);     matrix->setRow(3,1,B00000010);
       matrix->setRow(5,2,B01000000);     matrix->setRow(4,2,B00000000);     matrix->setRow(3,2,B00000010);
       matrix->setRow(5,3,B01000000);     matrix->setRow(4,3,B00000000);     matrix->setRow(3,3,B00000010);
       matrix->setRow(5,4,B01000000);     matrix->setRow(4,4,B00000000);     matrix->setRow(3,4,B00000010);
       matrix->setRow(5,5,B01000000);     matrix->setRow(4,5,B00000000);     matrix->setRow(3,5,B00000010);
       matrix->setRow(5,6,B01111111);     matrix->setRow(4,6,B11111111);     matrix->setRow(3,6,B11111110);
       matrix->setRow(5,7,B00000000);     matrix->setRow(4,7,B00000000);     matrix->setRow(3,7,B00000000);
       */
  
  //matrix->control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);

  //status = FLAG_FILL;
  //matrix->update();
}

void LEDMatrix::drawBox() {
  //matrix->clear();
  //matrix->control(MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);


  for (uint16_t  col=0; col < COLUMN_COUNT; col++) {
    if (col % ROW_LENGTH == 0 ||
       col % ROW_LENGTH == ROW_LENGTH - 1) {
      setColumn(col, 0xFF);
    } else if (col < COLUMN_COUNT / 2 ) {
      setColumn(col, 0x01);
    } else {
      setColumn(col, 0x80);
    }
  }

  /*
       matrix->setRow(2,0,B00000000);     matrix->setRow(1,0,B00000000);     matrix->setRow(0,0,B00000000);
       matrix->setRow(2,1,B00000000);     matrix->setRow(1,1,B00000000);     matrix->setRow(0,1,B00000000);
       matrix->setRow(2,2,B00111111);     matrix->setRow(1,2,B11111111);     matrix->setRow(0,2,B11111100);
       matrix->setRow(2,3,B00100000);     matrix->setRow(1,3,B00000000);     matrix->setRow(0,3,B00000100);
       matrix->setRow(2,4,B00100000);     matrix->setRow(1,4,B00000000);     matrix->setRow(0,4,B00000100);
       matrix->setRow(2,5,B00100000);     matrix->setRow(1,5,B00000000);     matrix->setRow(0,5,B00000100);
       matrix->setRow(2,6,B00100000);     matrix->setRow(1,6,B00000000);     matrix->setRow(0,6,B00000100);
       matrix->setRow(2,7,B00100000);     matrix->setRow(1,7,B00000000);     matrix->setRow(0,7,B00000100);
  
       matrix->setRow(5,0,B00100000);     matrix->setRow(4,0,B00000000);     matrix->setRow(3,0,B00000100);
       matrix->setRow(5,1,B00100000);     matrix->setRow(4,1,B00000000);     matrix->setRow(3,1,B00000100);
       matrix->setRow(5,2,B00100000);     matrix->setRow(4,2,B00000000);     matrix->setRow(3,2,B00000100);
       matrix->setRow(5,3,B00100000);     matrix->setRow(4,3,B00000000);     matrix->setRow(3,3,B00000100);
       matrix->setRow(5,4,B00100000);     matrix->setRow(4,4,B00000000);     matrix->setRow(3,4,B00000100);
       matrix->setRow(5,5,B00111111);     matrix->setRow(4,5,B11111111);     matrix->setRow(3,5,B11111100);
       matrix->setRow(5,6,B00000000);     matrix->setRow(4,6,B00000000);     matrix->setRow(3,6,B00000000);
       matrix->setRow(5,7,B00000000);     matrix->setRow(4,7,B00000000);     matrix->setRow(3,7,B00000000); 
       */
  
  //matrix->control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);

  //status = FLAG_BOX;
  //matrix->update();
}

void LEDMatrix::drawClear() {
    for (int x = 0; x < MAX_DEVICES; x++) {
      matrix->clearDisplay(x);         // and clear the display
    }
}



void LEDMatrix::setColumn(uint16_t c, uint8_t val) {
  uint16_t deviceCol = PIXEL_PER_DEVICE - 1 - c % 8;
  uint16_t deviceNum = c / PIXEL_PER_DEVICE;
  
  matrix->setColumn(deviceNum, deviceCol, val);
}
