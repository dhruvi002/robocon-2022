#include <PS3BT.h>
#include <usbhub.h>

#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>

USB Usb;

BTD Btd(&Usb);
PS3BT PS3(&Btd);

// Motor pins N,  E, S, W
//            32, 7, 5, 3
int directionPins[] = {{7, 5},{3, 22}};
int speedPins[] = {8, 6, 4, 2};
int change = 1;

// number of motors
int motorNum = 4;

// Speed and direction of x and y
int xspeed = 0, yspeed = 0;
bool  xdirection, ydirection;

void rotateRight(int *dp, int *sp) {
  int tempd, temps;
  tempd = dp[motorNum - 1];
  temps = sp[motorNum - 1];
  for (int i = motorNum - 2; i >= 0; i--) {
    dp[i + 1] = dp[i];
    sp[i + 1] = sp[i];
  }
  dp[0] = tempd;
  sp[0] = temps;
  if (change == 4) {
    change = 1;
    return;
  }
  change++;
}

void rotateLeft(int *dp, int *sp) {
  int tempd, temps;
  tempd = dp[0];
  temps = sp[0];
  for (int i = 0; i < motorNum - 1; i++) {
    dp[i] = dp[i + 1];
    sp[i] = sp[i + 1];
  }
  dp[motorNum - 1] = tempd;
  sp[motorNum - 1] = temps;
  if (change == 1) {
    change = 4;
    return;
  }
  change--;
}

void setup() {
  Serial.begin(115200);
#if !defined(_MIPSEL_)
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
        yspeed = map(yspeed, 148, 255, 0, 120);
      } else if (yspeed < 107) {
        ydirection = 0;
        yspeed = map(yspeed, 106, 0, 0, 120);
      }

      if (change == 3)
        ydirection = !ydirection;

      Serial.print("\nyspeed = ");
      Serial.print(yspeed);
      Serial.print("\tydir = ");
      Serial.print(ydirection);

      digitalWrite(directionPins[1], ydirection);
      analogWrite(speedPins[1], yspeed);
      digitalWrite(directionPins[3], ydirection);
      analogWrite(speedPins[3], yspeed);
    }
    if (PS3.getAnalogHat(RightHatX) > 147 ||
        PS3.getAnalogHat(RightHatX) < 107) {

      Serial.print("\tRightHatX: ");
      Serial.print(PS3.getAnalogHat(RightHatX));

      xspeed = PS3.getAnalogHat(RightHatX);

      if (xspeed > 147) {
        xdirection = 1;
        xspeed = map(xspeed, 148, 255, 0, 120);
      } else if (xspeed < 107) {
        xdirection = 0;
        xspeed = map(xspeed, 106, 0, 0, 120);
      }

      if (change == 3)
        xdirection = !xdirection;

      Serial.print("\nxspeed = ");
      Serial.print(xspeed);
      Serial.print("\txdir = ");
      Serial.print(xdirection);

      digitalWrite(directionPins[0], xdirection);
      analogWrite(speedPins[0], xspeed);
      digitalWrite(directionPins[2], xdirection);
      analogWrite(speedPins[2], xspeed);
    }
    if (PS3.getAnalogButton(L2)) {

      xspeed = map(PS3.getAnalogButton(L2), 0, 255, 0, 120);

      for (int i = 0; i < motorNum / 2; i++) {
        digitalWrite(directionPins[i], 0);
        analogWrite(speedPins[i], xspeed);
      }
      for (int i = 2; i < motorNum; i++) {
        digitalWrite(directionPins[i], 1);
        analogWrite(speedPins[i], xspeed);
      }
      Serial.print("L2 working with speed: ");
      Serial.println(xspeed);

    } else if (PS3.getAnalogButton(R2)) {

      yspeed = map(PS3.getAnalogButton(R2), 0, 255, 0, 120);

      for (int i = 0; i < motorNum / 2; i++) {
        digitalWrite(directionPins[i], 1);
        analogWrite(speedPins[i], yspeed);
      }
      for (int i = 2; i < motorNum; i++) {
        digitalWrite(directionPins[i], 0);
        analogWrite(speedPins[i], yspeed);
      }
      Serial.print("R2 working with speed: ");
      Serial.println(yspeed);

    } else {
      if (PS3.getAnalogHat(LeftHatY) < 147 &&
          PS3.getAnalogHat(LeftHatY) > 107
         ) {
        analogWrite(speedPins[1], 0);
        analogWrite(speedPins[3], 0);
        Serial.print("\nxspeed = 0");

      }
      if (PS3.getAnalogHat(RightHatX) < 147 &&
          PS3.getAnalogHat(RightHatX) > 107 ) {
        analogWrite(speedPins[0], 0);
        analogWrite(speedPins[2], 0);
        Serial.print("\nyspeed = 0");
      }
    }

    if (PS3.getButtonClick(L1)) {
      rotateLeft(directionPins, speedPins);
      Serial.println("PRESSED L1, now pins shifted anti-clockwise");
    }
    if (PS3.getButtonClick(R1)) {
      rotateRight(directionPins, speedPins);
      Serial.println("PRESSED R1, now pins shifted clockwise");
    }
  }
}
