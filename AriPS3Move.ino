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
//PS3BT PS3(&Btd, 0x00, 0x15, 0x83, 0x3D, 0x0A, 0x57); // This will also store the bluetooth address - this can be obtained from the dongle when running the sketch

bool printTemperature, printAngle;
int direction[] = {5,7,32,3};
int speed[] = {6,8,2,4};

/*
 * 0: North Wheel
 * 1: East Wheel
 * 2: South Wheel
 * 3: West Wheel
 */
int move_x;
int move_y;
int move_y_up;
int move_y_down;
int move_x_right;
int move_x_left;
int max_speed = 180;
int min_speed = 60;
int rotation_speed = 130;
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
  for(int i=0; i<4; i++){
    pinMode(direction[i], OUTPUT);
    pinMode(speed[i], OUTPUT);
  }  
}
void loop() {
  Usb.Task();
  
  move_y = PS3.getAnalogHat(LeftHatY);
  move_x = PS3.getAnalogHat(RightHatX);
  move_y_up = map(move_y, 137, 255, min_speed, max_speed);
  move_y_down = map(move_y, 117, 0, min_speed, max_speed);
  move_x_right = map(move_x, 137, 255, min_speed, max_speed);
  move_x_left = map(move_x, 117, 0, min_speed, max_speed);
  if (PS3.PS3Connected || PS3.PS3NavigationConnected) {
      if(PS3.getAnalogHat(LeftHatY) > 137){ 
        digitalWrite(direction[1], HIGH);
        analogWrite(speed[1], move_y_up);
        digitalWrite(direction[3], HIGH);
        analogWrite(speed[3], move_y_up);
      }
      if(PS3.getAnalogHat(LeftHatY) < 117){ 
        digitalWrite(direction[1], LOW);
        analogWrite(speed[1], move_y_down);
        digitalWrite(direction[3], LOW);
        analogWrite(speed[3], move_y_down);
      }
      if(PS3.getAnalogHat(RightHatX) > 137){
        digitalWrite(direction[0], HIGH);
        analogWrite(speed[0], move_x_right);
        digitalWrite(direction[2], HIGH);
        analogWrite(speed[2], move_x_right);        
      }
      if(PS3.getAnalogHat(RightHatX) < 117){
        digitalWrite(direction[0], LOW);
        analogWrite(speed[0], move_x_left);
        digitalWrite(direction[2], LOW);
        analogWrite(speed[2], move_x_left);        
      }
      if(PS3.getAnalogHat(RightHatX) > 117 && PS3.getAnalogHat(RightHatX) < 137){
        digitalWrite(direction[0], HIGH);
        analogWrite(speed[0], 0);
        digitalWrite(direction[2], HIGH);
        analogWrite(speed[2], 0);        
      }
      if(PS3.getAnalogHat(LeftHatY) > 117 && PS3.getAnalogHat(LeftHatY) < 137){
        digitalWrite(direction[1], HIGH);
        analogWrite(speed[1], 0);
        digitalWrite(direction[3], HIGH);
        analogWrite(speed[3], 0);        
      }
      

    // Analog button values can be read from almost all buttons
    if (PS3.getAnalogButton(L2) || PS3.getAnalogButton(R2)) {
      Serial.print(F("\r\nL2: "));
      Serial.print(PS3.getAnalogButton(L2));
      if (PS3.PS3Connected) {
        Serial.print(F("\tR2: "));
        Serial.print(PS3.getAnalogButton(R2));
      }
    }

    if (PS3.getButtonClick(PS)) {
      Serial.print(F("\r\nPS"));
      PS3.disconnect();
    }
    else {
      if (PS3.getButtonClick(TRIANGLE)) {
        Serial.print(F("\r\nTriangle"));
        PS3.setRumbleOn(RumbleLow);
      }
      if (PS3.getButtonClick(CIRCLE)) {
        Serial.print(F("\r\nCircle"));
        PS3.setRumbleOn(RumbleHigh);
      }
      if (PS3.getButtonClick(CROSS))
        Serial.print(F("\r\nCross"));
      if (PS3.getButtonClick(SQUARE))
        Serial.print(F("\r\nSquare"));

      if (PS3.getButtonClick(UP)) {
        Serial.print(F("\r\nUp"));
        if (PS3.PS3Connected) {
          PS3.setLedOff();
          PS3.setLedOn(LED4);
        }
      }
      if (PS3.getButtonClick(RIGHT)) {
        Serial.print(F("\r\nRight"));
        if (PS3.PS3Connected) {
          PS3.setLedOff();
          PS3.setLedOn(LED1);
        }
      }
      if (PS3.getButtonClick(DOWN)) {
        Serial.print(F("\r\nDown"));
        if (PS3.PS3Connected) {
          PS3.setLedOff();
          PS3.setLedOn(LED2);
        }
      }
      if (PS3.getButtonClick(LEFT)) {
        Serial.print(F("\r\nLeft"));
        if (PS3.PS3Connected) {
          PS3.setLedOff();
          PS3.setLedOn(LED3);
        }
      }

      if (PS3.getButtonClick(L1)){
        digitalWrite(direction[1], HIGH);
        analogWrite(speed[1], rotation_speed);
        digitalWrite(direction[2], HIGH);
        analogWrite(speed[2], rotation_speed);
        digitalWrite(direction[3], HIGH);
        analogWrite(speed[3], rotation_speed);
        digitalWrite(direction[4], HIGH);
        analogWrite(speed[4], rotation_speed);                                
      }
      
      if (PS3.getButtonClick(L3))
        Serial.print(F("\r\nL3"));
        
      if (PS3.getButtonClick(R1)){
        digitalWrite(direction[1], LOW);
        analogWrite(speed[1], rotation_speed);
        digitalWrite(direction[2], LOW);
        analogWrite(speed[2], rotation_speed);
        digitalWrite(direction[3], LOW);
        analogWrite(speed[3], rotation_speed);
        digitalWrite(direction[4], LOW);
        analogWrite(speed[4], rotation_speed);                                        
      }
      
      if (PS3.getButtonClick(R3))
        Serial.print(F("\r\nR3"));

      if (PS3.getButtonClick(SELECT)) {
        Serial.print(F("\r\nSelect - "));
        PS3.printStatusString();
      }
      
      if (PS3.getButtonClick(START)) {
        Serial.print(F("\r\nStart"));
        printAngle = !printAngle;
      }
    }
#if 0 // Set this to 1 in order to see the angle of the controller
    if (printAngle) {
      Serial.print(F("\r\nPitch: "));
      Serial.print(PS3.getAngle(Pitch));
      Serial.print(F("\tRoll: "));
      Serial.print(PS3.getAngle(Roll));
    }
#endif
  }
#if 0 // Set this to 1 in order to enable support for the Playstation Move controller
  else if (PS3.PS3MoveConnected) {
    if (PS3.getAnalogButton(T)) {
      Serial.print(F("\r\nT: "));
      Serial.print(PS3.getAnalogButton(T));
    }
    if (PS3.getButtonClick(PS)) {
      Serial.print(F("\r\nPS"));
      PS3.disconnect();
    }
    else {
      if (PS3.getButtonClick(SELECT)) {
        Serial.print(F("\r\nSelect"));
        printTemperature = !printTemperature;
      }
      if (PS3.getButtonClick(START)) {
        Serial.print(F("\r\nStart"));
        printAngle = !printAngle;
      }
      if (PS3.getButtonClick(TRIANGLE)) {
        Serial.print(F("\r\nTriangle"));
        PS3.moveSetBulb(Red);
      }
      if (PS3.getButtonClick(CIRCLE)) {
        Serial.print(F("\r\nCircle"));
        PS3.moveSetBulb(Green);
      }
      if (PS3.getButtonClick(SQUARE)) {
        Serial.print(F("\r\nSquare"));
        PS3.moveSetBulb(Blue);
      }
      if (PS3.getButtonClick(CROSS)) {
        Serial.print(F("\r\nCross"));
        PS3.moveSetBulb(Yellow);
      }
      if (PS3.getButtonClick(MOVE)) {
        PS3.moveSetBulb(Off);
        Serial.print(F("\r\nMove"));
        Serial.print(F(" - "));
        PS3.printStatusString();
      }
    }
    if (printAngle) {
      Serial.print(F("\r\nPitch: "));
      Serial.print(PS3.getAngle(Pitch));
      Serial.print(F("\tRoll: "));
      Serial.print(PS3.getAngle(Roll));
    }
    else if (printTemperature) {
      Serial.print(F("\r\nTemperature: "));
      Serial.print(PS3.getTemperature());
    }
  }
#endif
}
