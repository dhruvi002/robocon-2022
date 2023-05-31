#include <PS3BT.h>
#include <usbhub.h>

#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>

USB Usb;

BTD Btd(&Usb);
PS3BT PS3(&Btd);

// Motor pins N,E,S,W
int directionPins[] = {5, 7, 32, 3};
int speedPins[] = {6, 8, 2, 4};

// number of motors
int motorNum = 4;

// Speed and direction of x and y
int xspeed = 0, yspeed = 0, speed = 0;
bool  xdirection, ydirection;

void setup() {
  Serial.begin(115200);
#if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); //halt
  }
  Serial.print(F("\r\nPS3 Bluetooth Library Started"));

  //  Motor pins declerations
  for (int i = 0; i < motorNum; i++) {
    // Assigning and declaring the pins
    pinMode(directionPins[i], OUTPUT);
    pinMode(speedPins[i], OUTPUT);
  }
}
void loop() {
  Usb.Task();

  if (PS3.PS3Connected || PS3.PS3NavigationConnected) {
    // 107 - 147
    if (PS3.getAnalogHat(LeftHatY) > 147 ||
        PS3.getAnalogHat(LeftHatY) < 107) {

      Serial.print("\tLeftHatY: ");
      Serial.print(PS3.getAnalogHat(LeftHatY));

      yspeed = PS3.getAnalogHat(LeftHatY);

      if (yspeed > 147) {
        ydirection = 1;
        yspeed = map(yspeed, 148, 255, 0, 150);
      } else if (yspeed < 107) {
        ydirection = 0;
        yspeed = map(yspeed, 106, 0, 0, 150);
      }

      Serial.print("\nyspeed = ");
      Serial.print(yspeed);
      Serial.print("\tydir = ");
      Serial.print(ydirection);

      digitalWrite(directionPins[1], ydirection);
      analogWrite(speedPins[1], yspeed);
      digitalWrite(directionPins[3], ydirection);
      analogWrite(speedPins[3], yspeed);

    } else if (PS3.getAnalogHat(RightHatX) > 147 ||
               PS3.getAnalogHat(RightHatX) < 107) {

      Serial.print("\tRightHatX: ");
      Serial.print(PS3.getAnalogHat(RightHatX));

      xspeed = PS3.getAnalogHat(RightHatX);

      if (xspeed > 147) {
        xdirection = 1;
        xspeed = map(xspeed, 148, 255, 0, 150);
      } else if (xspeed < 107) {
        xdirection = 0;
        xspeed = map(xspeed, 106, 0, 0, 150);
      }
      Serial.print("\nxspeed = ");
      Serial.print(xspeed);
      Serial.print("\txdir = ");
      Serial.print(xdirection);

      digitalWrite(directionPins[0], xdirection);
      analogWrite(speedPins[0], xspeed);
      digitalWrite(directionPins[2], xdirection);
      analogWrite(speedPins[2], xspeed);

    } else if (PS3.getAnalogButton(L2)) {

      xspeed = map(PS3.getAnalogButton(L2), 0, 255, 0, 150);

      if (xspeed >= 0 && xspeed <= 150) {
        for (int i = 0; i < motorNum; i++) {
          digitalWrite(directionPins[i], 1);
          analogWrite(speedPins[i], xspeed);
        }
      }
      Serial.print("L2 working with speed: ");
      Serial.println(xspeed);

    } else if (PS3.getAnalogButton(R2)) {

      yspeed = map(PS3.getAnalogButton(R2), 0, 255, 0, 150);

      if (yspeed >= 0 && yspeed <= 150) {
        for (int i = 0; i < motorNum; i++) {
          digitalWrite(directionPins[i], 0);
          analogWrite(speedPins[i], yspeed);
        }
      }
      Serial.print("R2 working with speed: ");
      Serial.println(yspeed);

    } else {
      for (int i = 0; i < motorNum; i++) {
        analogWrite(speedPins[i], 0);
      }
      Serial.print("\nxspeed = 0\tyspeed = 0");
    }
  }
}
