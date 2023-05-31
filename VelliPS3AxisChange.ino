#include <PS3BT.h>
#include <usbhub.h>
// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>

USB Usb;
//USBHub Hub1(&Usb); // Some dongles have a hub inside

BTD Btd(&Usb); // You have to create the Bluetooth Dongle instance like so
/* You can create the instance of the class in two ways */
PS3BT PS3(&Btd); // This will just create the instance
//PS3BT PS3(&Btd, 0x00, 0x15, 0x83

//PS3BT PS3(&Btd, 0x00, 0x15, 0x83, 0x3D, 0x0A, 0x57); // This will also store the bluetooth address - this can be obtained from the dongle when running the sketch

bool printTemperature, printAngle;
int direction[] = {5, 7, 32, 3};
int speed[] = {6, 8, 2, 4};

/*
   0: North Wheel
   1: East Wheel
   2: South Wheel
   3: West Wheel
*/
int left_top, left_bot;
int right_right, right_left;
int x, y;
int min_speed_allowed = 60, max_speed_allowed = 180;

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

  for(int i = 0; i < 4; i++)
  {
    pinMode(direction[i], OUTPUT);
    pinMode(speed[i], OUTPUT);
  }
}

void loop()
{
  Usb.Task();
  if (PS3.PS3Connected || PS3.PS3NavigationConnected)
  { x = PS3.getAnalogHat(RightHatX);
    y = PS3.getAnalogHat(LeftHatY);
    left_top = map(y, 137, 255, min_speed_allowed, max_speed_allowed);
    left_bot = map(y, 0, 117, min_speed_allowed, max_speed_allowed);
    right_right = map(x, 137, 255, min_speed_allowed, max_speed_allowed);
    right_left = map(x, 0, 117, min_speed_allowed, max_speed_allowed);
    if (PS3.getAnalogHat(LeftHatY) > 137)
    {
      digitalWrite(direction[1], HIGH);
      analogWrite(speed[1], left_top);
      digitalWrite(direction[3], HIGH);
      analogWrite(speed[3], left_top);
    }

    else if (PS3.getAnalogHat(LeftHatY) < 117)
    {
      digitalWrite(direction[1], LOW);
      analogWrite(speed[1], left_top);
      digitalWrite(direction[3], LOW);
      analogWrite(speed[3], left_top);
    }
    if (PS3.getAnalogHat(RightHatX) > 137)
    {
      digitalWrite(direction[0], HIGH);
      analogWrite(speed[0], right_right);
      digitalWrite(direction[2], HIGH);
      analogWrite(speed[2], right_right);
    }

    else if (PS3.getAnalogHat(RightHatX) < 117)
    {
      digitalWrite(direction[0], LOW);
      analogWrite(speed[0], right_right);
      digitalWrite(direction[2], LOW);
      analogWrite(speed[2], right_right);
    }
    if (PS3.getAnalogHat(LeftHatY) < 137 && PS3.getAnalogHat(LeftHatY) > 117)
    {
      digitalWrite(direction[1], HIGH);
      analogWrite(speed[1], 0);
      digitalWrite(direction[3], HIGH);
      analogWrite(speed[3], 0);
    }
    if (PS3.getAnalogHat(RightHatX) < 137 && PS3.getAnalogHat(RightHatX) > 117)
    {
      digitalWrite(direction[0], HIGH);
      analogWrite(speed[0], 0);
      digitalWrite(direction[2], HIGH);
      analogWrite(speed[2], 0);
    }
  if(PS3.getAnalogButton(L2)>0){
    if (PS3.getAnalogHat(LeftHatY) > 137)
    {
      digitalWrite(direction[0], HIGH);
      analogWrite(speed[0], right_right);
      digitalWrite(direction[2], HIGH);
      analogWrite(speed[2], right_right);
    }

    else if (PS3.getAnalogHat(LeftHatY) < 117)
    {
      digitalWrite(direction[0], LOW);
      analogWrite(speed[0], right_right);
      digitalWrite(direction[2], LOW);
      analogWrite(speed[2], right_right);
    }
  }
    if(PS3.getButtonClick(R2)>0){
    if (PS3.getAnalogHat(RightHatX) > 137)
    {
      digitalWrite(direction[1], HIGH);
      analogWrite(speed[1], left_top);
      digitalWrite(direction[3], HIGH);
      analogWrite(speed[3], left_top);
    }

    else if (PS3.getAnalogHat(RightHatX) < 117)
    {
      digitalWrite(direction[1], LOW);
      analogWrite(speed[1], left_top);
      digitalWrite(direction[3], LOW);
      analogWrite(speed[3], left_top);
    }
   }
 }
}

//getButtonClick
