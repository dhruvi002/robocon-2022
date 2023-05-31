#include <PS3BT.h>
#include <usbhub.h>

#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>

USB Usb;

BTD Btd(&Usb);
PS3BT PS3(&Btd);

// Motor pins SNWE
int directionPins[2][2] = {{26, 17}, {15, 3}};
int speedPins[2][2] = {{2, 13}, {12, 4}};
bool axis = 0, sign = 1;

// Speed of x and y
int xspeed = 0, yspeed = 0;

// DCV Pins
// 1 - Ball pushing
// 2 - Ball loading
int valve1[] = {43, 45}, valve2[] = {51, 53};

int motorDigital[2] = {30, 6};
int motorAnalog[2] = {7, 5};

int prevSpeed = 0;

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
  for (int l = 0; l < 2; l++) {
    for (int m = 0; m < 2; m++) {
      // Assigning and declaring the pins
      pinMode(directionPins[l][m], OUTPUT);
      pinMode(speedPins[l][m], OUTPUT);
    }
  }
  for (int i = 0; i < 2; i++) {
    pinMode(motorDigital[i], OUTPUT);
    pinMode(motorAnalog[i], OUTPUT);
  }
  pinMode(valve1[0], OUTPUT);
  pinMode(valve1[1], OUTPUT);
  pinMode(valve2[0], OUTPUT);
  pinMode(valve2[1], OUTPUT);

  digitalWrite(motorDigital[0], 1);
  digitalWrite(motorDigital[1], 1);

}

void loop() {
  Usb.Task();

  if (PS3.PS3Connected || PS3.PS3NavigationConnected) {

    if (PS3.getAnalogButton(L2) >= 20) {
      xspeed = map(PS3.getAnalogButton(L2), 20, 255, 60, 120);
      xspeed = constrain(xspeed, 60, 120);
      digitalWrite(directionPins[0][0], 1);
      analogWrite(speedPins[0][0], xspeed);
      digitalWrite(directionPins[0][1], 0);
      analogWrite(speedPins[0][1], xspeed);
      digitalWrite(directionPins[1][0], 0);
      analogWrite(speedPins[1][0], xspeed);
      digitalWrite(directionPins[1][1], 1);
      analogWrite(speedPins[1][1], xspeed);
      Serial.print("L2 working with speed: ");
      Serial.println(xspeed);
    }
    if (PS3.getAnalogButton(R2) >= 20) {
      yspeed = map(PS3.getAnalogButton(R2), 20, 255, 60, 120);
      yspeed = constrain(yspeed, 60, 120);
      digitalWrite(directionPins[0][0], 0);
      analogWrite(speedPins[0][0], xspeed);
      digitalWrite(directionPins[0][1], 1);
      analogWrite(speedPins[0][1], xspeed);
      digitalWrite(directionPins[1][0], 1);
      analogWrite(speedPins[1][0], xspeed);
      digitalWrite(directionPins[1][1], 0);
      analogWrite(speedPins[1][1], xspeed);
      Serial.print("R2 working with speed: ");
      Serial.println(yspeed);

    } else {
      if (PS3.getAnalogHat(LeftHatY) < 147 && PS3.getAnalogHat(LeftHatY) > 107) {
        analogWrite(speedPins[axis][sign], 0);
        analogWrite(speedPins[axis][!sign], 0);
        Serial.print("\nxspeed = 0");
      }
      if (PS3.getAnalogHat(RightHatX) < 147 && PS3.getAnalogHat(RightHatX) > 107) {
        analogWrite(speedPins[!axis][sign], 0);
        analogWrite(speedPins[!axis][!sign], 0);
        Serial.print("\nyspeed = 0");
      }
      if (PS3.getAnalogHat(LeftHatY) > 147) { // N
        yspeed = map(PS3.getAnalogHat(LeftHatY), 148, 255, 60, 120);
        digitalWrite(directionPins[axis][sign], sign);
        analogWrite(speedPins[axis][sign], yspeed);
        digitalWrite(directionPins[axis][!sign], sign);
        analogWrite(speedPins[axis][!sign], yspeed);
      }
      if (PS3.getAnalogHat(LeftHatY) < 107) { // S
        yspeed = map(PS3.getAnalogHat(LeftHatY), 106, 0, 60, 120);
        digitalWrite(directionPins[axis][sign], !sign);
        analogWrite(speedPins[axis][sign], yspeed);
        digitalWrite(directionPins[axis][!sign], !sign);
        analogWrite(speedPins[axis][!sign], yspeed);
      }
      if (PS3.getAnalogHat(RightHatX) > 147) { // E
        xspeed = map(PS3.getAnalogHat(RightHatX), 148, 255, 60, 120);
        digitalWrite(directionPins[!axis][sign], !(!sign ^ axis));
        analogWrite(speedPins[!axis][sign], xspeed);
        digitalWrite(directionPins[!axis][!sign], !(!sign ^ axis));
        analogWrite(speedPins[!axis][!sign], xspeed);
      }
      if (PS3.getAnalogHat(RightHatX) < 107) { // W
        xspeed = map(PS3.getAnalogHat(RightHatX), 106, 0, 60, 120);
        digitalWrite(directionPins[!axis][sign], !(sign ^ axis));
        analogWrite(speedPins[!axis][sign], xspeed);
        digitalWrite(directionPins[!axis][!sign], !(sign ^ axis));
        analogWrite(speedPins[!axis][!sign], xspeed);
      }
    }
    if (PS3.getButtonClick(L1)) {
      bool temp = axis;
      axis = !axis;
      sign = temp ^ sign;
      Serial.println("PRESSED L1, now pins shifted anti-clockwise");
    }
    if (PS3.getButtonClick(R1)) {
      bool temp = axis;
      axis = !axis;
      sign = !(temp ^ sign);
      Serial.println("PRESSED R1, now pins shifted clockwise");
    }

    if (PS3.getButtonClick(TRIANGLE)) {
      if (prevSpeed == 0) {
        for (int s = 0; s <= 245; s += 10) {
          analogWrite(motorAnalog[0], s);
          analogWrite(motorAnalog[1], s);
          delay(100);
        }
        prevSpeed = 245;
      }
    }

    if (PS3.getButtonClick(CROSS)) {
      if (prevSpeed == 245) {
        for (int s = 245; s >= 0; s -= 10) {
          analogWrite(motorAnalog[0], s);
          analogWrite(motorAnalog[1], s);
          delay(100);
        }
        analogWrite(motorAnalog[0], 0);
        analogWrite(motorAnalog[1], 0);
        prevSpeed = 0;
      }
    }

    if (PS3.getButtonClick(UP)) {
      defaultDCV();
      digitalWrite(valve1[0], LOW);
      digitalWrite(valve1[1], HIGH);
      digitalWrite(valve2[0], LOW);
      digitalWrite(valve2[1], HIGH);
      delay(2000); //Wait 2 Second
      defaultDCV();
      delay(10);
    }
    if (PS3.getButtonClick(DOWN)) {
      defaultDCV();
      digitalWrite(valve1[0], HIGH);
      digitalWrite(valve1[1], LOW);
      digitalWrite(valve2[0], HIGH);
      digitalWrite(valve2[1], LOW);
      delay(2000);
      defaultDCV();
      delay(10);
    }
    if (PS3.getButtonClick(PS)) {
      PS3.disconnect();
    }
  }
}

void defaultDCV() {
  digitalWrite(valve1[0], LOW);
  digitalWrite(valve1[1], LOW);
  digitalWrite(valve2[0], LOW);
  digitalWrite(valve2[1], LOW);
}
