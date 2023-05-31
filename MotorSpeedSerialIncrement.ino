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
  
  digitalWrite(directionPins[0], 1);
  digitalWrite(directionPins[1], 1);
}

void loop() {
  delay(5000);  
  for(int j = 0 ; j <= 240 ; j++){      
    analogWrite(spdPins[0], j);
    analogWrite(spdPins[1], j);
    delay(10);
  }
  delay(30000);
  for(int j = 240 ; j >= 0 ; j--){      
    analogWrite(spdPins[0], j);
    analogWrite(spdPins[1], j);
    delay(10);
  }
  delay(5000);
}
