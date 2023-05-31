#include <Servo.h>

#define servoPin 26

Servo servo;
int dtime = 20, pos;

void setup()
{
  servo.attach(servoPin);
}

void loop() {
  servo.write(0);
  // Rotate from 0° to 180°
  for (pos = 0; pos <= 180; pos++) {
    servo.write(pos);
    delay(dtime);
  }
  // Rotate from 180° to 0°
  for (pos = 180; pos >= 0 ; pos--) {
    servo.write(pos);
    delay(dtime);
  }
}
