int directionPins[] = {2};
int speedPins[] = {3};

int motorNum = 1;

int speed, dtime;
bool dir; 

void setup() {
  // put your setup code here, to run once:
  for (int i = 0; i < motorNum; i++) {
    // Assigning and declaring the pins
    pinMode(directionPins[i], OUTPUT);
    pinMode(speedPins[i], OUTPUT);
  }
  Serial.begin(9600);
  Serial.println("Enter the direction.speed.time: ");
}

void loop() {

  if (Serial.available() > 0) {
    // Eg. 0.100.3
    dir = Serial.readStringUntil('.').toInt();
    speed = Serial.readStringUntil('.').toInt();
    dtime = Serial.readString().toInt();
    Serial.print(directionPins[0]);
    Serial.print(" ");
    Serial.print(speed);
    Serial.print(" ");
    Serial.println(dtime);

    if (speed >= 0 && speed < 256) {
      // Rotate the motor with the given {speed}, {time}, {direction}
      for (int i = 0; i < motorNum; i++) {
        digitalWrite(directionPins[i], dir);
        analogWrite(speedPins[i], speed);
      }
      delay(dtime * 1000);
    } else {
      Serial.println("Enter Speed value less than 256 or greater than 0");
    }

  }
}
