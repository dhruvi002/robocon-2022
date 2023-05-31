class Motors{
  
  int motorNum = 2;
  int speedVal, dtime, directionVal; 
  int directionPins[2] ;
  int speedPins[2] ;
  int speed_initial = 0 ;
  
  public:
  
  Motors(int motorNum, int speedVal, int directionVal, int dtime, int directionPins, int speedPins, int speed_initial){
    this -> motorNum = motorNum ;
    this -> speedVal = speedVal ; 
    this -> directionVal = directionVal ;
    this -> dtime = dtime ;
    this -> directionPins = directionPins ;
    this -> speedPins = speedPins ;
    this -> speed_initial = speed_initial ;
  }

  Serial2MotorsOppDirection(int speed_initial, int speedVal, ){
    `
  }

  
  Serial2Motors(){
    Serial.println("Enter the direction.speed.time: ");
    if (Serial.available() > 0) {
    // Eg. 0.100:3 in direction.speed.time
    direction = (Serial.readStringUntil('.')).toInt();
    speed = (Serial.readStringUntil('.')).toInt();
    dtime = (Serial.readString()).toInt();
    Serial.print(direction);
    Serial.print(" ");
    Serial.print(speed);
    Serial.print(" ");
    Serial.println(dtime);
  
      if (speed >= 0 && speed < 256) {
        // Rotate the motor with the given //({speed}, {time}, {direction}) 
        for (int i = 0; i < motorNum; i++) {
          digitalWrite(directionPins[i], direction);
          analogWrite(speedPins[i], speed);
        }
        delay(dtime);
        for (int i = 0; i < motorNum; i++) {
          analogWrite(speedPins[i], 0);
        }
      } 
      else {
        Serial.println("Enter Speed value less than 256 or greater than 0");
      }
    }
  }
}
