#include "MedianFilterLib.h"
#include "Plotter.h"

#define PIN_ECHO A5
#define PIN_TRIGGER 11

MedianFilter<int> medianFilter(10);

Plotter p;
int analogVal;
int rounded;
int median;

void setup() {
  // put your setup code here, to run once:
  //Serial.begin(115200);

  p.Begin();
  p.AddTimeGraph("AnalogRead", 10000, "", analogVal);
  //p.AddTimeGraph("AnalogRounded", 10000, "", rounded);
  p.AddTimeGraph("AnalogMedian", 10000, "", median);
  
  //pinMode(PIN_TRIGGER, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
}

void loop() {
  //digitalWrite(PIN_TRIGGER, HIGH);

  analogVal = analogRead(PIN_ECHO);
  

  //rounded = roundInt(analogVal);
  median = medianFilter.AddValue(analogVal);

  
  //Serial.println(analogVal);
/*int median; 
  
  for (int i = 0; i < 20; i++) {
    median = medianFilter.AddValue(analogVal);
  }
  
  Serial.println(median);*/
  
  //int digitalVal = LOW;
  
  /*while (digitalVal == LOW) {
    analogVal = analogRead(PIN_ECHO);
    digitalVal = digitalRead(PIN_ECHO);
    //Serial.print("Analog: ");
    Serial.println(analogVal);
    //Serial.print("; digital: ");
    //Serial.print(digitalVal);
    //Serial.println("");
  }*/

  //delay(20);

  p.Plot();
}

int roundInt(int i) {
    int rest = i % 10;

    return rest < 5
      ? i - rest
      : i + 10 - rest;
}
