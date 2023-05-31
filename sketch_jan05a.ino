int directionPins[] = {22, 3};
int speedPins[] = {2, 4};

int speed = 102;
int motorNum = 2;

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
        analogWrite(speedPins[i], speed);
      }
}
