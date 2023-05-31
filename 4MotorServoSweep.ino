#include <Servo.h>

Servo myservo1;
Servo myservo2;
Servo myservo3;
Servo myservo4;
int pos = 0;    // variable to store the servo position

void setup() {
  myservo1.attach(9);
  myservo2.attach(10);  
  myservo3.attach(11);  
  myservo4.attach(12);  
}

void loop() {
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    myservo1.write(pos);
    myservo2.write(pos);
    myservo3.write(pos);
    myservo4.write(pos);
    delay(15);                       // waits 15 ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
   myservo1.write(pos);
   myservo2.write(pos);
   myservo3.write(pos);
   myservo4.write(pos);
   delay(15);                       // waits 15 ms for the servo to reach the position
  }
}
