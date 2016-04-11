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
void setup() {
   Serial.begin(9600);
  
  int mask = ~7;
  TCCR1B = (TCCR1B & mask) | 1;
  TCCR2B = (TCCR2B & mask) | 1;
  TCCR3B = (TCCR3B & mask) | 1;
  TCCR4B = (TCCR4B & mask) | 1;
  
  
  for (int i = 0; i < N_PINS; i++)
    pinMode(allPins[i], OUTPUT);
  
  pinMode(P_ENABLE, OUTPUT);
  digitalWrite(P_ENABLE, LOW);
  // Init hall  
  pinMode(47, OUTPUT);
  digitalWrite(47, HIGH);
  
  pinMode(49, INPUT);
  pinMode(51, INPUT);
  pinMode(53, INPUT);
  
  pinMode(13, OUTPUT);
}

pin ACTIVE_HIGH[] = {C_H, A_H, A_H, B_H, B_H, C_H};
pin ACTIVE_LOW[] = {B_L, B_L, C_L, C_L, A_L, A_L};
int stateMapping[] = {-1, 0, 4, 5, 2, 1, 3, -1};
int state = 0;
int speed = 128;

void loop() {
  if (Serial.available() > 0) {
    state = Serial.read() - '0';
    Serial.print("Switched to state ");
    Serial.println(state);
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
