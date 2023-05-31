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

int dir[] = {5,7,32,3}; //1,2,3,4
int pwm[] = {6,8,2,4}; //
bool phase[] = {HIGH,LOW,HIGH,HIGH};

/*
 * 0: North Wheel
 * 1: East Wheel
 * 2: South Wheel
 * 3: West Wheel
 */
int left_hat, right_hat;


int left_speed;
int right_speed;
int max_speed = 180;
int min_speed = 60;
int min_pos =0; 
int min_mid_pos=117; 
int max_mid_pos=137; 
int max_pos=255;
int rotation_speed = 130;
int wheelDir;
int spd;
int left_button, right_button;
int left_L2, right_R2;


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
    pinMode(dir[i], OUTPUT);
    pinMode(pwm[i], OUTPUT);
  }  
}
void loop() {
  Usb.Task();
  if (PS3.PS3Connected || PS3.PS3NavigationConnected) {
  left_hat = PS3.getAnalogHat(LeftHatY);
  right_hat = PS3.getAnalogHat(RightHatX);
  bool right_dir = right_hat > 127; 
  bool left_dir = left_hat > 127; 
  
  if(left_dir){
   left_speed = map(left_hat, max_mid_pos, max_pos, min_speed, max_speed);
  }else{
  left_speed = map(left_hat, min_mid_pos, min_pos, min_speed, max_speed);
  }
  left_speed = constrain(left_speed, 0, max_speed);


  if(right_dir){
     right_speed = map(right_hat, max_mid_pos, max_pos, min_speed, max_speed);
  }else{
     right_speed = map(right_hat, min_mid_pos, min_pos, min_speed, max_speed);
  }
  
  right_speed = constrain(right_speed, 0, max_speed);
 

  left_button = PS3.getAnalogButton(L2);
  right_button = PS3.getAnalogButton(R2);

  left_L2= map(left_button, 0, 255, min_speed, max_speed);
  right_R2= map(right_button,0, 255, min_speed,max_speed);
  
  bool dominate = right_speed > left_speed;
      if(dominate){
        wheelDir = right_dir;
        }else{
        wheelDir = left_dir;
      }
      digitalWrite(dir[0],wheelDir);
      digitalWrite(dir[2],!wheelDir);
      

      if(dominate){
         digitalWrite(dir[1],wheelDir);
         digitalWrite(dir[3],!wheelDir);
        }else{
         digitalWrite(dir[1],!wheelDir);
         digitalWrite(dir[3],wheelDir);
      }

      int Less = constrain(abs(left_speed - right_speed),0, 120);
      int More = constrain(max(left_speed, right_speed),0,120);
      
      Less *= Less>=60;
      More *= More>=60;
      
      
      
      if(left_hat >= 117 && left_hat <= 137 && right_hat >= 117 && right_hat <= 137){
       analogWrite(pwm[0],0); 
       analogWrite(pwm[1],0);
       analogWrite(pwm[2],0);
       analogWrite(pwm[3],0);
      }
      
      else if(left_dir == right_dir){
       analogWrite(pwm[0],More); 
       analogWrite(pwm[1],Less);
       analogWrite(pwm[2],More);
       analogWrite(pwm[3],Less);
      }else{
       analogWrite(pwm[0],Less); 
       analogWrite(pwm[1],More);
       analogWrite(pwm[2],Less);
       analogWrite(pwm[3],More);       
      }
      
      
   }

}











    
    
    
    
   
