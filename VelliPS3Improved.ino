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

int direction[] = {5, 7, 22, 3}; //north, west,south,east
int speed[] = {6, 8, 2, 4};
bool phase[] = {HIGH, LOW, LOW, HIGH};
int counter = 0;

/*
 * 0: North Wheel
 * 1: East Wheel
 * 2: South Wheel
 * 3: West Wheel
 */
 
int left_hat, right_hat;
int left_top, left_bot;
int right_right, right_left;
int min_pos = 0, min_mid_pos = 117, max_mid_pos = 137, max_pos = 255;
int min_speed = 60, max_speed = 180;
int left_button_speed, right_button_speed;
int left_button, right_button;

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

    left_button = PS3.getAnalogButton(L2);
    right_button = PS3.getAnalogButton(R2);
    
    left_hat = PS3.getAnalogHat(LeftHatY);
    right_hat = PS3.getAnalogHat(RightHatX);

    left_top = map(left_hat, max_mid_pos, max_pos, min_speed, max_speed);
    left_bot = map(left_hat, min_mid_pos, min_pos, min_speed, max_speed);
    right_right = map(right_hat, max_mid_pos, max_pos, min_speed, max_speed);
    right_left = map(right_hat, min_mid_pos, min_pos, min_speed, max_speed);

    left_button_speed = map(left_button,min_pos, max_pos, min_speed, max_speed);
    right_button_speed = map(right_button, min_pos, max_pos, min_speed, max_speed);

    if(right_hat >= min_mid_pos && right_hat <= max_mid_pos){
      for(counter = 1 ; counter < 4 ; counter +=2){
        digitalWrite(direction[counter], phase[counter]);
        analogWrite(speed [counter], 0);
      }
    }

    if(left_hat >= min_mid_pos && left_hat <= max_mid_pos){
      for(counter = 0 ; counter < 4 ; counter +=2){
        digitalWrite(direction[counter], phase[counter]);
        analogWrite(speed [counter], 0);
      }
    }
    
    if(left_hat > max_mid_pos){
      for(counter = 0 ; counter < 4 ; counter += 2){
        digitalWrite(direction[counter], phase[counter]);
        analogWrite(speed [counter], left_top);
      }
    }

    if(left_hat < min_mid_pos){
      for(counter = 0 ; counter < 4 ; counter +=2){
        digitalWrite(direction[counter], !phase[counter]);
        analogWrite(speed [counter], left_bot);
      }
    }

    if(right_hat > max_mid_pos){
      for(counter = 1 ; counter < 4 ; counter +=2){
        digitalWrite(direction[counter], phase[counter]);
        analogWrite(speed [counter], right_right);
      } 
    }

    if(right_hat < min_mid_pos){
      for(counter = 1 ; counter < 4 ; counter +=2){
        digitalWrite(direction[counter], !phase[counter]);
        analogWrite(speed [counter], right_right);
      } 
    }
//north west south east
    if (left_button > 10) {
      for(counter = 0 ; counter < 4 ; counter ++){
        digitalWrite(direction[counter], 
        !phase[counter]);
        analogWrite(speed [counter], left_button_speed);
      } 
    }

    else if (right_button > 10) {
      for(counter = 0 ; counter < 4 ; counter ++){
        digitalWrite(direction[counter], phase[counter]);
        analogWrite(speed [counter], left_button_speed);
      } 
    }
    if (PS3.getButtonClick(PS)) {
     Serial.print(F("\r\nPS"));
     PS3.disconnect();
  }
}
