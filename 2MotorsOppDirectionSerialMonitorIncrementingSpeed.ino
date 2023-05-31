int directionPins[] = {5, 7};
int speedPins[] = {6, 8};

int motorNum = 2;

int speed, speed_initial = 0;
bool direction = false;

void setup() {
  for (int i = 0; i < motorNum; i++) {
    pinMode(directionPins[i], OUTPUT);
    pinMode(speedPins[i], OUTPUT);
  }
  Serial.begin(9600);
  Serial.println("Enter the speed: ");
}

void loop() {
  if (Serial.available() > 0) {
    speed_initial = speed ; 
    //direction = (Serial.readStringUntil('.')).toInt();
    speed = Serial.readString().toInt();
    //Serial.print(direction);
    Serial.println(speed);
    
    if (speed >= 0 && speed < 256) {
      // Rotate the motor with the given //({speed}, {time}, {direction}) 
      for (int i = 0; i < motorNum; i++) {
        digitalWrite(directionPins[0], direction);
        digitalWrite(directionPins[1], !direction); 
      
        if (speed > speed_initial) {
          for(int j = speed_initial ; j <= speed ; j+=1){      
                analogWrite(speedPins[i], speed);
                delay(10);
            }
        }
        else{
          for(int j = speed_initial ; j >= speed ; j-=1){      
                analogWrite(speedPins[i], speed);
                delay(10);
              }
            }
        } 
    }    
    else {
      Serial.println("Enter Speed value less than 256 or greater than 0");
    }
  }
}
