#define P_ENABLE 7

enum Pins {
  A_H=5,
  A_L=3,
  B_H=9,
  B_L=6,
 C_H=11,
 C_L=10
};

#define N_PINS 6
Pins allPins[N_PINS] = {A_H, A_L, B_H, B_L, C_H, C_L};
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
    
  analogWrite(allPins[0], 128);
}
byte buf[1024];
int currentPin = 0; 
void loop() {
  delay(5000);
  digitalWrite(ledPin, HIGH);
  delay(200);
  digitalWrite(ledPin, LOW);
  
  analogWrite(allPins[currentPin], 0);
  //currentPin = (currentPin + 1) % N_PINS;
  analogWrite(allPins[currentPin], 128);
  //Serial.print("Now doing PWM on pin ");
  //Serial.println(allPins[currentPin]);
}
