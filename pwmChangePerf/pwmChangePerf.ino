#include "Wire.h"

int sensePin = 8;
int outPin = 3;

int state = LOW;

void setPwmFrequency(int pin, int divisor) {
   byte mode;
   if(pin == 5 || pin == 6 || pin == 9 || pin == 10) {
     switch(divisor) {
       case 1: mode = 0x01; break;
       case 8: mode = 0x02; break;
       case 64: mode = 0x03; break;
       case 256: mode = 0x04; break;
       case 1024: mode = 0x05; break;
       default: return;
     }
     if(pin == 5 || pin == 6) {
       TCCR0B = TCCR0B & 0b11111000 | mode;
     } else {
       TCCR1B = TCCR1B & 0b11111000 | mode;
     }
   } else if(pin == 3 || pin == 11) {
     switch(divisor) {
       case 1: mode = 0x01; break;
       case 8: mode = 0x02; break;
       case 32: mode = 0x03; break;
       case 64: mode = 0x04; break;
       case 128: mode = 0x05; break;
       case 256: mode = 0x06; break;
       case 1024: mode = 0x7; break;
       default: return;
     }
     TCCR2B = TCCR2B & 0b11111000 | mode;
   }
}

void setup() {
  Serial.begin(9600);
  
  /*pinMode(outPin, OUTPUT);
      Wire.begin();
    analogWrite(outPin,1);
    Wire.beginTransmission(0x20);
    Wire.write(0x29);
    Wire.write(0x02);
    Wire.endTransmission();

    //analogWrite(outPin, 128);*/

    pinMode(outPin, OUTPUT);
    pinMode(sensePin, INPUT);
    setPwmFrequency(outPin, 1);
}

void loop() {
  int val = digitalRead(sensePin);
  if (val != state) {
    state = val;
    analogWrite(outPin, 128 & (-val));
  }
}
