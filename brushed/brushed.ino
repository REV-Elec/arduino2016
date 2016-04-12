int i = 0;
int dir = 1;
void setup() {
  // put your setup code here, to run once:
  pinMode(8, OUTPUT);
  pinMode(13, OUTPUT);
  
  digitalWrite(13, LOW);
  
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  //int val = analogRead(A7);
  //Serial.println(val);
  
  analogWrite(8, i);
  i += dir;
  if (i == 0 || i == 0x7F)
    dir = -dir;
  delay(50);
}
