int directionPins[] = {5, 7};
int speedPins[] = {6, 8};

int motorNum = 2;

int speed, dtime, direction;

void setup() {
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
    // Eg. 0.100:3 in direction.speed.time
    direction = (Serial.readStringUntil('.')).toInt();
    speed = (Serial.readStringUntil('.')).toInt();
    dtime = (Serial.readString()).toInt();
    Serial.print(direction);
    Serial.print(" ");
    Serial.print(speed);
    Serial.print(" ");
    Serial.println(dtime);

    if (speed >= 0 && speed < 256) {
      // Rotate the motor with the given //({speed}, {time}, {direction}) 
      for (int i = 0; i < motorNum; i++) {
        digitalWrite(directionPins[i], direction);
        analogWrite(speedPins[i], speed);
      }
      delay(dtime);
      for (int i = 0; i < motorNum; i++) {
        analogWrite(speedPins[i], 0);
      }
    } else {
      Serial.println("Enter Speed value less than 256 or greater than 0");
    }

  }
}

// PLS DON'T GO BEYOND THIS LINE
// ------------ BASIC ------------
//int directionPins[] = {32, 3, 5, 7};
//int speedPins[] = {2, 4, 6, 8};
//
//int speed;
//
//
//void setup() {
//  // put your setup code here, to run once:
//  for (int i = 0; i < 4; i++) {
//    pinMode(directionPins[i], OUTPUT);
//    pinMode(speedPins[i], OUTPUT);
//  }
//  Serial.begin(9600);
//  Serial.println("Enter the speed: ");
//}
//
//void loop() {
//
//  if (Serial.available()) {
//
//    speed = Serial.parseInt();
//
//    if (speed > 0 && speed < 256) {
//      // Rotate Clockwise with speed of 100 for 5s
//      for (int i = 0; i < 4; i++) {
//        digitalWrite(directionPins[i], HIGH);
//        analogWrite(speedPins[i], speed);
//      }
//      delay(5000);
//
//      // Stop for 2s
//      for (int i = 0; i < 4; i++) {
//        analogWrite(speedPins[i], 0);
//      }
//      delay(2000);
//
//      // Rotate Clockwise with speed of 100 for 5s
//      for (int i = 0; i < 4; i++) {
//        digitalWrite(directionPins[i], LOW);
//        analogWrite(speedPins[i], speed);
//      }
//      delay(5000);
//
//      // Stop for 2s
//      for (int i = 0; i < 4; i++) {
//        analogWrite(speedPins[i], 0);
//      }
//      delay(2000);
//    }
//  }
//
//}

// ------------ VERSION 1 ------------
//int directionPins[] = {5, 7};
//int speedPins[] = {6, 8};
//
//int speed, direction[2], time;
//
//void setup() {
//  // put your setup code here, to run once:
//  for (int i = 0; i < 2; i++) {
//    pinMode(directionPins[i], OUTPUT);
//    pinMode(speedPins[i], OUTPUT);
//  }
//  Serial.begin(9600);
//  Serial.println("Enter the direction1,direction2,speed: ");
//}
//
//void loop() {
//
//  if (Serial.available() > 0) {
//    direction[0] = Serial.readStringUntil('.').toInt();
//    direction[1] = Serial.readStringUntil('.').toInt();
//    speed = Serial.readString().toInt();
//    Serial.print(direction[0]);
//    Serial.print(" ");
//    Serial.print(direction[1]);
//    Serial.print(" ");
//    Serial.println(speed);
//  }
//
//  if (speed >= 0 && speed < 256) {
//    // Rotate Clockwise with speed of 100 for 5s
//    for (int i = 0; i < 2; i++) {
//      digitalWrite(directionPins[i], direction[i]);
//      analogWrite(speedPins[i], speed);
//    }
//  }
//
//}
