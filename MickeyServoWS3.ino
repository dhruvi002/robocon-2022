#include <Servo.h>

#define servoNum 1
int servo_pins[servoNum] = {9};

Servo servo[servoNum];

int dtime = 20;

void setup()
{
  for (int i = 0; i < servoNum; i++) {
    servo[i].attach(servo_pins[i]);
    servo[i].write(0);
  }
}

void loop() {
  // Rotate from 0° to 180°
  for (int pos = 0; pos <= 180; pos++) {
    for (int i = 0; i < servoNum; i++) {
      servo[i].write(pos);
    }
    delay(dtime);
  }
  // Rotate from 180° to 0°
  for (int pos = 180; pos >= 0 ; pos--) {
    for (int i = 0; i < servoNum; i++) {
      servo[i].write(pos);
    }
    delay(dtime);
  }
}
