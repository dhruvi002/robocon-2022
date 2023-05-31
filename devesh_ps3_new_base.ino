#include <SPI.h>
#include <PS3BT.h>   
USB Usb;
BTD Btd(&Usb);
PS3BT PS3(&Btd);

int motorDigital[2][2] = {{5,7},{12,9}};  // 1,2,3,4
int motorAnalog[2][2] = {{6,8},{13,11}};  // 1,2,3,4
bool dirArray[2][2];

bool axis, sign;

void setup() {
   Serial.begin(9600);
   if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); //halt
  }
  Serial.print(F("\r\nPS3 Bluetooth Library Started"));

  for(int i=0; i<2; i++){
    for(int j=0; j<2; j++){
      pinMode(motorDigital[i][j], OUTPUT);
      pinMode(motorAnalog[i][j], OUTPUT);
    }
  }
}
void loop()
{
  Usb.Task();

  if (PS3.PS3Connected){

      if((PS3.getAnalogHat(LeftHatY)>117 && PS3.getAnalogHat(LeftHatY)<137) && (PS3.getAnalogHat(RightHatX)>117 && PS3.getAnalogHat(RightHatX)<137) ){
        for(int i=0; i<2; i++){
          for(int j=0; j<2; j++){
           analogWrite(motorAnalog[i][j], 0); 
          }
        }
      }

      //LEFT HAT 
    int left_down = map(PS3.getAnalogHat(LeftHatY),0,117,120,70);  // Left Hat Down
    int left_up = map(PS3.getAnalogHat(LeftHatY),137,225,70,120);  // Left Hat UP

    // RIGHT HAT 
    int right_left = map(PS3.getAnalogHat(RightHatX),0,117,120,70); // Right Hat Left
    int right_right = map(PS3.getAnalogHat(RightHatX),137,225,70,120); // Right Hat Right


      //Right Hat mid position
    if(PS3.getAnalogHat(RightHatX)>117 && PS3.getAnalogHat(RightHatX)<137){
      
      if(PS3.getAnalogHat(LeftHatY)>137){
        digitalDirection(PS3.getAnalogHat(LeftHatY), PS3.getAnalogHat(RightHatX), 1);
        for(int i=0; i<2; i++){
          for(int j=0; j<2; j++){
            analogWrite(motorAnalog[i][j], left_up);         
          }
        }
      }

      if(PS3.getAnalogHat(LeftHatY)<117){
        digitalDirection(PS3.getAnalogHat(LeftHatY), PS3.getAnalogHat(RightHatX), 0);
        for(int i=0; i<2; i++){
          for(int j=0; j<2; j++){
            analogWrite(motorAnalog[i][j], left_down);         
          }
        }
      }
    }
    

      // Left hat mid position
    if(PS3.getAnalogHat(LeftHatY)>117 && PS3.getAnalogHat(LeftHatY)<137){
      if(PS3.getAnalogHat(RightHatX)>137){
        digitalDirection(PS3.getAnalogHat(LeftHatY), PS3.getAnalogHat(RightHatX), 1);
        for(int i=0; i<2; i++){
          for(int j=0; j<2; j++){
            analogWrite(motorAnalog[i][j], right_right);         
          }
        }
      }

      else if(PS3.getAnalogHat(LeftHatY)<117){
        digitalDirection(PS3.getAnalogHat(LeftHatY), PS3.getAnalogHat(RightHatX), 0);
        for(int i=0; i<2; i++){
          for(int j=0; j<2; j++){
            analogWrite(motorAnalog[i][j], right_left);         
          }
        }
      }
    }


      // Both hats same placements
    if(PS3.getAnalogHat(LeftHatY)>137 && PS3.getAnalogHat(RightHatX)>137){  //both max position
      digitalDirection(PS3.getAnalogHat(LeftHatY), PS3.getAnalogHat(RightHatX), 1);
      analogSpeed(left_up, right_right, PS3.getAnalogHat(RightHatX), PS3.getAnalogHat(LeftHatY));
    }
    else if(PS3.getAnalogHat(LeftHatY)<117 && PS3.getAnalogHat(RightHatX)<117){  // both hats min position
      digitalDirection(PS3.getAnalogHat(LeftHatY), PS3.getAnalogHat(RightHatX), 0);
      analogSpeed(left_down, right_left, PS3.getAnalogHat(RightHatX), PS3.getAnalogHat(LeftHatY));
    }


    // Both hats oppostite placements
    if(PS3.getAnalogHat(LeftHatY)>137 && PS3.getAnalogHat(RightHatX)<117){  // Left max and Right min
      digitalDirection(PS3.getAnalogHat(LeftHatY), PS3.getAnalogHat(RightHatX), 1);
      analogSpeed(left_up, right_left, PS3.getAnalogHat(RightHatX), PS3.getAnalogHat(LeftHatY));
    }
    else if(PS3.getAnalogHat(LeftHatY)<117 && PS3.getAnalogHat(RightHatX)>137){  // Right min and Left max
      digitalDirection(PS3.getAnalogHat(LeftHatY), PS3.getAnalogHat(RightHatX), 1);
      analogSpeed(left_down, right_right, PS3.getAnalogHat(RightHatX), PS3.getAnalogHat(LeftHatY));
    }

    
    if (PS3.getButtonClick(PS)) {
      PS3.disconnect();
    }
  }
}


void digitalDirection(int LHD, int RHD, int dir1){
  bool dirArray[2][2];
    dirArray[0][0] = dir1;
  if(LHD < RHD){  // >
    dirArray[0][1] = !dir1;
  }else{
    dirArray[0][1] = dir1;
  }
  dirArray[1][0] = !dirArray[0][0];
  dirArray[1][1] = !dirArray[0][1];

  for(int i=0; i<2; i++){
    for(int j=0; j<2; j++){
      digitalWrite(motorDigital[i][j], dirArray[i][j]);
    }
  }
}


void analogSpeed(int LHS, int RHS, int RHD, int LHD){  
  if((LHD>137 && RHD>137) || (LHD<117 && RHD<117)){
    for(int i=0; i<2; i++){
      analogWrite(motorAnalog[1][i], (LHS-RHS));
    }
  }
  else{
    for(int i=0; i<2; i++){
      analogWrite(motorAnalog[0][i], (LHS+RHS));
    }
  }
}


// New Base Codevoid setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
