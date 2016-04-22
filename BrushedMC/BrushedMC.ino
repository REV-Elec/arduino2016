const int ZERO_CUTOFF = 75;
const long DAMPING = 10000L;
const int SHIFT_TO_LONG = 21;
const int SHIFT_TO_BYTE = 2;
const bool INVERT = false;

const int INPUT_PIN = 0;
const int OUTPUT_PIN = 0;

int adjustedLastReading = 0;
void setup() {
  pinMode(OUTPUT_PIN, OUTPUT);
}

void loop() {
    int reading = analogRead(INPUT_PIN);
    if (reading < ZERO_CUTOFF)
      reading = 0;
    adjustedLastReading += ((((long)reading - (long)adjustedLastReading) << SHIFT_TO_LONG)/DAMPING) >> SHIFT_TO_LONG;
    if (INVERT)
      analogWrite(OUTPUT_PIN, 255 - (reading >> SHIFT_TO_BYTE));
    else
      analogWrite(OUTPUT_PIN, reading >> SHIFT_TO_BYTE);
}
