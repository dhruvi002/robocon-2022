#include <PS3BT.h>
#include <usbhub.h>

#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>

USB Usb;
//USBHub Hub1(&Usb); 

BTD Btd(&Usb); 
PS3BT PS3(&Btd); 

//int max_speedPin = 255, min_speedPin = 0, min_speedPin = 128 ;

int directionPin[] = {5, 7, 32, 3};  //north, west, south, east
int speedPin[] = {6, 8, 2, 4};

int MotorNum = 4;

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

  for(int i = 0; i <MotorNum; i++)
  {
    pinMode(directionPin[i], OUTPUT);
    pinMode (speedPin[i], OUTPUT);
  }
}

int min_pos = 0, max_pos = 255;
int min_speedPin = 60, max_speedPin = 180; 

int left_hat, right_hat;
int left_speedPin, right_speedPin;

int s1 = max(left_speedPin, right_speedPin);
int s3 = left_speedPin - right_speedPin; 
  
void loop() {
  Usb.Task();
  if (PS3.PS3Connected || PS3.PS3NavigationConnected){
    left_hat = PS3.getAnalogHat(LeftHatY);
    right_hat = PS3.getAnalogHat(RightHatX); 
    bool right_dir = right_hat > 127, left_dir = left_hat < 127 ; 

    if(right_dir){
      right_speedPin = map(right_hat, min_speedPin, max_speedPin, 137, max_pos);
     }
    else{
      right_speedPin = map(right_hat, min_speedPin, max_speedPin, 117, min_pos);
     }
     
    if(left_dir){
      left_speedPin = map(left_hat, min_speedPin, max_speedPin, 117, min_pos);
      }
    else{ 
      left_speedPin = map(left_hat, min_speedPin, max_speedPin, 137, max_pos);
      }

    int right_speedPin = constrain(right_speedPin, min_speedPin, max_speedPin);
    int left_speedPin = constrain(left_speedPin, min_speedPin, max_speedPin);
    bool dominant = right_speedPin > left_speedPin;
    
    int s1, s2, s3, s4 ;
    bool wheelDir;
    if(dominant){
      wheelDir = right_dir;
    }
    else{
      wheelDir = left_dir;
    }
    
    digitalWrite(directionPin[0],wheelDir);
    digitalWrite(directionPin[2],!wheelDir);

    if(dominant){
       digitalWrite(directionPin[1],wheelDir);
       digitalWrite(directionPin[3],!wheelDir);
    }
    else{
      digitalWrite(directionPin[1],!wheelDir);
      digitalWrite(directionPin[3],wheelDir);
      }

    int sum, diff ; 
    diff = abs(left_speedPin - right_speedPin);
    sum = max(left_speedPin, right_speedPin); 

    if(117 < left_hat && left_hat < 137 && 117 < right_hat && right_hat < 137){
      analogWrite(directionPin[0], 0);
      analogWrite(directionPin[1], 0);
      analogWrite(directionPin[2], 0);
      analogWrite(directionPin[3], 0);      
    }
    else{
      if (left_dir != right_dir){
        analogWrite(directionPin[0], diff);
        analogWrite(directionPin[1], sum);
        analogWrite(directionPin[2], diff);
        analogWrite(directionPin[3], sum);
    }
      else{      
        analogWrite(directionPin[0], sum);
        analogWrite(directionPin[1], diff);
        analogWrite(directionPin[2], sum);
        analogWrite(directionPin[3], diff);    
    }
   }
  }  
}
  
