#include <PS3BT.h>
#include <usbhub.h>
#include <Servo.h>

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

int direction[] = {22,3,9,12}; //north,west,south,east
int speed[] = {2,4,11,13}; //
bool phase[] = {HIGH,LOW,HIGH,HIGH};

/*
 * 0: North Wheel
 * 1: East Wheel
 * 2: South Wheel
 * 3: West Wheel
 */
int left_hat;


int left_up, left_down;
int max_speed = 180;
int min_speed = 60;
int min_pos =0; 
int min_mid_pos=117; 
int max_mid_pos=137; 
int max_pos=255;
int rotation_speed = 130;
int dir;
int spd;
int left_button;
int left_SQUARE;

Servo myservo;
int pos = 0;
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
  myservo.attach(27); 
}

void loop() {
  Usb.Task();
  
  left_hat = PS3.getAnalogHat(LeftHatY);
  
  left_up = map(left_hat, max_mid_pos, max_pos, min_speed, max_speed);
  left_down = map(left_hat, min_mid_pos, min_pos, min_speed, max_speed);
 

  left_button = PS3.getAnalogButton(SQUARE);
 

  left_SQUARE= map(left_button, 0, 255, min_speed, max_speed);
  
 
  
  if (PS3.PS3Connected || PS3.PS3NavigationConnected) {
      
      if(left_hat > 137){      
        digitalWrite(direction[1], phase[1]);
        analogWrite(speed[1], left_up);
        digitalWrite(direction[3], phase[3]);
        analogWrite(speed[3], left_up);
      }
     
      
      if(left_hat < 117){ 
        digitalWrite(direction[1], !phase[1]);
        analogWrite(speed[1], left_down);
        digitalWrite(direction[3], !phase[3]);
        analogWrite(speed[3], left_down);
      }

      if(left_hat > 137){
        digitalWrite(direction[0], phase[0]);
        analogWrite(speed[0], left_up);
        digitalWrite(direction[2], phase[2]);
        analogWrite(speed[2], left_up);        
      }
     
      
      if(left_hat < 117){
        digitalWrite(direction[0], !phase[0]);
        analogWrite(speed[0], left_down);
        digitalWrite(direction[2], !phase[2]);
        analogWrite(speed[2], left_down);        
      }

       if(left_hat >= 117 && left_hat <= 137 and PS3.getAnalogButton(SQUARE)==0){
        digitalWrite(direction[1], phase[1]);
        analogWrite(speed[1], 0);
        digitalWrite(direction[3], phase[3]);
        analogWrite(speed[3], 0);        
      }

       if(left_hat >= 117 && left_hat <= 137 and PS3.getAnalogButton(SQUARE)==0){
        digitalWrite(direction[0], phase[0]);
        analogWrite(speed[0], 0);
        digitalWrite(direction[2], phase[2]);
        analogWrite(speed[2], 0);        
      }
     
 


 // Analog button values can be read from almost all buttons

     
    
     if(PS3.getAnalogButton(SQUARE)>0){
      
  for (pos = 0; pos <= 90; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15 ms for the servo to reach the position
  }
  for (pos = 90; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15 ms for the servo to reach the position
  }
}
}
}










    
    
    
    
   
