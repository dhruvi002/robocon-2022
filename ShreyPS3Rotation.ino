#include <SPI.h>
#include <PS3BT.h>   
USB Usb;
BTD Btd(&Usb);
PS3BT PS3(&Btd);

int motorDigital[] = {5,3,22,7}; // north east south west
int motorAnalog[] = {6,4,2,8}; 
//int min_Val = 70;
//int max_Val = 120;

void shift() {
    
}

void setup() {
   Serial.begin(9600);
   if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); //halt
  }
  Serial.print(F("\r\nPS3 Bluetooth Library Started"));

  for(int i=0; i<4; i++){
    pinMode(motorDigital[i], OUTPUT);
    pinMode(motorAnalog[i], OUTPUT);
  }
}
void loop(){
  Usb.Task();

  if (PS3.PS3Connected){

    if(PS3.getAnalogButton(R2)<5 && PS3.getAnalogButton(L2)<5){
      if((PS3.getAnalogHat(LeftHatY)>117 && PS3.getAnalogHat(LeftHatY)<137)){
        for(int i=2; i<4; i++){
          analogWrite(motorAnalog[i], 0);
        }
      }
      if(PS3.getAnalogHat(RightHatX)>117 && PS3.getAnalogHat(RightHatX)<137){
          for(int j=0; j<2; j++){
          analogWrite(motorAnalog[j], 0);
          }
        }
      }

    int left_down = map(PS3.getAnalogHat(LeftHatY),0,117,120,70);
    int left_up = map(PS3.getAnalogHat(LeftHatY),137,225,70,120);
    int right_down = map(PS3.getAnalogHat(RightHatX),0,117,120,70);
    int right_up = map(PS3.getAnalogHat(RightHatX),137,225,70,120);
    int L2_speed = map(PS3.getAnalogButton(L2),0,225,70,120);
    int R2_speed = map(PS3.getAnalogButton(R2),0,225,70,120);

    if(PS3.getAnalogHat(LeftHatY)>137){
      for(int i=2; i<4; i++){
        analogWrite(motorAnalog[i],left_up );
        digitalWrite(motorDigital[i], HIGH);
        Serial.print("forward");
      }
    }

    if(PS3.getAnalogHat(LeftHatY)<117){
      for(int i=2; i<4; i++){
        analogWrite(motorAnalog[i],left_down );
        digitalWrite(motorDigital[i], LOW);
        Serial.print("reverse");
      }
    }

    if(PS3.getAnalogHat(RightHatX)>137){
      for(int i=0; i<2; i++){
        analogWrite(motorAnalog[i],right_up );
        digitalWrite(motorDigital[i], HIGH);
        Serial.print("right");
      }
    }

    if(PS3.getAnalogHat(RightHatX)<117){
      for(int i=0; i<2; i++){
        analogWrite(motorAnalog[i],right_down );
        digitalWrite(motorDigital[i], LOW);
        Serial.print("left");
      }
    }

    if(PS3.getAnalogButton(R2)>5){
      for(int i=0; i<4; i+=2){
        analogWrite(motorAnalog[i],R2_speed );
        digitalWrite(motorDigital[i], HIGH);
      }
      for(int j=1; j<4; j+=2){
        analogWrite(motorAnalog[j],R2_speed );
        digitalWrite(motorDigital[j], LOW);
      }
    }

    if(PS3.getAnalogButton(L2)>5){
      for(int i=0; i<4; i+=2){
        analogWrite(motorAnalog[i],L2_speed );
        digitalWrite(motorDigital[i], LOW);
      }
      for(int j=1; j<4; j+=2){
        analogWrite(motorAnalog[j],L2_speed );
        digitalWrite(motorDigital[j], HIGH);
      }
    }
  }
}
