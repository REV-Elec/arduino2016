const int N_TS = 2;
const int TS_IN[] = {0, 0};
const int TS_OUT[] = {5, 6};

const unsigned long NEVER_TRANSITION = -1;
unsigned long transitionTime[N_TS];

int state[N_TS];
// states: 0 totally off b/c switch off
//         1 ramping on
//         2 totally on
//         3 ramping off
//         4 totally off (but will turn on again)
const unsigned long TOTALLY_STATE_MS = 150;
const unsigned long RAMP_STATE_MS = 250;

const unsigned int MAX_PWM = 255;

const int BRAKE_IN = 0;
const int BRAKE_OUT = 9;

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < N_TS; i++) {
    pinMode(TS_IN[i], INPUT_PULLUP);
    pinMode(TS_OUT[i], OUTPUT);
    state[i] = 0;
    transitionTime[i] = NEVER_TRANSITION;
  }
  pinMode(BRAKE_IN, INPUT_PULLUP);
  pinMode(BRAKE_OUT, OUTPUT);
}

void loop() {
   for (int i = 0; i < N_TS; i++) {
     int pinVal = digitalRead(TS_IN[i]);
     if (pinVal == LOW) {
       state[i] = 0;
       transitionTime[i] = NEVER_TRANSITION;
     }
     else if (state[i] == 0) {
       state[i] = 1;
       transitionTime[i] = millis() + RAMP_STATE_MS;
     }
     
     if (transitionTime[i] != NEVER_TRANSITION && transitionTime[i] < millis()) {
       state[i]++;
       if (state[i] == 5)
         state[i] = 1;
       transitionTime[i] += (state[i] == 1 || state[i] == 3) ? RAMP_STATE_MS : TOTALLY_STATE_MS;
     }
     int duty = 0;
     switch(state[i]) {
       case 0:
         duty = 0;
         break;
       case 1:
         duty = MAX_PWM -((transitionTime[i] - millis())*MAX_PWM)/RAMP_STATE_MS;
         break;
       case 2:
         duty = MAX_PWM;
         break;
       case 3:
         duty = ((transitionTime[i] - millis())*MAX_PWM)/RAMP_STATE_MS;
         break;
       case 4:
         duty = 0;
         break;
     }
     analogWrite(TS_OUT[i], duty);
     //Serial.println(duty);
   }
   
   
   int brakeVal = digitalRead(BRAKE_IN);
   if (brakeVal == HIGH)
     analogWrite(BRAKE_OUT, MAX_PWM);
   else
     analogWrite(BRAKE_OUT, MAX_PWM/2);
}
