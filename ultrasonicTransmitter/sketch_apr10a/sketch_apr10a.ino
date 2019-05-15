#define PIN_TRIGGER 3
#define FREQUENCY 40000 

void setup() {
  // put your setup code here, to run once:
  pinMode(PIN_TRIGGER, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  tone(PIN_TRIGGER, FREQUENCY);
  delay(50);
  noTone(PIN_TRIGGER);
  delay(50);
}
