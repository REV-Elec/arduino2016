const int ZERO_CUTOFF = 350;
const float DAMPING = 1000.0;
const int SHIFT_TO_LONG = 21;
const int SHIFT_TO_BYTE = 23;
const bool INVERT = true;

const int INPUT_PIN = A3;
const int OUTPUT_PIN = 10;

const int ZERO_POINT = 160;
const int MAX = 860;

float adjustedLastReading = 0.0;
void setup() {
  //Serial.begin(9600);
  pinMode(OUTPUT_PIN, OUTPUT);
}


void loop() {
    int reading = analogRead(INPUT_PIN);

    //Serial.print(reading);
    //Serial.print(" ");
    if (reading < ZERO_CUTOFF)
      reading = 0;
    else
      reading -= ZERO_POINT;
    if (reading > MAX)
      reading = MAX;
      
    if (millis() < 500) {
      reading = 0;
    }
    float zeroToOneThrottle = reading / (float) (MAX - ZERO_POINT);
    
    adjustedLastReading += (zeroToOneThrottle - adjustedLastReading)/ DAMPING;
    int toWrite; 
     if (INVERT)
       toWrite = (int) (255.0 * (1.0- adjustedLastReading));
    else
      toWrite = (int) (255.0 * adjustedLastReading);
    
    analogWrite(OUTPUT_PIN, toWrite);
    //Serial.print(adjustedLastReading);
    //Serial.print(" ");
    //Serial.println(toWrite);
    //analogWrite(OUTPUT_PIN, 0);
}
