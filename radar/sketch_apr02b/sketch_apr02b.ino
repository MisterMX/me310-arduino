#define PIN_OUT 10
#define PIN_VIN 11
#define PIN_CDS 12

int Sensor = 2;   //Input Pin
int LED = 13;     // Led pin for Indication
 
int flg = 0;  //Change detection flag
void setup() {
    Serial.begin(9600);
  pinMode (PIN_OUT, INPUT);  //Define Pin as input
  //pinMode (LED, OUTPUT);    //Led as OUTPUT
  Serial.println("Waiting for motion");
}
 
void loop() {
    int val = digitalRead(PIN_OUT); //Read Pin as input
     
    if (val > 0 && flg == 0) {
      Serial.println("Motion Detected");
      flg = 1;
    }
 
     if(val == 0 && flg == 1) {
        Serial.println("No motion anymore!");
        flg = 0;
     }
}
