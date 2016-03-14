void setup() {
  // put your setup code here, to run once:
  //Digital input signals, from switch to the Arduino
  pinMode(2, INPUT); //Left TS
  pinMode(4, INPUT); //Right TS
  pinMode(6, INPUT); //Headlights
  pinMode(8, INPUT); //Brake/Rear

  //Digital output signals, from Arduino to lights
  pinMode(3, OUTPUT); //Left
  pinMode(5, OUTPUT); //Right
  pinMode(7, OUTPUT); //Head
  pinMode(9, OUTPUT); //Brake/Rear

  int ltsInPin = 2;
  int rtsInPin = 4;
  int headInPin = 6;
  int brakeInPin = 8;

  int ltsOutPin = 3;
  int rtsOutPin = 5;
  int headOutPin = 7;
  int brakeOutPin = 9;

  //Setup: turn all lights off
  digitalWrite(ltsOutPin, LOW);
  digitalWrite(rtsOutPin, LOW);
  digitalWrite(headOutPin, LOW);
  digitalWrite(brakeOutPin, LOW);
  
}

void loop() {
  // put your main code here, to run repeatedly:

  //Read the switch values
  ltsInVal = digitalRead(ltsInPin);
  rtsInVal = digitalRead(rtsInpin);
  headInVal = digitalRead(headInPin);
  brakeInVal = digitalRead(brakeInPin);

  //Headlights; This is simple, just read the current switch value and set the headlights to that value.
  if(headInVal == HIGH){ //If switch closed, turn lights on and keep them on
    digitalWrite(headOutPin, HIGH);
  }
  if(headInVal == LOW){ //If switch open, turn lights off and keep them off
    digitalWrite(headOutPin, LOW);
  }

  //Brake/Rear lights: If brake pedal pressed, turn on. If front headlights turned on, turn on. If both off, turn lights off.
  if(brakeInVal==HIGH || headInVal==HIGH){
    digitalWrite(brakeOutPin, HIGH);
  }
  else{
    digitalWrite(brakeOutPin, LOW);
  }

  //Left turn signal: We're using Delay here, but that should be updated to not interfere with the rest of the loop.
  //If LTS on, then turn light on, delay, turn light off, delay, and continue with loop. If LTS off, then lights should already be off and nothing needs to be changed.
  if(ltsInVal == HIGH){
    digitalWrite(ltsOutPin, HIGH);
    delay(1000); //wait one second
    digitalWrite(ltsOutPin, LOW);
    delay(1000);
  }

  //RTS: same thing as LTS
  if(rtsInVal == HIGH){
    digitalWrite(rtsOutPin, HIGH);
    delay(1000); //wait one second
    digitalWrite(rtsOutPin, LOW);
    delay(1000);
  }

  
  
  
  



  //SAMPLE CODE
  digitalWrite(3, HIGH);   // sets the LED on
  delay(1000);                  // waits for a second
  digitalWrite(3, LOW);    // sets the LED off
  delay(1000);                  // waits for a second
}
