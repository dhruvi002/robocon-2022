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
//PS3BT PS3(&Btd, 0x00, 0x15, 0x83, 0x3D, 0x0A, 0x57); 

int direction[] = {5, 7, 3, 22};  //north, west, south, east
int speed[] = {6, 8, 4, 2};

int left_hat, right_hat;
int left_top, left_bot;
int right_right, right_left;
int min_pos = 0, min_mid_pos = 117, max_mid_pos = 137, max_pos = 255;
int min_speed = 60, max_speed = 100;

void setup() {
    Serial.begin(115200);
#if !defined(__MIPSEL__)
  while (!Serial); 
#endif
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); //halt
  }
  Serial.print(F("\r\nPS3 Bluetooth Library Started"));
  for(int i = 0; i <4; i++)
  {
    pinMode(direction[i], OUTPUT);
    pinMode (speed[i], OUTPUT);
  }
}

void loop() {
  Usb.Task();
  if (PS3.PS3Connected || PS3.PS3NavigationConnected){
    
    left_hat = PS3.getAnalogHat(LeftHatY);
    right_hat = PS3.getAnalogHat(RightHatX);

    left_top = map(left_hat, max_mid_pos, max_pos, min_speed, max_speed);
    left_bot = map(left_hat, min_mid_pos, min_pos, min_speed, max_speed);
    right_right = map(right_hat, max_mid_pos, max_pos, min_speed, max_speed);
    right_left = map(right_hat, min_mid_pos, min_pos, min_speed, max_speed);

    if(left_hat > max_mid_pos){
      digitalWrite(direction[1], LOW);
      analogWrite(speed [1], left_top);
      digitalWrite(direction[3], HIGH);
      analogWrite(speed [3], left_top);
    }

    if(left_hat < min_mid_pos){
      digitalWrite(direction[1], HIGH);
      analogWrite(speed [1], left_bot);
      digitalWrite(direction[3], LOW);
      analogWrite(speed [3], left_bot);
    }

    if(right_hat > max_mid_pos){
      digitalWrite(direction[0], LOW);
      analogWrite(speed [0], right_right);
      digitalWrite(direction[2], HIGH);
      analogWrite(speed [2], right_right);
    }

    if(right_hat < min_mid_pos){
      digitalWrite(direction[0], HIGH);
      analogWrite(speed [0], right_left);
      digitalWrite(direction[2], LOW);
      analogWrite(speed [2], right_left);
    }

    if(right_hat >= min_mid_pos && right_hat <= max_mid_pos){
      digitalWrite(direction[0], HIGH);
      analogWrite(speed [0], 0);
      digitalWrite(direction[2], HIGH);
      analogWrite(speed [2], 0);
    }

    if(left_hat >= min_mid_pos && left_hat <= max_mid_pos){
      digitalWrite(direction[1], HIGH);
      analogWrite(speed [1], 0);
      digitalWrite(direction[3], HIGH);
      analogWrite(speed [3], 0);
    }
          if (PS3.getButtonClick(PS)) {
      Serial.print(F("\r\nPS"));
      PS3.disconnect();
  }
}
}
