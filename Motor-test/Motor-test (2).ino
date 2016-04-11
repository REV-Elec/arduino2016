#include <limits.h>

#define P_ENABLE 7

enum pin {
  A_H=5,
  A_L=3,
  B_H=9,
  B_L=6,
 C_H=11,
 C_L=10
};

#define N_PINS 6
pin allPins[N_PINS] = {A_H, A_L, B_H, B_L, C_H, C_L};
int ledPin = 13;
void setup() {
   // put your setup code here, to run once:
  Serial.begin(9600);
  
  int mask = ~7;
  TCCR1B = (TCCR1B & mask) | 1;
  TCCR2B = (TCCR2B & mask) | 1;
  TCCR3B = (TCCR3B & mask) | 1;
  TCCR4B = (TCCR4B & mask) | 1;
  
  pinMode(P_ENABLE, OUTPUT);
  digitalWrite(P_ENABLE, LOW);
  
   pinMode(ledPin, OUTPUT);
  
  for (int i = 0; i < N_PINS; i++)
    pinMode(allPins[i], OUTPUT);
  
  // Init hall  
  pinMode(47, OUTPUT);
  digitalWrite(47, HIGH);
  
  pinMode(49, INPUT_PULLUP);
  pinMode(51, INPUT_PULLUP);
  pinMode(53, INPUT_PULLUP);
}
pin ACTIVE_HIGH[] = {C_H, A_H, A_H, B_H, B_H, C_H};
pin ACTIVE_LOW[] = {B_L, B_L, C_L, C_L, A_L, A_L};
int stateMapping[] = {-1, 0, 4, 5, 2, 1, 3, -1};
int state = -1;
int speed = 128;

unsigned long turnOffTime = ULONG_MAX;
void loop() {
  if (millis() > turnOffTime)
  {
    turnOffTime = ULONG_MAX;
     digitalWrite(ledPin, LOW);
  }
  // 49, 51, 53
   int iState = digitalRead(51) | (digitalRead(53) << 1) | (digitalRead(49) << 2);
   int newState = stateMapping[iState];
   //Serial.println(newState);
   if (state != newState)
   {
     if (newState == -1)
     {
       turnOffTime = millis() + 200;
       digitalWrite(ledPin, HIGH);
     }
     else if ((state == -1) || (newState == state - 1) || ((state == 0) && (newState == 5)))
     {
       state = newState;
       //Serial.println(state);
     }
   }
   for (int i = 0; i < N_PINS; i++)
   {
     if (allPins[i] == ACTIVE_HIGH[state])
       analogWrite(allPins[i], speed);
     else if (allPins[i] == ACTIVE_LOW[state])
       analogWrite(allPins[i], 255);
     else
        analogWrite(allPins[i], 0);
   }
}
