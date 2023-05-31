int direction[] = {5};
int speed[] = {6};

void setup() {
  // put your setup code here, to run once:
  {
    pinMode(direction[0], OUTPUT);
    pinMode(speed[0], OUTPUT);
  }
}

void loop() {
  // put your main code here, to run repeatedly:   
  {
    digitalWrite(direction[0], HIGH);
    analogWrite(speed[0], 40);
  }
}
 
