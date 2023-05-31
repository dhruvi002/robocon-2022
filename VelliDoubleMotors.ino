int directionPins[] = {5};
int speedPins[] = {9};

int motorNum = 1;

void setup() {
  for (int i = 0; i < motorNum; i++) {
    pinMode(directionPins[i], OUTPUT);
    pinMode(speedPins[i], OUTPUT);
  }
  Serial.begin(9600);
}

void loop() {
      for (int i = 0; i < motorNum; i++) {
        digitalWrite(directionPins[i], HIGH);
        analogWrite(speedPins[i], 100);
      }
      delay(500);
 }
