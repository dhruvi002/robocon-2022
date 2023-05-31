int directionPins[2] = {5, 7};
int spdPins[2] = {6, 8};

int spd, spd_initial = 0;

void setup() {
  for (int i = 0; i < 2; i++) {
    pinMode(directionPins[i], OUTPUT);
    pinMode(spdPins[i], OUTPUT);
  }
  Serial.begin(9600);
  Serial.println("Enter the spd: ");
}

void loop() {
  if (Serial.available() > 0) {
    //direction = (Serial.readStringUntil('.')).toInt();
    spd = Serial.readString().toInt();
    //Serial.print(direction);
    Serial.println(spd);
    
    if (spd >= 0 && spd < 245) {
      // Rotate the motor with the given //({spd}, {time}, {direction}) 
        digitalWrite(directionPins[0], 1);
        digitalWrite(directionPins[1], 1);
      
        if (spd > spd_initial) {
          for(int j = spd_initial ; j <= spd ; j++){      
                analogWrite(spdPins[0], j);
                analogWrite(spdPins[1], j);
                delay(10);
            }
        }
        else{
          for(int j = spd_initial ; j >= spd ; j--){      
                analogWrite(spdPins[1], j);
                analogWrite(spdPins[0], j);
                delay(10);
              }
            }
        spd_initial = spd; 
        }
    else {
      Serial.println("Enter spd value less than 245 or greater than 0 or the motor will go boom");
    }
  }
}
