// motor connections
int digitalPins[4] = {22, 3, 5, 7};
int analogPins[4] = {2, 4, 6, 8};


void setup() {
    // Set all the motor control pins to outputs
    for(int i=0; i<4; i++) {
      pinMode(digitalPins[i], OUTPUT);
      pinMode(analogPins[i], OUTPUT);
    }
}

void loop() {
  working();
  delay(1000);
}
void working() {
  // running all motors
  for(int i=0; i<4; i++) {
      digitalWrite(digitalPins[i], HIGH);
      analogWrite(analogPins[i], 100);
    }
   delay(5000);
 // stopping the motor for 5 seconds
   for(int i=0; i<4; i++) {
        analogWrite(analogPins[i], 0);
   }
   delay(2000);
 // direction change for all motors
 for(int i=0; i<4; i++) {
      digitalWrite(digitalPins[i], LOW);
      analogWrite(analogPins[i], 100);
    }
  delay(5000);
 // stopping the motor for 5 seconds
  for(int i=0; i<4; i++) {
    analogWrite(analogPins[i], 0);
  }
  delay(2000);
}
