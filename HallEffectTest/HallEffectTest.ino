void setup() {
  pinMode(47, OUTPUT);
  digitalWrite(47, HIGH);
  
  pinMode(49, INPUT);
  pinMode(51, INPUT);
  pinMode(53, INPUT);
  
  Serial.begin(9600);

}
int stateMapping[] = {-1, 0, 4, 5, 2, 1, 3, -1};

int lstate = -1;
void loop() {
  int iState = digitalRead(49) | (digitalRead(51) << 1) | (digitalRead(53) << 2);
  if (iState != lstate)
  {
    lstate = iState;
    Serial.println(stateMapping[iState]);
  }
}
